#pragma once
#include "IMCCommand.h"
class HelpCommand : public IMCCommand {
public:
	HelpCommand();
	~HelpCommand();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};
