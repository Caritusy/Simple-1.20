#pragma once

#include "Module.h"
#include "../ModuleManager.h"
#include "../../../Utils/Target.h"
#include "../../../Utils/TimerUtil.h"
class Killaura : public IModule
{
private:
	bool isMulti = true;
	int delay = 0;
	int Odelay = 0;
	int CPS = 5;
	int maxCPS = 20;
	int minCPS = 20;
	TimerUtil CPSTime;

	bool autoweapon = false;
	void findWeapon();
	bool silent = true;
	PlayerAuthInputPacket AuthInputPacket;
public:
	bool rotations = false;
	bool targetListEmpty = false;
	Vec2 angle;
	bool isMobAura = false;
	bool hurttime = true;
	float range = 6;


	Killaura();
	~Killaura();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual const char* getRawModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onSendPacket(Packet* packet) override;
};