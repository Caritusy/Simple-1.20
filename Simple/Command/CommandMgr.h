#pragma once

#include "../../Memory/GameData.h"

#include "Commands/IMCCommand.h"

#include <algorithm>
#include <string>
#include <vector>

class CommandMgr {
private:
	GameData* gameData;
	std::vector<IMCCommand*> commandList;

public:
	CommandMgr(GameData* gm);
	~CommandMgr();

	char prefix = '.';

	void initCommands();
	void disable();
	std::vector<IMCCommand*>* getCommandList();
	void execute(char* message);
	void onTick();
};

extern CommandMgr* cmdMgr;
