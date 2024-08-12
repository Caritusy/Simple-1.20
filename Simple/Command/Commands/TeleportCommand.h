#pragma once
#include "IMCCommand.h"
class TeleportCommand : public IMCCommand {
public:
	TeleportCommand();
	~TeleportCommand();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};
