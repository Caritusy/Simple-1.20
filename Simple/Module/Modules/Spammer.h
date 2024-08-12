#pragma once
#include "Module.h"
#include "../ModuleManager.h"
#include "../../../Utils/TimerUtil.h"
class Spammer :public IModule {
private:
	float delay = 80.f;
	bool bypass = true;
	bool diwu = true;
	TimerUtil delayTime;
	int length = 10;
	std::string message ="";
	C_TextPacket textPacket;
public:
	Spammer();
	~Spammer();

	// Inherited via IModule
	virtual void onDisable() override;
	virtual void onEnable() override;
	virtual const char* getModuleName() override;
	virtual const char* getRawModuleName() override;
	virtual void onTick(GameMode* gm) override;
};

