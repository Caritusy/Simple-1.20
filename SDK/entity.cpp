#include "entity.h"

void entity::displayClientMessageVA(const char* fmt, va_list lis){
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

void entity::displayClientMessageF(const char* fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);
	displayClientMessageVA(fmt, arg);
	va_end(arg);
}

void entity::displayClientMessageNoSendF(const char* fmt, ...){
	va_list arg;
	va_start(arg, fmt);
	displayClientMessageVA(fmt, arg);
	va_end(arg);
}

void entity::displayClientMessage(std::string* a2){
	TextHolder text = TextHolder(*a2);
	this->displayClientMessage(&text);
}

PlayerInventoryProxy* Player::getSupplies()
{
	return *reinterpret_cast<PlayerInventoryProxy**>(reinterpret_cast<__int64>(this) + 0x974);
}
