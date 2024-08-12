#pragma once
#include "IMCCommand.h"
class GameModeCommand : public IMCCommand {
public:
	GameModeCommand();
	~GameModeCommand();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};
