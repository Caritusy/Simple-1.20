#pragma once
#include "../Utils/easylogging++.h"
//#include "../Utils/Logger.h"

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

#include "../Memory/MinHook.h"

#include "../Utils/DrawUtils.h"
#include "../Memory/GameData.h"
#include "../Memory/Hooks.h"
#include "../SDK/ClientInstance.h"
#include "../SDK/Entity.h"
#include "../SDK/GameMode.h"
#include "../SDK/Packet.h"
#include "../Utils/HMath.h"
#include "../Utils/Utils.h"
#include "../Utils/Target.h"
#include "../Utils/TextFormat.h"
#include "Module/ModuleManager.h"
#include "Command/CommandMgr.h"
#include "Config/ConfigManager.h"
class Loader {
public:
	static bool isRunning;
};

