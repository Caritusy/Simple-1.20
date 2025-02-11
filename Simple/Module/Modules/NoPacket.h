#pragma once

#include "Module.h"

class NoPacket : public IModule {
public:
	NoPacket();
	~NoPacket();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual const char* getRawModuleName() override;
	bool allowAutoStart() override;
	
};
