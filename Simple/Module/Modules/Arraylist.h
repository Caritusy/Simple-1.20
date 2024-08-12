#pragma once
#include "Module.h"
class Arraylist:public IModule{
public:
	bool clickToggle = true;
	float cycleSpeed = 2.f;
	float saturation = 0.5f;
	float offsetML = 0.5f;
	float rangeML = 0.5f;
	float alpha = 1.f;
	SettingEnum style = SettingEnum(this);

	Arraylist();
	~Arraylist();

	virtual const char* getModuleName();
	virtual const char* getRawModuleName();
	virtual void onPostRender();
};

