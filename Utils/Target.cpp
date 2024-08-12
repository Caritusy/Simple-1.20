#include "Target.h"

#include <regex>
//#include "../Simple/FriendList/FriendsManager.h"

#include "../Simple/Module/ModuleManager.h"

Localplayer** localPlayer;

void Target::init(Localplayer** cl) {
	localPlayer = cl;
}
bool Target::isValidTarget(entity* ent) {
	auto localPlayer = Game.getLocalPlayer();
	if (ent == nullptr)
		return false;

	static auto antibot = moduleMgr->getModule<AntiBot>();

	if (!ent->isAlive())
		return false;

	if (ent == localPlayer)
		return false;

	auto entityTypeId = ent->getEntityTypeId();

	if (antibot->isEntityIdCheckEnabled() && entityTypeId <= 130 && entityTypeId != 63)
		return false;

	if (ent->isPlayer()) {
	}

	if (antibot->isInvisibleCheckEnabled() && ent->isInvisible())
		return false;

	if (antibot->isOtherCheckEnabled() && (ent->isSilent() || ent->getNameTag()->getTextLength() < 1 || std::string(ent->getNameTag()->getText()).find(std::string("\n")) != std::string::npos))
		return false;

	if (antibot->isExtraCheckEnabled() && !ent->canShowNameTag())
		return false;

//	if (!localPlayer->canAttack(ent))
	//	return false;

	return true;
}

bool Target::containsOnlyASCII(const std::string& string) {
	for (auto c : string) {
		int n = static_cast<unsigned char>(c);
		if (n > 127 && n != -89) {
			return false;
		}
	}
	return true;
}
