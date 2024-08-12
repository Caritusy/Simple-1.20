#pragma once
#include "IMCCommand.h"
class BindCommand :public IMCCommand {
public:
	BindCommand();
	~BindCommand();

	virtual bool execute(std::vector<std::string>* args) override;
};

