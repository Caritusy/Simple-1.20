#pragma once

#ifndef PERFORMANCE_TEST
//#define PERFORMANCE_TEST
#endif
#include "../Utils/easylogging++.h"
//#include "../include/safetyhook/safetyhook.hpp"

#include "../Utils/TextFormat.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <intrin.h>
//#include <entt/entity/entity.hpp>

#include <thread>
#include <unordered_map>
#include <vector>

#include <iostream>

#include "../Simple/Command/CommandMgr.h"
#include "../Simple/Config/ConfigManager.h"
#include "../Simple/Module/ModuleManager.h"
#include "../SDK/GameMode.h"
#include "../SDK/TextHolder.h"
#include "../Utils/TextFormat.h"
#include "../Utils/easylogging++.h"

#include "../Simple/Menu/Gui.h"

#include "GameData.h"
#include "MinHook.h"
#include <algorithm>
using namespace std;
class VMTHook;
class FuncHook;

class Hooks {
private:
	bool shouldRender = true;
public:

	char currentScreenName[100];

	std::vector<std::shared_ptr<FuncHook>> lambdaHooks;
    struct EntityListPointerHolder {
        entity* ent;
        int addedTick;
    };
    std::vector<EntityListPointerHolder> entityList;

	__int32 RMBManager = 0;
	bool shouldLocalPlayerBeImmobile = false;

	static void Init();
	static void Restore();
	static void Enable();
private:
	static void __fastcall ClientInstanceScreenModel_sendChatMessage(void* _this, uintptr_t edx, TextHolder* text);
	static void __fastcall onTick(uintptr_t* _this);
	static void _fastcall  KeyMapHookCallback(uintptr_t* _this, uintptr_t edx, unsigned char key, bool isDown);
	static float _fastcall  GetGamma(uintptr_t* _this);

	static void _fastcall LoopbackPacketSender_sendToServer(LoopbackPacketSender* a, uintptr_t edx, Packet* packet);
	static void __fastcall LoopbackPacketSender_sendToClient(class networkhandler* _this, uintptr_t edx, const void* networkIdentifier, Packet* packet);

	static void __fastcall GameMode_startDestroyBlock(GameMode* _this, uintptr_t edx, Vec3i* a2, uint8_t face, void* a4);
	static float __fastcall GameMode_getPickRange(GameMode* _this, uintptr_t edx, __int32 a2, char a3);
	static __int32 __fastcall GameMode_attack(GameMode* _this,uintptr_t edx, entity*);

	static void __fastcall Actor_baseTick(entity* _this);
	static void __fastcall Actor_normalTickTick(entity* _this);
	static void __fastcall Player_tickWorld(Player* _this,uintptr_t edx,__int32 a1);
	static void __fastcall Actor_lerpMotion(entity* _this,uintptr_t edx, Vec3);
	
	static BOOL __stdcall hkWGLSwapBuffers(HDC hdc);

	std::unique_ptr<FuncHook> oWGLSwapBuffers;

	std::unique_ptr<FuncHook> ClientInstanceScreenModel_sendChatMessageHook;
	std::unique_ptr<FuncHook> KeyMap;
	std::unique_ptr<FuncHook> GetGammaHook;
	std::unique_ptr<FuncHook> onTickHook;

	std::unique_ptr<FuncHook> LoopbackPacketSender_sendToServerHook;
	std::unique_ptr<FuncHook> LoopbackPacketSender_sendToClientHook;

	std::unique_ptr<FuncHook> GameMode_startDestroyBlockHook;
	std::unique_ptr<FuncHook> GameMode_getPickRangeHook;
	std::unique_ptr<FuncHook> GameMode_attackHook;

	std::unique_ptr<FuncHook> Actor_lerpMotionHook;
	std::unique_ptr<FuncHook> Actor_baseTickHook;
	std::unique_ptr<FuncHook> Actor_normalTickHook;
	std::unique_ptr<FuncHook> Player_tickWorldHook;
};


class FuncHook {
public:
	void* funcPtr;
	void* funcReal;

	FuncHook(void* func, void* hooked) {
		funcPtr = func;

		// Check if the function pointer is valid
		if (IsBadReadPtr(funcPtr, sizeof(funcPtr))) {
			//		cout<<"Invalid function pointer!"<<endl;
			return;
		}

		MH_STATUS ret = MH_CreateHook(func, hooked, &funcReal);
		if (ret == MH_OK && (__int32)func > 10) {
			// Hook created successfully
		}
		else {
			//		cout<<"MH_CreateHook "<<ret<<endl;
		}
	};

	FuncHook(uintptr_t func, void* hooked) {
		funcPtr = reinterpret_cast<void*>(func);

		// Check if the function pointer is valid
		if (IsBadReadPtr(funcPtr, sizeof(funcPtr))) {
			//		cout<<"Invalid function pointer!"<<endl;
			return;
		}

		MH_STATUS ret = MH_CreateHook(funcPtr, hooked, &funcReal);
		if (ret == MH_OK && (__int32)funcPtr > 10) {
		}
		else {
			//			cout << "MH_CreateHook " << ret << endl;
		}
	};

	void enableHook(bool enable = true) {
		if (funcPtr != nullptr) {
			int ret = enable ? MH_EnableHook(funcPtr) : MH_DisableHook(funcPtr);
			if (ret != MH_OK) {
				//	cout<<"MH_EnableHook"<< ret<<endl;
			}
		}
		else {
			//			cout<<"enableHook() called with nullptr func!"<<endl;
		}
	}
	~FuncHook() { Restore(); }
	// Restore the hook
	void Restore() {
		if (funcPtr != nullptr) {
			MH_STATUS ret = MH_DisableHook(funcPtr);
			if (ret != MH_OK) {
				//				cout<<"MH_DisableHook"<<ret<<endl;
			}
		}
	}
	// Get the original function pointer with fastcall calling convention
	template <typename TRet, typename... TArgs>

	inline auto* GetFastcall() {
		using Fn = TRet(__fastcall*)(TArgs...);
		return reinterpret_cast<Fn>(funcReal);
	};

	template <typename TRet, typename... TArgs>
	inline auto* Getstdcall() {
		using Fn = TRet(__stdcall*)(TArgs...);
		return reinterpret_cast<Fn>(funcReal);
	};
};

extern Hooks g_Hooks;
