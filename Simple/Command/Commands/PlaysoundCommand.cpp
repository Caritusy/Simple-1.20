#include "PlaysoundCommand.h"
#include "../../Module/ModuleManager.h"

PlaysoundCommand::PlaysoundCommand() :IMCCommand("playsound", "Play a sound effect.", "<Music ID>") {
}

PlaysoundCommand::~PlaysoundCommand()
{
}

bool PlaysoundCommand::execute(std::vector<std::string>* args)
{
	assertTrue(Game.getLocalPlayer() != nullptr);
	assertTrue(args->size() > 1);
	static LevelSoundEventPacket playsound;
	playsound.sound = assertInt(args->at(1));
	playsound.pos = *Game.getLocalPlayer()->getPos();
	Game.getClientInstance()->loopbackPacketSender->sendToServer(&playsound);
	return true;
}
