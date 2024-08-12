#pragma once
#include "Item.h"
#include "../Utils/Utils.h"
#include <functional>

class Inventory
{
};

class PlayerInventoryProxy {
public:
	BUILD_ACCESS(this, int, selectedHotbarSlot, 0x8);
	BUILD_ACCESS(this, Inventory*, inventory, 0xC0);
};
