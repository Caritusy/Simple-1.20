#pragma once
#include "../Utils/HMath.h"
//#include "ComplexInventoryTransaction.h"
#include "entity.h"
#include "TextHolder.h"
class Packet
{
public:
	uintptr_t** vTable;  //0x0000
public:
	TextHolder* getName();
	template <class T>
	bool isInstanceOf(T& packet) {
		//T packet;
		if (packet.vTable == this->vTable)
			return true;
		else
			return false;
	}
};
class PlayerAuthInputPacket : public Packet {
public:
	PlayerAuthInputPacket();
	PlayerAuthInputPacket(Vec3 pos, Localplayer* player);
private:
	char pad_0x0[0x24];
public:
	float pitch;              //0x24
	float yaw;                //0x28
	Vec3 pos;
	float yawUnused;
	Vec3 Velocity;
	bool onGround;
	float InputAD;
	float InputWS;
};
class CommandRequestPacket : public Packet {

public:
	CommandRequestPacket();
	CommandRequestPacket(std::string cmd);
private:
	char pad_0x0[0x24];
public:
	TextHolder command;
private:
	char pad[0x34];
public:
	int version;
};
class LevelSoundEventPacket : public Packet {
private:
	char pad_0x4[0x24];
public:
	int sound;           //0x28
	Vec3 pos;          //0x2C
	int extraData = -1;  //0x38
private:
	int unknown = 0;  //0x3C
public:
	TextHolder entityType;               //0x40
	bool isBabyMod = false;              //0x60
	bool disableRelativeVolume = false;  //0x61
	LevelSoundEventPacket();
};
class C_TextPacket : public Packet {
private:
	char pad_0x4[0x24];
public:
	C_TextPacket();

	unsigned __int8 messageType;  // 0x28
	TextHolder sourceName;           // 0x30
	TextHolder message;              // 0x50
	unsigned char field_24222[24];   // 0x70
	bool translationNeeded = false;  // 0x88

	unsigned char ga2p[7];  // 0x89
	TextHolder xboxUserId;
	TextHolder platformChatId;
};
class AnimatePacket : public Packet {
public:
	AnimatePacket();
	AnimatePacket(int action, __int32 entityRuntimeID, float rowingTime);

	__int32 entityId;
	int action;
	float rowingTime;
};
class PlayerActionPacket : public Packet {
private:
	char pad_0[0x24];
public:
	PlayerActionPacket();

	Vec3i blockPosition;    // 0x28
	int face;                 // 0x34
	int action;               // 0x38
	__int32 entityRuntimeId;  // 0x40
};