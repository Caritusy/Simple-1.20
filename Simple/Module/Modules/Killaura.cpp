#include "Killaura.h"


Killaura::Killaura() :IModule('R', Category::COMBAT, "Attacks entities around you automatically.") {
	registerBoolSetting("MultiAura", &isMulti, isMulti);
	registerBoolSetting("MobAura", &isMobAura, isMobAura);
	registerFloatSetting("Range", &range, range, 1.f, 20.f);
	registerIntSetting("Max CPS", &maxCPS, maxCPS, 1, 30);
	registerIntSetting("Min CPS", &minCPS, minCPS, 1, 30);
	registerBoolSetting("rotations", &rotations, rotations);
}

Killaura::~Killaura()
{
}

const char* Killaura::getModuleName()
{
	return ("Killaura");
}

const char* Killaura::getRawModuleName()
{
	return ("Killaura");
}
static std::vector<entity*> targetList;
void findEntity(entity* currentEntity, bool isRegularEntity) {
	static auto killauraMod = moduleMgr->getModule<Killaura>();

	if (currentEntity == nullptr)
		return;

	if (currentEntity == Game.getLocalPlayer())  // Skip Local player
		return;

	if (!Game.getLocalPlayer()->canAttack(currentEntity))
		return;

	if (!Game.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity->isAlive())
		return;

	if (currentEntity->getEntityTypeId() == 66) // falling block
		return;

	if (currentEntity->getEntityTypeId() == 69)  // XP
		return;

	if (killauraMod->isMobAura) {
		if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63)
			return;
		//if (currentEntity->aabb->size.y <= 0.01f || currentEntity->aabb->size.x <= 0.01f)  // Don't hit this pesky antibot on 2b2e.org
		//	return;
		if (currentEntity->getEntityTypeId() == 64) // item
			return;
		if (currentEntity->getEntityTypeId() == 80)  // Arrows
			return;
		if (currentEntity->getEntityTypeId() == 51) // NPC
			return;
	}
	else {
		if (!Target::isValidTarget(currentEntity))
			return;
	}

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	if (dist < killauraMod->range) {
		targetList.push_back(currentEntity);
	}
}

void Killaura::findWeapon()
{
}
void Killaura::onTick(GameMode* gm)
{
	targetListEmpty = targetList.empty();
	//Loop through all our players and retrieve their information
	targetList.clear();
	Game.forEachEntity(findEntity);
	if (!targetList.empty()) {
		std::sort(targetList.begin(), targetList.end(), [](const entity* lhs, const entity* rhs) {
			Vec3 localPlayerPos = *Game.getLocalPlayer()->getPos();
			entity* current = const_cast<entity*>(lhs);
			entity* other = const_cast<entity*>(rhs);
			return (*current->getPos()).dist(localPlayerPos) < (*other->getPos()).dist(localPlayerPos);
			});
		if (minCPS > maxCPS)
			minCPS = maxCPS;
		CPS = random(minCPS, maxCPS);
		if (CPSTime.hasTimedElapsed(1000.f / (float)CPS, true)) {
			if (isMulti) {
				for (auto& i : targetList) {
					if (!(i->damageTime > 1 && hurttime)) {
						Game.getLocalPlayer()->swing();
						Game.getGameMode()->attack(i);
					}
				}
			}
			else {
				if (!(targetList[0]->damageTime > 1 && hurttime)) {
					Game.getLocalPlayer()->swing();
					Game.getGameMode()->attack(targetList[0]);
				}
			}
		}
		if (rotations) {
			angle = Game.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());
			//	Game.getLocalPlayer()->setRot(angle);
		}
	}
}

void Killaura::onEnable()
{
	if (Game.getLocalPlayer() == nullptr)
		setEnabled(false);
	CPSTime.resetTime();
}

void Killaura::onSendPacket(Packet* packet){
	if (!targetList.empty()) {
		if (packet->isInstanceOf<PlayerAuthInputPacket>(AuthInputPacket)) {
			auto* authInputPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
			authInputPacket->pitch = angle.x;
			authInputPacket->yaw = angle.y;
			authInputPacket->InputAD = angle.x;
			authInputPacket->InputWS = angle.y;
		}
	}
}
