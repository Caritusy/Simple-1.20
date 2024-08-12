#include "HudModule.h"
#include "../../../Utils/DrawUtils.h"
#include "../ModuleManager.h"
//#include "../../../Utils/ClientColors.h"


HudModule::HudModule() : IModule(0, Category::CLIENT, "Displays things like the ArrayList/TabGUI.") {
	registerBoolSetting("TabGui", &tabgui, tabgui);
	registerBoolSetting("ClickToggle", &clickToggle, clickToggle);
	registerBoolSetting("Watermark", &watermark, watermark);
	registerBoolSetting("Coordinates", &coordinates, coordinates);
	registerBoolSetting("Show Keybinds", &keybinds, keybinds);
	registerBoolSetting("Show ArmorHUD", &displayArmor, displayArmor);
	registerBoolSetting("Keystrokes", &keystrokes, keystrokes);
	registerBoolSetting("Show FPS", &fps, fps);
	registerBoolSetting("Show CPS", &cps, cps);
	registerBoolSetting("Always show", &alwaysShow, alwaysShow);
	registerFloatSetting("Scale", &scale, scale, 0.5f, 1.5f);
}


HudModule::~HudModule()
{
}

const char* HudModule::getModuleName()
{
    return "HUB";
}

const char* HudModule::getRawModuleName()
{
    return "HUB";
}

void HudModule::onPostRender()
{
}

void HudModule::drawKeystroke(char key, const Vec2& pos)
{
}

void HudModule::drawMouseKeystroke(Vec2 pos, std::string keyString)
{
}
