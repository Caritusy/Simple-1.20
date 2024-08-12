#pragma once
#include "Module.h"
class GuiMod :public IModule {
public:
	GuiMod();
	~GuiMod();

	bool showTooltips = true;

	// Inherited via IModule
	//virtual void onPostRender(MinecraftUIRenderContext* renderCtx) override;
	virtual const char* getModuleName() override;
	virtual const char* getRawModuleName() override;
	virtual void onDisable() override;
	virtual void onEnable() override;
};

