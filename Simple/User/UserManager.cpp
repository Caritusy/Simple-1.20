#include "UserManager.h"
#include <chrono>
#include <ctime>
#include <comdef.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include "../../Utils/Json.hpp"
#include "../../Utils/network.h"
#include "../../Memory/GameData.h"
#include <filesystem>

#include <intrin.h>

#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "Crypt32.lib")

namespace fs = std::filesystem;
std::string UserManager::getSignature(const json& params){
	std::string params_str = params.dump();
	std::string signature = this->tok + std::string("params") + params_str + "ts" + std::to_string(std::time(nullptr)) + "user_id" + this->user;
	json request_json = {
		{"user_id",  this->user},
		{"params", params_str},
		{"ts", std::time(nullptr)},
		{"sign", calculateMD5(signature)}
	};
	return request_json.dump();
}
UserManager::UserManager(std::string user, std::string tok){
	this->tok = tok;
	this->user = user;
}
UserManager::~UserManager()
{
}
std::string UserManager::calculateMD5(const std::string& input){
	EVP_MD_CTX* mdctx;
	const EVP_MD* md = EVP_md5();
	unsigned char md_value[EVP_MAX_MD_SIZE];
	unsigned int md_len;

	mdctx = EVP_MD_CTX_new();
	EVP_DigestInit_ex(mdctx, md, NULL);
	EVP_DigestUpdate(mdctx, input.c_str(), input.length());
	EVP_DigestFinal_ex(mdctx, md_value, &md_len);
	EVP_MD_CTX_free(mdctx);

	std::stringstream ss;
	ss << std::hex << std::setfill('0');
	for (unsigned int i = 0; i < md_len; i++) {
		ss << std::setw(2) << static_cast<unsigned int>(md_value[i]);
	}

	return ss.str();
}
bool UserManager::TimeAuth(long Time){
	json params = { {"page", 1} };
	std::string time = Network::Request("http://afdian.net/api/open/ping", Network:: Request(params));
	json jsonResponse = json::parse(time);
	if (jsonResponse["ec"] == 200) {
		if (jsonResponse["data"]["request"]["ts"] < Time)
			return true;
	}
	else if(jsonResponse["ec"] == 400002){
		LOG(WARNING) << "Response :" << jsonResponse["ec"] <<"【请校验本机时间!】";
		return false;
	}
	else {
		return false;
	}
	return false;
}

bool UserManager::FileAuth(std::string path){
	std::string line;
	std::ifstream inputFile("Auth");
	if (inputFile.is_open()) {
		while (std::getline(inputFile, line));
		json params = { {"page", 1} };
		std::string result = Network::Request("http://afdian.net/api/open/query-sponsor", getSignature(params));
		json jsonResponse = json::parse(result);

		if (jsonResponse["ec"] == 200) {
			int e = 1;
			for (int i = 0; i < jsonResponse["data"]["total_count"].get<int>();e++) {
				json parameter = { {"page", e} };
				std::string results = Network::Request("http://afdian.net/api/open/query-sponsor", getSignature(parameter));
				json Response = json::parse(results);
				json dataList = Response["data"]["list"];
				i += Response.size();
				if (Response["ec"] == 200) {
					for (auto& item : dataList) {
						//LOG(INFO) << calculateMD5(item["user"]["user_id"].get<std::string>() + GetHwid() + "vqSKa4hUYNkjF3VertdCJxfb8p5nmXwB")<< item["user"]["name"].get<std::string>().c_str();
						//Game.getClientInstance()->getGuiData()->displayClientMessageF(u8"%s[SimpleMod]用户 >> %s %s", GREEN, item["user"]["name"].get<std::string>().c_str(), item["user"]["user_id"].get<std::string>().c_str());
						if (calculateMD5(item["user"]["user_id"].get<std::string>() /*+ GetHwid()*/) == line) {
							Game.getClientInstance()->getGuiData()->displayClientMessageF("%s[SimpleMod]用户 >> %s", GREEN, item["user"]["name"].get<std::string>().c_str());
							expire_time = item["sponsor_plans"][0]["expire_time"].get<int>();
							return true;
						}
					}

				}
				else {
					Game.getClientInstance()->getGuiData()->displayClientMessageF("%s[ec]: %i", jsonResponse["ec"].get<int>());
					return false;
				}

			}
		}
		else {
			Game.getClientInstance()->getGuiData()->displayClientMessageF("%s[ec]: %i", jsonResponse["ec"].get<int>());
			return false;
		}
	}
	else {
		Game.getClientInstance()->getGuiData()->displayClientMessageF("%shwid已生成到目录下！", RED);
		std::ofstream outputFile("Hwid.txt");
		if (outputFile.is_open()) {
			//outputFile << GetHwid().c_str() << std::endl;
			outputFile.close();
		}
	}
	return false;
}
UserManager* User = new UserManager("76c659c0b43b11eea14352540025c377","vqSKa4hUYNkjF3VertdCJxfb8p5nmXwB");