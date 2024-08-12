#pragma once
#include "IMCCommand.h"
class PlaysoundCommand :public IMCCommand {
public:
	PlaysoundCommand();
	~PlaysoundCommand();

	virtual bool execute(std::vector<std::string>* args) override;
};

