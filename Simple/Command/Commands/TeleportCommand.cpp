#include "TeleportCommand.h"

TeleportCommand::TeleportCommand() : IMCCommand("tp", "Teleports to coordinates", "<X> <Y> <Z>") {
	registerAlias("teleport");
	registerAlias("setpos");
}
TeleportCommand::~TeleportCommand()
{
}

bool TeleportCommand::execute(std::vector<std::string>* args)
{
	assertTrue(Game.getLocalPlayer() != nullptr);
	assertTrue(args->size() >= 4);

	Vec3 pos;
	pos.x = assertFloat(args->at(1));
	pos.y = assertFloat(args->at(2)) + 1;
	pos.z = assertFloat(args->at(3));

	Game.getLocalPlayer()->chorusFruitTeleport(pos);
	clientMessageF("%sTeleported! X %f Y %f Z %f", GREEN, pos.x, pos.y, pos.z);
	return true;
}
