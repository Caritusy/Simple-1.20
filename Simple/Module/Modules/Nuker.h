#pragma once

#include "Module.h"

class Nuker : public IModule {
private:
	int delay = 0;
	int nukerRadius = 7;
	bool veinMiner = false;
	bool autodestroy = false;

public:
	Nuker();
	~Nuker();

	inline bool isAutoMode() { return autodestroy; };
	int getNukerRadius() { return nukerRadius; };
	inline bool isVeinMiner() { return veinMiner; };

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual const char* getRawModuleName() override;
	virtual void onTick(GameMode* gm) override;
};
