#include "UserCommand.h"
#include "../../../Utils/Json.hpp"
#include "../../../Utils/TimerUtil.h"
#include "../../../Utils/network.h"
#include "../../User/UserManager.h"

using json = nlohmann::json;
UserCommand::UserCommand() :IMCCommand("user", (const char*)u8"查询你的信息.", (const char*)u8"<ping/order(订单查询)/sponsor(赞助名单)/\"我要赞助\"> <user_id/\"all\"/user>") {
}

UserCommand::~UserCommand() {
}

bool UserCommand::execute(std::vector<std::string>* args) {
	assertTrue(args->size() > 1);
	std::string option = args->at(1);
	std::transform(option.begin(), option.end(), option.begin(), ::tolower);
	if (option == "ping") {
		json params = { {"page", 1} };
		std::string result = Network::Request("http://afdian.net/api/open/ping",User->getSignature(params));
		json jsonResponse = json::parse(result);
		clientMessageF("%sping >> %s", jsonResponse["ec"] == 200 ? GREEN : RED, jsonResponse["ec"] == 200 ? "[OK]" : "[NO]");
		return true;
	}
	else if (option == "order") {
		if (args->at(2) == "all") {
			clientMessageF((const char*)u8"%s因为用户隐私,暂时不展示.", RED);
			return true;
		}
		else {
			json params = { {"page", 1} };
			std::string result = Network::Request("http://afdian.net/api/open/query-order", User->getSignature(params));
			json jsonResponse = json::parse(result);
			if (jsonResponse["ec"] == 200) {
				json dataList = jsonResponse["data"]["list"];
				for (auto& item : dataList) {
					if (item["user_id"] == args->at(2)) {
						clientMessageF((const char*)u8"%s[SimpleMod] %s订单号 >> %s", GOLD, GREEN, item["out_trade_no"].get<std::string>().c_str());
						clientMessageF((const char*)u8"%s[SimpleMod] %s用户ID >> %s", GOLD, GREEN, item["user_id"].get<std::string>().c_str());
						clientMessageF((const char*)u8"%s[SimpleMod] %s赞助数量 >> %d", GOLD, GREEN, item["month"].get<int>());
						clientMessageF((const char*)u8"%s[SimpleMod] %s交易状态 >> %s", GOLD, GREEN, item["status"] == 2 ? "[YES]" : "[NO]");
						clientMessageF((const char*)u8"%s[SimpleMod] %s留言 >> %s", GOLD, GREEN, item["remark"].get<std::string>().c_str());
					}
				}
			}
			clientMessageF("%sresult >> %d", jsonResponse["ec"] != 200 ? RED : GREEN, jsonResponse["ec"].get<int>());
			return true;
		}
	}
	else if (option == "sponsor") {
		if (args->at(2) == "all") {
			json params = { {"page", 1} };
			std::string result = Network::Request("http://afdian.net/api/open/query-sponsor", User->getSignature(params));
			json jsonResponse = json::parse(result);
			if (jsonResponse["ec"] == 200) {
				int e = 1;
				for (int i = 0;i < jsonResponse["data"]["total_count"].get<int>();e++) {
					json parameter = { {"page", e} };
					std::string results = Network::Request("http://afdian.net/api/open/query-sponsor", User->getSignature(params));
					json Response = json::parse(results);
					if (Response["ec"] == 200) {
						json dataList = Response["data"]["list"];
						i += dataList.size();
						clientMessageF("===================================================");
						for (auto& item : dataList) {
							clientMessageF((const char*)u8"%s[SimpleMod]发电用户 >> %s", GREEN, item["user"]["name"].get<std::string>().c_str());
							clientMessageF((const char*)u8"%s[SimpleMod] %s 赞助项目 >> %s", GREEN, item["user"]["name"].get<std::string>().c_str()
								, item["current_plan"]["name"].get<std::string>().c_str());
							clientMessageF((const char*)u8"%s[SimpleMod] %s 捐赠总金额 >> %s", GREEN, item["user"]["name"].get<std::string>().c_str(),
								item["all_sum_amount"].get<std::string>().c_str());
#ifdef _DEBUG
							clientMessageF((const char*)u8"%s[SimpleMod] user_id >> %s", GREEN, item["user"]["user_id"].get<std::string>().c_str());
#endif // _DEBUG
						}
						clientMessageF("===================================================");
						clientMessageF((const char*)u8"%s[SimpleMod] 捐赠人数>> %d", GREEN, jsonResponse["data"]["total_count"].get<int>());
						return true;

					}
					else {
						Game.getClientInstance()->getGuiData()->displayClientMessageF("%s[ec]: %i", jsonResponse["ec"].get<int>());
						return false;
					}
				}
		
			}
		}
		else {
				json params = { {"page", 1} };
				std::string result = Network::Request("http://afdian.net/api/open/query-sponsor", User->getSignature(params));
				json jsonResponse = json::parse(result);
				if (jsonResponse["ec"] == 200) {
					int e = 1;
					for (int i = 0;i < jsonResponse["data"]["total_count"].get<int>();e++) {
						json parameter = { {"page", e} };
						std::string results = Network::Request("http://afdian.net/api/open/query-sponsor", User->getSignature(params));
						json Response = json::parse(results);
						if (Response["ec"] == 200) {
							json dataList = Response["data"]["list"];
							i += dataList.size();
							for (auto& item : dataList) {
								if (item["user"]["user_id"] == args->at(2)) {
									clientMessageF((const char*)u8"%s[SimpleMod] Name >> %s", GREEN, item["user"]["name"].get<std::string>().c_str());
									clientMessageF((const char*)u8"%s[SimpleMod] 赞助项目名 >> %s", GREEN, item["current_plan"]["name"].get<std::string>().c_str());
									clientMessageF((const char*)u8"%s[SimpleMod] 赞助项目金额 >> %s", GREEN, item["current_plan"]["price"].get<std::string>().c_str());
									clientMessageF((const char*)u8"%s[SimpleMod] 赞助总金额 >> %s", GREEN, item["all_sum_amount"].get<std::string>().c_str());
								}
							}
						
						}
						else {
							Game.getClientInstance()->getGuiData()->displayClientMessageF("%s[ec]: %i", jsonResponse["ec"].get<int>());
							return false;
						}

					
					}
				
				}
				//clientMessageF("%sresult >> %d", jsonResponse["ec"] != 200 ? RED : GREEN, jsonResponse["ec"].get<int>());
				return true;
			}
	}
	else if (option == (const char*)u8"我要赞助") {
		if (args->size() >= 2) {
			if (assertInt(args->at(2)) <= 0) {
				clientMessageF((const char*)u8"%s[SimpleMod] >> %s私宅没实力让想让我倒贴%i! 地址: https://afdian.net/a/QwQLL ", GOLD, GREEN, assertInt(args->at(2)));
				ShellExecuteA(NULL, "open", "https://afdian.net/a/QwQLL", NULL, NULL, SW_SHOWNORMAL);
				//ShellExecuteA(NULL, "open", "https://www.bilibili.com/video/BV1cD421j7RC/?share_source=copy_web&vd_source=49b39132845192c29c7ee48e34be3a36", NULL, NULL, SW_SHOWNORMAL);
				return true;
			}
			else if (assertInt(args->at(2)) >= 100) {
				clientMessageF((const char*)u8"%s[SimpleMod] >> %s私宅有实力!你真会捐赠这么%i多吗？ 地址: https://afdian.net/a/QwQLL ", GOLD, GREEN, assertInt(args->at(2)));
				ShellExecuteA(NULL, "open", "https://afdian.net/a/QwQLL", NULL, NULL, SW_SHOWNORMAL);
				//ShellExecuteA(NULL, "open", "https://v3-weba.douyinvod.com/7c2587233fd960d53c0e496760065db8/66487f87/video/tos/cn/tos-cn-ve-15c001-alinc2/oAH9NAzBI9IAxfeyzMlPLQDAgIyMBgEEDlGnhY/?a=6383&ch=11&cr=3&dr=0&lr=all&cd=0%7C0%7C0%7C3&cv=1&br=969&bt=969&cs=0&ds=4&ft=inKH6BoHUUmfzPdFg02D1YZMfxiXVT1JxVJEjUx62bPD-Ipz&mime_type=video_mp4&qs=0&rc=ZjhpOjxlZmhlODplOTdpOUBpMzg8Ozk6ZjpocjMzNGkzM0AtYGEwYy0vX18xMDNiNF4uYSMxZTMzcjRnXzNgLS1kLTBzcw%3D%3D&btag=c0000e00018000&cquery=101n_100B_100x_100z_100o&dy_q=1716023641&feature_id=46a7bb47b4fd1280f3d3825bf2b29388&l=20240518171401C1C2EF5051CFA0904060", NULL, NULL, SW_SHOWNORMAL);
				return true;
			}
		}
		clientMessageF((const char*)u8"%s[SimpleMod] >> %s私宅有实力! 地址: https://afdian.net/a/QwQLL ", GOLD, GREEN);
		ShellExecuteA(NULL, "open", "https://afdian.net/a/QwQLL", NULL, NULL, SW_SHOWNORMAL);
		return true;
	}
	return true;
	}