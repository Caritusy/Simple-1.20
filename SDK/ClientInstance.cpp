#include "ClientInstance.h"
#include <cstdarg>
//#include "../Utils/Logger.h"
#include "../Utils/easylogging++.h"
#include "../Utils/Utils.h"
#include "../Memory/GameData.h"

void GuiData::displayClientMessageVA(const char* fmt, va_list lis) {
	auto lengthNeeded = _vscprintf(fmt, lis) + 1;
	if (lengthNeeded >= 300) {
		LOG(INFO) << "A message that was %i characters long could not be fitted into the buffer" << lengthNeeded;
		return;
	}

	char message[300];
	vsprintf_s(message, 300, fmt, lis);
	std::string msg(message);
	displayClientMessage(&msg);
}

void GuiData::displayClientMessage(std::string* a2) {
//	using displayClientMessage = void(__thiscall*)(void*, TextHolder&, TextHolder&);
//	static displayClientMessage displayMessageFunc = reinterpret_cast<displayClientMessage>(FindSignature("55 8B EC 6A FF 68 ? ? ? ? 64 A1 00 00 00 00 50 81 EC 50 01 00 00 A1 ? ? ? ? 33 C5 89 45 F0 56 57 50 8D 45 F4 64 A3 00 00 00 00 89 8D 14"
//		/*"55 8b ec 6a ? 68 ? ? ? ? 64 a1 ? ? ? ? 50 81 ec ? ? ? ? a1 ? ? ? ? 33 c5 89 45 ? 53 56 57 50 8d 45 ? 64 a3 ? ? ? ? 8b d9 8b 7d ? 8d b3"*/));

	TextHolder text = TextHolder(*a2);
	Game.getLocalPlayer()->displayClientMessage(&text);

//	if (displayMessageFunc != nullptr)
//		displayMessageFunc(this, text, text);
}
void GuiData::displayClientMessageF(const char* fmt, ...) {
	va_list arg;
	va_start(arg, fmt);
	displayClientMessageVA(fmt, arg);
	va_end(arg);
}
void GuiData::displayClientMessageNoSendF(const char* fmt, ...) {
	va_list arg;
	va_start(arg, fmt);
	displayClientMessageVA(fmt, arg);
	va_end(arg);
}

