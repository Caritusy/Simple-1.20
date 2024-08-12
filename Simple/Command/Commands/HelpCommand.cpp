#include "HelpCommand.h"
#include "../CommandMgr.h"
#include "../../Module/ModuleManager.h"
HelpCommand::HelpCommand() : IMCCommand("help", "Lists all commands", "") {
	registerAlias("h");
}

HelpCommand::~HelpCommand()
{
}

bool HelpCommand::execute(std::vector<std::string>* args)
{
	auto lock = moduleMgr->lockModuleList();
	std::vector<std::shared_ptr<IModule>>* modules = moduleMgr->getModuleList();
	clientMessageF("%sCLIENT:", GREEN);
	for (auto& mod : *modules) {
		if (mod->getCategory() == Category::CLIENT) {
			clientMessageF("%s[SimpleMod]%s >> %s %s- %s%s", GOLD, mod->isEnabled() ? GREEN : WHITE, mod->getRawModuleName(), GRAY, ITALIC, mod->getTooltip());
		}
	}
	clientMessageF("%sMisc:", GREEN);
	for (auto& mod : *modules) {
		if (mod->getCategory() == Category::MISC) {
			clientMessageF("%s[SimpleMod]%s >> %s %s- %s%s", GOLD, mod->isEnabled() ? GREEN : WHITE, mod->getRawModuleName(), GRAY, ITALIC, mod->getTooltip());
		}
	}
	clientMessageF("%sVISUAL:", GREEN);
	for (auto& mod : *modules) {
		if (mod->getCategory() == Category::VISUAL) {
			clientMessageF("%s[SimpleMod]%s >> %s %s- %s%s", GOLD, mod->isEnabled() ? GREEN : WHITE, mod->getRawModuleName(), GRAY, ITALIC, mod->getTooltip());
		}
	}
	clientMessageF("%sWORLD:", GREEN);
	for (auto& mod : *modules) {
		if (mod->getCategory() == Category::WORLD) {
			clientMessageF("%s[SimpleMod]%s >> %s %s- %s%s", GOLD, mod->isEnabled() ? GREEN : WHITE, mod->getRawModuleName(), GRAY, ITALIC, mod->getTooltip());
		}
	}
	clientMessageF("%sMOVEMENT:", GREEN);
	for (auto& mod : *modules) {
		if (mod->getCategory() == Category::MOVEMENT) {
			clientMessageF("%s[SimpleMod]%s >> %s %s- %s%s", GOLD, mod->isEnabled() ? GREEN : WHITE, mod->getRawModuleName(), GRAY, ITALIC, mod->getTooltip());
		}
	}
	clientMessageF("%sPLAYER:", GREEN);
	for (auto& mod : *modules) {
		if (mod->getCategory() == Category::PLAYER) {
			clientMessageF("%s[SimpleMod]%s >> %s %s- %s%s", GOLD, mod->isEnabled() ? GREEN : WHITE, mod->getRawModuleName(), GRAY, ITALIC, mod->getTooltip());
		}
	}
	clientMessageF("%sCOMBAT:", GREEN);
	for (auto& mod : *modules) {
		if (mod->getCategory() == Category::COMBAT) {
			clientMessageF("%s[SimpleMod]%s >> %s %s- %s%s", GOLD, mod->isEnabled() ? GREEN : WHITE, mod->getRawModuleName(), GRAY, ITALIC, mod->getTooltip());
		}
	}

	clientMessageF("===================================== %sModule[%i]", GRAY, modules->size());
	std::vector<IMCCommand*>* commandList = cmdMgr->getCommandList();
	for (auto it = commandList->begin(); it != commandList->end(); ++it) {
		IMCCommand* command = *it;
		clientMessageF("%s[SimpleMod] %s >> %s%s - %s%s", GOLD, WHITE, command->getCommand(), GRAY, ITALIC, command->getDescription());
	}
	return true;
}
