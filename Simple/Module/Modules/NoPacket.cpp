#include "NoPacket.h"

NoPacket::NoPacket() : IModule(0, Category::MISC, "Prevents you from sending InventoryTransaction packets.") {
}

NoPacket::~NoPacket() {
}

const char* NoPacket::getModuleName() {
	return ("NoPacket");
}
const char* NoPacket::getRawModuleName()
{
	return ("NoPacket");
}
bool NoPacket::allowAutoStart() {
	return false;
}