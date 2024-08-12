#include "GameModeCommand.h"

GameModeCommand::GameModeCommand() : IMCCommand("gamemode", "Changes the local player's gamemode", "<number>") {
	registerAlias("gm");
}

GameModeCommand::~GameModeCommand() {
}

bool GameModeCommand::execute(std::vector<std::string>* args) {
	assertTrue(Game.getLocalPlayer() != nullptr);
	assertTrue(args->size() > 1);
	int gamemode = assertInt(args->at(1));
	if (gamemode >= 0 && gamemode <= 6) {
		Game.getLocalPlayer()->setPlayerGameType(gamemode);
		clientMessageF("[%sSimpleMod%s] %sGameMode changed!", GOLD, WHITE, GREEN);
		return true;
	}

	clientMessageF("[%sSimpleMod%s] %sInvalid GameMode!", GOLD, WHITE, RED);
	return true;
}
