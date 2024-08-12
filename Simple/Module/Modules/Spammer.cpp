#include "Spammer.h"
#include "../../../Utils/Utils.h"
#include "../../../Utils/network.h"

Spammer::Spammer() : IModule(0, Category::MISC, "Spams a message in a specified delay.") {
	registerFloatSetting("Delay", &delay, delay, 0, 500);
	registerIntSetting("Length", &length, length, 1, 60);
	registerBoolSetting("Bypass", &bypass, bypass);
	registerBoolSetting((const char*)u8"第五人格", &diwu, diwu);
}

Spammer::~Spammer()
{
}

void Spammer::onDisable()
{
}

void Spammer::onEnable()
{
}

const char* Spammer::getModuleName()
{
	return ("Spammer");
}

const char* Spammer::getRawModuleName()
{
	return ("Spammer");
}

void Spammer::onTick(GameMode* gm){
	if (delayTime.hasTimedElapsed(delay, true)) {
		if (message.empty()|| diwu) {
			if (delay < 100) delay = 100;
			message = Network::Request("http://api.akun666.top/API/emo.php");
		}

		textPacket.messageType = 1;
		textPacket.message.setText(bypass ? (message + " | " + Utils::randomString(length)) : message);
		textPacket.sourceName.setText(Game.getLocalPlayer()->getNameTag()->getText());
		Game.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
	}
}
