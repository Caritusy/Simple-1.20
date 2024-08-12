#pragma once
#include "../../Utils/easylogging++.h"
#include "../../Utils/Json.hpp"
using json = nlohmann::json;
class UserManager{
private:
	std::string user;
	std::string tok;
private:
	long expire_time;
public:
	UserManager(std::string user,std::string tok);
	~UserManager();
	int getexpire_time() {return expire_time;}

	std::string getSignature(const json& params);
	std::string calculateMD5(const std::string& input);
	bool TimeAuth(long);
	bool FileAuth(std::string path="");
};
extern UserManager* User;