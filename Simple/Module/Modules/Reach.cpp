#include "Reach.h"

#include <Windows.h>

#include "../../../Utils/Utils.h"

Reach::Reach() : IModule(0, Category::COMBAT, "Increases your reach.") {
	type.addEntry(EnumEntry("Signature", 0)).addEntry(EnumEntry("Offset", 1));
	registerEnumSetting("Mode", &type, 0);
	registerFloatSetting("Reach Value", &reachValue, reachValue, 3.f, 7.f);
}

Reach::~Reach() {
}

const char* Reach::getModuleName() {
	return ("Reach");
}

const char* Reach::getRawModuleName()
{
	return ("Reach");
}

void Reach::onTick(GameMode* gm) {
	if (reachPtr != 0 && type.selected == 0) {
		*reachPtr = reachValue;
	}
}

void Reach::onEnable() {
	if (type.selected == 0) {
		static uintptr_t sigOffset = 0x0;
		if (sigOffset == 0x0) {
			sigOffset = GetOffsetFromSig("F3 0F 10 05 ? ? ? ? F3 0F 10 8D ? ? ? ? 0F 2F C8 76",4);

			if (sigOffset != 0x0) {
				reachPtr = reinterpret_cast<float*>(sigOffset);
				originalReach = *reachPtr;
			}
		}
		if (!VirtualProtect(reachPtr, sizeof(float), PAGE_EXECUTE_READWRITE, &oldProtect)) {
#ifdef _DEBUG
			LOG(DEBUG)<<"couldnt unprotect memory send help";
			__debugbreak();
#endif
		}
	}
	else {
		uintptr_t reachOff = Utils::getBase() + 0x4632170; // Reach offset

		unsigned char arr[4];

		memcpy(arr, &reachValue, sizeof(float));
		PatchBytes((BYTE*)reachOff, (BYTE*)arr, 4);
	}
}

void Reach::onDisable() {
	if (type.selected == 0) {
		*reachPtr = originalReach;
		if (reachPtr != 0)
			VirtualProtect(reachPtr, sizeof(float), oldProtect, &oldProtect);
	}
}
