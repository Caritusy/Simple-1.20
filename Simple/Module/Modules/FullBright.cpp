#include "FullBright.h"

FullBright::FullBright() : IModule(0, Category::VISUAL, "Puts your gamma to max.") {
	registerFloatSetting("Gamma", &intensity, intensity, -25.f, 25.f);
}

FullBright::~FullBright()
{
}
float originalGamma = -1;

void FullBright::onTick(GameMode* gm) {
	if (gammaPtr != nullptr && *gammaPtr != 10)
		*gammaPtr = 10;
}

void FullBright::onEnable() {
	if (gammaPtr != nullptr) {
		originalGamma = *gammaPtr;
		*gammaPtr = 10;
	}
}

void FullBright::onDisable() {
	if (gammaPtr != nullptr) {
		if (originalGamma >= 0 && originalGamma <= 1)
			*gammaPtr = originalGamma;
		else
			*gammaPtr = 0.5f;
	}

}

const char* FullBright::getModuleName()
{
	return "Fullbright";
}

const char* FullBright::getRawModuleName()
{
	return "Fullbright";
}