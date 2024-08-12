#include "NoWeb.h"


NoWeb::NoWeb() : IModule(0, Category::MOVEMENT, "Ignore cobwebs slowdown.") {
}


NoWeb::~NoWeb()
{
}

const char* NoWeb::getModuleName()
{
	return ("NoWeb");
}

const char* NoWeb::getRawModuleName()
{
	return ("NoWeb");
}

void NoWeb::onTick(GameMode* gm){
	Game.getLocalPlayer()->resetBlockMovementSlowdownMultiplier();
}
