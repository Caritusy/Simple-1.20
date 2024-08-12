#pragma once
#include "IMCCommand.h"
class UserCommand:public IMCCommand{
public:
	UserCommand();
	~UserCommand();

	virtual bool execute(std::vector<std::string>* args) override;
};

