#include "Item.h"
#include "../Memory/GameData.h"
#include "../Utils/Utils.h"
#include "Tag.h"

void ItemStack::setLore(std::string lore)
{
}

inline void ItemStack::setVtable(void){
	static uintptr_t sigOffset = GetOffsetFromSig("c7 06 ? ? ? ? e8 ? ? ? ? 6a ? 8b ce c6 45 ? ? c6 86",2);
	this->vTable = reinterpret_cast<uintptr_t**>(sigOffset);
}
