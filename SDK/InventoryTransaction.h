#pragma once
#include "../Utils/HMath.h"
#include "Inventory.h"
#include "Item.h"

enum InventorySourceType : int32_t {
	InvalidInventory = -1,
	ContainerInventory = 0,
	GlobalInventory = 1,
	WorldInteraction = 2,
	CreativeInventory = 3,
	// UntrackedInteractionUI = 100,
	NonImplementedFeatureTODO = 99999,
	EnchantStuff = 32766,
};

enum ContainerID : uint8_t {
	Invalid = 0xFF,
	inventory = 0,  // needs to be lower case bec stupidness
	First = 1,
	Last = 100,
	Offhand = 119,
	Armor = 120,
	SelectionSlots = 122,
	PlayerUIOnly = 124
};

enum InventorySourceFlags : int32_t {
	NoFlag = 0,
	WorldInteraction_Random = 1,
};

class InventoryTransaction
{
};

