#include "Packet.h"

PlayerAuthInputPacket::PlayerAuthInputPacket()
{
	static uintptr_t** PlayerAuthInputPacketVtable = 0x0;
	if (PlayerAuthInputPacketVtable == 0x0) {
		PlayerAuthInputPacketVtable = (uintptr_t**)GetOffsetFromSig("c7 07 ? ? ? ? e8 ? ? ? ? 8b b7", 2);
#ifdef _DEBUG
		if (PlayerAuthInputPacketVtable == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(PlayerAuthInputPacket));
	vTable = PlayerAuthInputPacketVtable;
}

PlayerAuthInputPacket::PlayerAuthInputPacket(Vec3 pos, Localplayer* player)
{
	static uintptr_t** PlayerAuthInputPacketVtable = 0x0;
	if (PlayerAuthInputPacketVtable == 0x0) {
		PlayerAuthInputPacketVtable = (uintptr_t**)GetOffsetFromSig("c7 07 ? ? ? ? e8 ? ? ? ? 8b b7", 2);
#ifdef _DEBUG
		if (PlayerAuthInputPacketVtable == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(PlayerAuthInputPacket));
	vTable = PlayerAuthInputPacketVtable;
	this->pos = pos;
	/*this->pitch = player->pitch;
	this->yaw = player->yaw;
	this->yawUnused = player->yaw;
	this->onGround = true;
	this->InputAD = player->pitch;
	this->InputWS = player->yaw;*/
}

CommandRequestPacket::CommandRequestPacket()
{
	static uintptr_t** CommandRequestPacketVtable = 0x0;
	if (CommandRequestPacketVtable == 0x0) {
		CommandRequestPacketVtable = (uintptr_t**)GetOffsetFromSig("c7 06 ? ? ? ? e8 ? ? ? ? 8b cb", 2);
#ifdef _DEBUG
		if (CommandRequestPacketVtable == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(CommandRequestPacket));
	vTable = CommandRequestPacketVtable;
	version = 35;
}

CommandRequestPacket::CommandRequestPacket(std::string cmd)
{
	static uintptr_t** CommandRequestPacketVtable = 0x0;
	if (CommandRequestPacketVtable == 0x0) {
		CommandRequestPacketVtable = (uintptr_t**)GetOffsetFromSig("c7 06 ? ? ? ? e8 ? ? ? ? 8b cb", 2);
#ifdef _DEBUG
		if (CommandRequestPacketVtable == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(CommandRequestPacket));
	vTable = CommandRequestPacketVtable;
}

LevelSoundEventPacket::LevelSoundEventPacket()
{
	uintptr_t** LevelSoundEventVtable = 0x0;
	if (LevelSoundEventVtable == 0x0) {
		LevelSoundEventVtable = (uintptr_t**)GetOffsetFromSig("c7 06 ? ? ? ? c7 45 ? ? ? ? ? f3 0f ? ? 66 0f d6 46 ? 8b 40 ? 89 46", 2);
#ifdef _DEBUG
		if (LevelSoundEventVtable == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(LevelSoundEventPacket));
	vTable = LevelSoundEventVtable;
	this->entityType.setText("minecraft:player");
}

C_TextPacket::C_TextPacket()
{
	static uintptr_t** textPacketVtable = 0x0;
	if (textPacketVtable == 0x0) {
		textPacketVtable = (uintptr_t**)GetOffsetFromSig("c7 06 ? ? ? ? 88 46 ? e8 ? ? ? ? ff 75", 2);
#ifdef _DEBUG
		if (textPacketVtable == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(C_TextPacket));
	vTable = textPacketVtable;
	messageType = 1;  // TYPE_CHAT
}

TextHolder* Packet::getName(){
	return Utils::CallVFunc<2, TextHolder*>(this, new TextHolder());
}
