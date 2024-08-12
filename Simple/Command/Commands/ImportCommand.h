#pragma once
#include "IMCCommand.h"
#include "../../../Utils/TimerUtil.h"
class ImportCommand :public IMCCommand {
private:
	TimerUtil delayTime;
	float delay = 20.f;
	bool Import=false;
	bool command=false;
	CommandRequestPacket commandrequest;
	C_TextPacket Textpacket;
public:
	ImportCommand();
	~ImportCommand();
	virtual bool execute(std::vector<std::string>* args) override;
	virtual void onTick();
};

