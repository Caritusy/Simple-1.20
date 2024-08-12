#include "GuiMod.h"
GuiMod::GuiMod():IModule(VK_F6, Category::CLIENT, "The Gui - toggle everything just by clicking on it!") {
}

GuiMod::~GuiMod(){
}

const char* GuiMod::getModuleName()
{
    return ("Gui");
}

const char* GuiMod::getRawModuleName()
{
    return ("Gui");
}

void GuiMod::onDisable()
{
}

void GuiMod::onEnable()
{
}
