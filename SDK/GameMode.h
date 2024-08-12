#pragma once

#include <stdint.h>

#include "../Utils/HMath.h"
#include "ClientInstance.h"
#include "Entity.h"

class GameMode {
private:
	virtual __int32 destructorGameMode();
	// Duplicate destructor
public:
	virtual __int32 startDestroyBlock(Vec3i const& pos, unsigned char blockSide, bool& isDestroyedOut);
	virtual __int32 destroyBlock(Vec3i*, unsigned char, bool);
	virtual __int32 continueDestroyBlock(Vec3i const&, unsigned char blockSide, bool& isDestroyedOut);
	virtual __int32 stopDestroyBlock(Vec3i const&);
	virtual __int32 startBuildBlock(Vec3i const&, unsigned char);
	virtual __int32 buildBlock(Vec3i*, unsigned char, bool);
	virtual __int32 continueBuildBlock(Vec3i const&, unsigned char);
	virtual __int32 stopBuildBlock(void);
	virtual __int32 tick(void);

public:
	virtual __int32 getPickRange(__int32 const&, bool);
	virtual __int32 useItem(ItemStack&);
	virtual void useItemOn(ItemStack&, Vec3i const&, char, Vec3i const&,class Block const*);
	virtual __int32 interact(entity&, Vec3 const&);

public:
	virtual __int32 attack(entity*);

public:
	virtual __int32 releaseUsingItem(void);

public:
	virtual void setTrialMode(bool);
	virtual bool isInTrialMode(void);

private:
	virtual __int32 registerUpsellScreenCallback(__int32);

public:
	Player* player;

	void survivalDestroyBlockHack(Vec3i const& block, int face, bool& isDestroyedOut, bool isFirst);
};