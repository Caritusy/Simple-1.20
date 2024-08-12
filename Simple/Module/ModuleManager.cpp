#include "ModuleManager.h"
#include "../../Utils/easylogging++.h"
#include "../../Utils/Json.hpp"

using json = nlohmann::json;
ModuleManager::~ModuleManager()
{
	initialized = false;
	auto lock = lockModuleListExclusive();
	moduleList.clear();
}

ModuleManager::ModuleManager(GameData* gameData)
{
	gameData = gameData;
}

void ModuleManager::initModules()
{
	LOG(INFO) << "Initializing modules.";
	{
		auto lock = lockModuleListExclusive();
		moduleList.push_back(std::shared_ptr<IModule>(new BlockReach()));
		moduleList.push_back(std::shared_ptr<IModule>(new Velocity()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoPacket()));
		moduleList.push_back(std::shared_ptr<IModule>(new Reach()));
		moduleList.push_back(std::shared_ptr<IModule>(new Nuker()));
		moduleList.push_back(std::shared_ptr<IModule>(new AntiBot()));
		moduleList.push_back(std::shared_ptr<IModule>(new Killaura()));
		moduleList.push_back(std::shared_ptr<IModule>(new FullBright()));
		moduleList.push_back(std::shared_ptr<IModule>(new Spammer()));
	//	moduleList.push_back(std::shared_ptr<IModule>(new HudModule()));
	//	moduleList.push_back(std::shared_ptr<IModule>(new GuiMod()));
		moduleList.push_back(std::shared_ptr<IModule>(new Arraylist()));
		//moduleList.push_back(std::shared_ptr<IModule>(new NoWeb()));


#ifdef _DEBUG
		moduleList.push_back(std::shared_ptr<IModule>(new PacketLogger()));
#endif // _DEBUG


		std::sort(moduleList.begin(), moduleList.end(), [](auto lhs, auto rhs) {
			auto current = lhs;
			auto other = rhs;
			return std::string{ *current->getRawModuleName() } < std::string{ *other->getRawModuleName() };
			});

		initialized = true;
	}

}

void ModuleManager::disable() {
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		if (mod->isEnabled())
			mod->setEnabled(false);
	}
}

void ModuleManager::onLoadConfig(void* confVoid) {
	auto conf = reinterpret_cast<json*>(confVoid);
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		mod->onLoadConfig(conf);
	}
}
void ModuleManager::onSaveConfig(void* confVoid) {
	auto conf = reinterpret_cast<json*>(confVoid);
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		mod->onSaveConfig(conf);
	}
}

void ModuleManager::onTick(GameMode* gameMode)
{
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onTick(gameMode);
	}
}

void ModuleManager::onAttack(entity* attackedEnt)
{
	if (!isInitialized())
		return;

	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onAttack(attackedEnt);
	}
}

void ModuleManager::onWorldTick(GameMode* gameMode) {
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onWorldTick(gameMode);
	}
}

void ModuleManager::onKeyUpdate(int key, bool isDown)
{
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		mod->onKeyUpdate(key, isDown);
	}
}

void ModuleManager::onKey(int key, bool isDown, bool& shouldCancel)
{
	if (!isInitialized())
		return;
	auto mutex = lockModuleList();

	for (auto& mod : moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onKey(key, isDown, shouldCancel);
	}
}

void ModuleManager::onPreRender()
{
	if (!isInitialized())
		return;
	auto mutex = lockModuleList();

	for (auto& mod : moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onPreRender();
	}
}

void ModuleManager::onPostRender()
{
	if (!isInitialized())
		return;
	auto mutex = lockModuleList();

	for (auto& mod : moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onPostRender();
	}
}

void ModuleManager::onLevelRender()
{
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& it : moduleList) {
		if (it->isEnabled() || it->callWhenDisabled())
			it->onLevelRender();
	}
}

void ModuleManager::onMove(MoveInputHandler* handler)
{
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& it : moduleList) {
		if (it->isEnabled() || it->callWhenDisabled())
			it->onMove(handler);
	}
}

void ModuleManager::onPlayerTick(Player* player)
{
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& it : moduleList) {
		if (it->isEnabled() || it->callWhenDisabled())
			it->onPlayerTick(player);
	}
}

void ModuleManager::onSendPacket(Packet* packet)
{
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& it : moduleList) {
		if (it->isEnabled() || it->callWhenDisabled())
			it->onSendPacket(packet);
	}
}

void ModuleManager::onSendClientPacket(Packet* packet)
{
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& it : moduleList) {
		if (it->isEnabled() || it->callWhenDisabled())
			it->onSendClientPacket(packet);
	}
}

void ModuleManager::onBaseTick(entity* ent)
{
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		mod->onBaseTick(ent);
	}
}
std::vector<std::shared_ptr<IModule>>* ModuleManager::getModuleList()
{
	return &moduleList;
}
int ModuleManager::getModuleCount()
{
	return (int)moduleList.size();
}
int ModuleManager::getEnabledModuleCount(){
	int i = 0;
	auto lock = lockModuleList();
	for (auto& it : moduleList) {
		if (it->isEnabled()) i++;
	}
	return i;
}
ModuleManager* moduleMgr = new ModuleManager(&Game);