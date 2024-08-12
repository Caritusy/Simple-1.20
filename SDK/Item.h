#pragma once
#include <memory>

#include "../Utils/HMath.h"
#include "../Utils/Utils.h"
#include "TextHolder.h"

class CompoundTag;
class Tag;
class BlockLegacy;
class BlockSource;
class Block;
class Entity;
class ItemStack;
class ScreenContext;
class ItemRenderer;
class ItemInHandRenderer;
class ClientInstance;
class MinecraftGame;

class Item{
public:
	BUILD_ACCESS(this, TextHolder, rawName, 0xB0);
	BUILD_ACCESS(this, int16_t, maxStackSize, 0xDC);
	BUILD_ACCESS(this, int16_t, itemId, 0xE0);

};

class ItemStack {
private:
	uintptr_t** vTable;  //0x0000
	char pad_0x4[0x4];
public:
	Item** item;     //0x08
	//CompoundTag* tag;  //0x10
public:
	ItemStack() {
		memset(this, 0x0, sizeof(ItemStack));
	}

	ItemStack(BlockLegacy& legacy, int count) {
		memset(this, 0x0, sizeof(ItemStack));
		reinit(legacy, count);
	}

	ItemStack(Item& item, int count, int itemData) {
		memset(this, 0x0, sizeof(ItemStack));
		reinit(item, count, itemData);
	}

	ItemStack(ItemStack const& src);

	ItemStack(Tag const& tag);

	void fromTag(Tag const& tag);

	void save(CompoundTag** tag);

	void setUserData(std::unique_ptr<Tag> tag);

	bool isValid() {
		return this->item != nullptr && *this->item != nullptr;
	}

	inline Item* getItem() {
		return *this->item;
	}

	void reinit(BlockLegacy& legacy, int count);

	void reinit(Item& item, int count, int itemData);

	int getEnchantValue(int enchantId);

	bool isEnchanted() {
		int enchantValue = 0;
		for (int i = 0; i < 40; i++) {
			enchantValue = this->getEnchantValue(i);
		}
		if (enchantValue != 0)
			return true;
		else
			return false;
	}

	//float getArmorValueWithEnchants() {
	//	if (!this->item || !(*this->item)->isArmor())
	//		return 0;

	//	return (float)(((*this->item)->getArmorValue() + ((this->getEnchantValue(0) * 1.5f    // Protection
	//		+ this->getEnchantValue(5) * 0.4f  // Thorns
	//		+ this->getEnchantValue(3) * 0.4f  // Blast Protection
	//		+ this->getEnchantValue(1) * 0.4f  // Fire Protection
	//		+ this->getEnchantValue(4) * 0.4f  // Projectile Protection
	//		))));
	//}

	//float getAttackingDamageWithEnchants() {
	//	if (!this->item)
	//		return 0;
	//	int sharpnessValue = this->getEnchantValue(9);
	//	return (*this->item)->getAttackDamage() + 1.25f * sharpnessValue;
	//}

	void setShowPickUp(bool b) {
		*(bool*)(reinterpret_cast<__int32>(this) + 0x30) = b;
	}

	void setLore(std::string lore);

private:
	inline void setVtable(void);
};