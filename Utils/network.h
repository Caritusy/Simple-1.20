#pragma once
#include "../Utils/easylogging++.h"
#include "../Utils/Json.hpp"
class Network{
public:
	static std::string Request(const std::string& api, const std::string& additionalParams = "");
};

