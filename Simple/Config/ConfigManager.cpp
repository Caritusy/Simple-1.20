#include "ConfigManager.h"
#include <filesystem>
#include "../../Utils/easylogging++.h"
namespace fs = std::filesystem;

std::wstring ConfigManager::GetRoamingFolderPath() {
	wchar_t path[MAX_PATH];
	DWORD length = GetModuleFileNameW(nullptr, path, MAX_PATH);
	if (length == 0 || length == MAX_PATH) {
		throw std::runtime_error("Failed to retrieve current program directory");
	}
	std::wstring fullPath(path);
	std::wstring::size_type pos = fullPath.find_last_of(L"\\/");
	if (pos != std::wstring::npos) {
		return fullPath.substr(0, pos);
	}
	return fullPath;
}

ConfigManager::ConfigManager() {
	roamingFolder = GetRoamingFolderPath();
}

ConfigManager::~ConfigManager() {}

void ConfigManager::loadConfig(std::string name, bool create) {

	size_t allocSize = name.size() + roamingFolder.size() + 20;  // std::wstring::size() can be wierd so lets make sure this actually fits
	char* fullPath = new char[allocSize];
	sprintf_s(fullPath, allocSize, "%S\\Configs\\%s.h", roamingFolder.c_str(), name.c_str());
	LOG(INFO) << "roamingFolder: " << roamingFolder.c_str();
	const bool configExists = std::filesystem::exists(fullPath);
	if (configExists || create) {
		if (name != currentConfig)
			saveConfig();  // Save old config

		currentConfig = name;
		if (configExists) {
			std::ifstream confFile(fullPath, std::ifstream::binary);
			json conf;
			try {
				currentConfigObj.clear();
				confFile >> currentConfigObj;
			}
			catch (json::parse_error& e) {
				LOG(DEBUG) << "Config Load Exception!: " << e.what();
			}
			currentConfigObj["from"] = "SimpleMod";
		}

		if (configExists) {
			moduleMgr->onLoadConfig(&currentConfigObj);
			if (currentConfigObj.contains("prefix")) {
				std::string prefix = currentConfigObj["prefix"];
				cmdMgr->prefix = prefix.at(0);
			}
			//if (currentConfigObj.contains("friends")) {
			//	std::vector<std::string> Friends = currentConfigObj["friends"];
			//	//friends.loadList(Friends);
			//}
		}

		if (create)
			saveConfig();

		if (Game.getLocalPlayer() != nullptr) {
			static bool helpedUser = false;
		//	LOG(INFO) << "Successfully "<< (!configExists ? "created" : "loaded") << " config "<< name.c_str();
			Game.getClientInstance()->getGuiData()->displayClientMessageF("[%sSimple%s] %sSuccessfully %s config %s%s%s!", GOLD, WHITE, GREEN, !configExists ? "created" : "loaded", GRAY, name.c_str(), GREEN);
			if (!helpedUser && name != "default") {
				helpedUser = true;
				Game.getClientInstance()->getGuiData()->displayClientMessageF("[%sSimple%s] %sEnter \"%s%cconfig load default%s\" to load your old config!", GOLD, WHITE, YELLOW, WHITE, cmdMgr->prefix, YELLOW);
			}
		}
	}
	else {
		if (Game.getLocalPlayer() != nullptr)
			Game.getClientInstance()->getGuiData()->displayClientMessageF("[%sSimple%s] %sCould not load config %s%s%s!", GOLD, WHITE, RED, GRAY, name.c_str(), RED);
	}

	delete[] fullPath;
}

void ConfigManager::saveConfig() {
	LOG(INFO) << "Saving config " << currentConfig.c_str();
	size_t allocSize = currentConfig.size() + roamingFolder.size() + 20;  // std::wstring::size() can be weird so lets make sure this actually fits
	char* fullPath = new char[allocSize];
	sprintf_s(fullPath, allocSize, "%S\\Configs\\%s.h", roamingFolder.c_str(), currentConfig.c_str());

	moduleMgr->onSaveConfig(&currentConfigObj);

	std::string prefix;
	prefix.push_back(cmdMgr->prefix);
	currentConfigObj["prefix"] = prefix;
//	currentConfigObj["friends"] = friends.getList();

	std::ofstream o(fullPath, std::ifstream::binary);
	o << std::setw(4) << currentConfigObj << std::endl;
	o.flush();
	o.close();

	delete[] fullPath;
}

void ConfigManager::init() {
	LOG(INFO) << "Initializing config";
	fs::path currentPath = roamingFolder.c_str();
	fs::path configsFolder = currentPath / "Configs";
	if (!fs::exists(configsFolder)) {
		fs::create_directory(configsFolder);
	}
	loadConfig(currentConfig, true);
}

ConfigManager* configMgr = new ConfigManager();
