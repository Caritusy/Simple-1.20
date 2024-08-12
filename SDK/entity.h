#pragma once
#include "../Utils/easylogging++.h"
#include <bitset>
#include "../Utils/HMath.h"
#include "../Utils/Utils.h"
#include "BlockLegacy.h"
#include "TextHolder.h"
#include "EntityId.h"
#include "Inventory.h"
#include "InventoryTransaction.h"

class GameMode;
class Level {
public:
	char pad_0x0[0xA58];
private:
	int rayHitType;  // 0x9f4
	int blockSide;   // 0x9f8
	Vec3i block;     // 0xA08
	Vec3 rayHitVec;  // 0xC04
};
class EntityLocation {  //this+0x288
public:
	Vec3 posPrev;
	Vec3 pos;
	Vec3 velocity;
};
class EntityRotation {
public:
	Vec2 rotPrev;
	Vec2 rot;
};

class EntityRegistry;

class EntityContext {
public:
	// EntityRegistry& mRegistry;
	entt::basic_registry<EntityId>& mEnttRegistry;
	EntityId mEntity;

	[[nodiscard]] inline entt::basic_registry<EntityId>& getRegistry()
	{
		return mEnttRegistry;
	}

	[[nodiscard]] inline entt::basic_registry<EntityId> const& getRegistry() const
	{
		return mEnttRegistry;
	}
};
class IPlayerMovementProxy {};
struct MobEffectInstance;
class Player;
class  {
public:
};

class entity {
public:
	uintptr_t** vtable;
	EntityContext mEntityContext; //this+4
	//private:
	//	char pad_4[0x170];
	//public:
	//	bool isGround;   //this+178
	//private:
	//	char pad_178[0x110];
	//public:
	//	AABB* aabb;  //28C
	//	EntityLocation* location;  //290
	//	EntityRotation* rotation; //29+
	//

	BUILD_ACCESS(this, int32_t, ticksAlive, 0x1B8);
	BUILD_ACCESS(this, int16_t, damageTime, 0x1BC);
	BUILD_ACCESS(this, bool, isGround, 0x170);
	BUILD_ACCESS(this, Level*, level, 0x25C);
	BUILD_ACCESS(this, AABB*, aabb, 0x28C);
	BUILD_ACCESS(this, EntityLocation, location, 0x290);
	BUILD_ACCESS(this, EntityRotation, rotation, 0x294);

public:
	template <typename T>
	const T* tryGetComponent() const
	{
		const auto& registry = mEntityContext.getRegistry();
		return registry.try_get<T>(mEntityContext.mEntity);
	}
	template <typename T>
	T* tryGetComponent()
	{
		auto& registry = mEntityContext.getRegistry();
		return registry.try_get<T>(mEntityContext.mEntity);
	}

public:
	virtual void function_0();   // 0
	virtual void function_1();   // 1
	virtual void function_2();   // 2
	virtual void function_3();   // 3
	virtual void function_4();   // 4
	virtual void function_5();   // 5
	virtual void function_6();   // 6
	virtual void function_7();   // 7
	virtual void function_8();   // 8
	virtual void function_9();   // 9
	virtual void function_10();   // 10
	virtual void function_11();   // 11
	virtual void function_12();   // 12
	virtual void function_13();  // 13
	virtual void function_14();   // 14
	virtual void function_15();  // 15
	virtual void function_16();   // 16
	virtual void function_17();   // 17
	virtual void function_18();   // 18
	virtual void function_19();   // 19
	virtual void function_20();   // 20
	virtual void function_21();   // 21
	virtual void function_22();   // 22
public:
	virtual int getPredictedMovementValues(void);  // 23
	virtual Vec3* getPos(void);// 24
	virtual Vec3* getPosOld(void);  // 25
	virtual float getPosExtrapolated(float);  // 26
private:
	virtual void function_27();   // 27
	virtual void function_28();   // 28
	virtual int setRot(Vec2 const&);   // 29
	virtual void function_30();   // 30
	virtual void function_31();   // 31
	virtual void function_32();   // 32
	virtual void function_33();   // 33
	virtual void function_34();   // 34
	virtual void function_35();   // 35
public:
	virtual void updateEntityInside(AABB const&);  // 36
	virtual bool isFireImmune(void);   // 37
	virtual void blockedByShield(__int32 const&, entity&); // 38
	virtual void canDisableShield(void);  // 39
	virtual void teleportTo(Vec3 const&, bool, int, int, bool);   // 40
	virtual void tryTeleportTo(Vec3 const&, bool, bool, int, int);  // 41
	virtual void chorusFruitTeleport(Vec3 const&);   // 42
	virtual void lerpMotion(Vec3 const&); //43
	virtual void tryCreateAddEntityPacket(void); //44
	virtual void normalTick(void); //45
	virtual void baseTick(void); // 46
	virtual void passengerTick(void);  // 47
	virtual void positionPassenger(entity&, float);//48
	virtual void startRiding(entity&); //49
	virtual void addPassenger(entity&);  // 50
	virtual void flagPassengerToRemove(entity&); // 51
	virtual int getExitTip(std::string const&, __int32, __int32);   // 52
	virtual int getEntityLocNameString(void);  // 53
	virtual void intersects(Vec3 const&, Vec3 const&);   // 54
	virtual bool isInWall(void);  // 55
	virtual bool isInvisible(void);  // 56
	virtual bool canShowNameTag(void);  // 57
	virtual void setNameTagVisible(bool); // 58
	virtual TextHolder* getNameTag(void);  // 59
	virtual int getSeasons(void);   // 60
	virtual TextHolder* getFormattedNameTag(void);   // 61
	virtual void filterFormattedNameTag(__int32 const&); // 62
	virtual void setNameTag(std::string const&);  // 63
	virtual void setScoreTag(std::string const&);  // 64
	virtual int getScoreTag(void);  // 65
	virtual bool isInWater(void);  // 66
	virtual bool isUnderLiquid(__int32);  // 67
	virtual void setBlockMovementSlowdownMultiplier(BlockLegacy const&, Vec3 const&);   // 68
	virtual void resetBlockMovementSlowdownMultiplier(void); // 69
	virtual int getCameraOffset(void); // 70
	virtual int getShadowHeightOffs(void);  // 71
	virtual int getShadowRadius(void);  // 72
	virtual float getHeadLookVector(float);     // 73
	virtual void canSee(entity const&);    // 74
	virtual void canSee(Vec3 const&);  // 75
	virtual void canInteractWithOtherEntitiesInGame(void);// 76
	virtual bool isSkyLit(void);   // 77
	virtual float getBrightness(float, __int32 const&);  // 78
	virtual void onAboveBubbleColumn(bool);   // 79
	virtual void onInsideBubbleColumn(bool);  // 80
	virtual bool isImmobile(void); // 81
	virtual bool isSilent(void);  // 82
	virtual void _doSprintParticleEffect(void);   // 83
	virtual bool isPickable(void);   // 84
	virtual bool isFishable(void);  // 85
	virtual bool isSleeping(void); // 86
	virtual void setSleeping(bool);  // 87
	virtual bool isShootable(void);   // 88
	virtual void setSneaking(bool);   // 89
	virtual bool isBlocking(void); // 90
	virtual bool isDamageBlocked(__int32 const&);   // 91
	virtual bool isAlive(void); // 92
private:
	virtual void function_93();   // 93
	virtual void function_94();   // 94
public:
	virtual bool isCreativeModeAllowed(void);  // 95
	virtual bool isSurfaceEntity(void);// 96
	virtual bool isTargetable(void);   // 97
	virtual bool isLocalPlayer(void);  // 98
	virtual bool isRemotePlayer(void); // 99
	virtual bool isPlayer(void); // 100
	virtual bool isAffectedByWaterBottle(void);  // 101
	virtual bool canAttack(entity*); // 102
	virtual void setTarget(entity*); // 103
	virtual bool isValidTarget(entity*); // 104
	virtual void attack(entity&, __int32 const&); // 105
	virtual void performRangedAttack(entity&, float);// 106
	virtual int getEquipmentCount(void);// 107
	virtual void setOwner(uint32_t);  // 108
	virtual void setSitting(bool); // 109
	virtual void __onTame(void); // 110
	virtual void __onFailedTame(void); // 111
	virtual int getInventorySize(void);// 112
	virtual int getEquipSlots(void);  // 113
	virtual int getChestSlots(void); // 114
	virtual void setStanding(bool);  // 115
	virtual void canPowerJump(void);  // 116
	virtual void setCanPowerJump(bool); // 117
	virtual bool isEnchanted(void); // 118
private:
	virtual void function_119();  // 119
public:

	virtual void shouldRender(void);  // 120
	virtual void playAmbientSound(void);// 121
	virtual int getAmbientSound(void); // 122
	virtual bool isInvulnerableTo(__int64 const&); // 123
private:
	virtual void function_124();  // 124
public:
	virtual void animateHurt(void);  // 125
private:
	virtual void function_126();  // 126
	virtual void function_127();  // 127
	virtual void function_128();  // 128
public:
	virtual void handleEntityEvent(__int64, int); // 129
	virtual int getPickRadius(void);// 130
	virtual int getEntityRendererId(void);// 131
	virtual void spawnAtLocation(int, int);// 132
	virtual void spawnAtLocation(int, int, float); // 133
	virtual void spawnAtLocation(ItemStack const&, float); // 134
	virtual void despawn(void);  // 135
	virtual void killed(entity&);  // 136
	virtual void awardKillScore(entity&, int);// 137
	virtual void setArmor(int, ItemStack const&); // 138
	virtual ItemStack* getArmor(int);// 139
	virtual int getAllArmor(void); // 140
	virtual int getArmorMaterialTypeInSlot(int); // 141
	virtual int getArmorMaterialTextureTypeInSlot(int); // 142
	virtual int getArmorColorInSlot(int, int);  // 143
	virtual int getEquippedSlot(int);  // 144
	virtual void setEquippedSlot(int, ItemStack const&); // 145
private:
	virtual void function_146();  // 146
	virtual void function_147();  // 147
public:
	virtual void setOffhandSlot(ItemStack const*);  // 148
	virtual ItemStack* getEquippedTotem(void);  // 149
	virtual void consumeTotem(void);  // 150
	virtual void save(CompoundTag*); // 151
	virtual void saveWithoutId(CompoundTag&);  // 152
	virtual void load(CompoundTag const&, __int32&);  // 153
	virtual void loadLinks(CompoundTag const&, std::vector<__int32>&, __int32&); // 154
	virtual int getEntityTypeId(void);	// 155
	virtual void queryEntityRenderer(void);  // 156
	virtual int __getSourceUniqueID(void);  // 157
	virtual void thawFreezeEffect(void);  // 158
	virtual void canFreeze(void);  // 159
	virtual bool isWearingLeatherArmor(void);  // 160
	virtual int getLiquidAABB(__int32);  // 161
	virtual void handleInsidePortal(Vec3i const&); // 162
	virtual int getPortalCooldown(void); //163
	virtual int getPortalWaitTime(void);  // 164
	virtual void canChangeDimensionsUsingPortal(void);  // 165
	virtual void changeDimension(class Dimension*, int);  // 166
	virtual void changeDimension(__int32 const&); // 167
	virtual int getControllingPlayer(void);	  // 168
private:
	virtual void function_169();  // 169
	virtual void function_170();  // 170
	virtual void function_171();  // 171
	virtual void function_172();  // 172
	virtual void function_173();  // 173
public:
	virtual void checkFallDamage(float, bool);  // 174
	virtual void causeFallDamage(float, float, __int32);  // 175
	virtual void handleFallDistanceOnServer(float, float, bool);  // 176
	virtual void playSynchronizedSound(__int32, Vec3 const&, Block const&, bool);
	virtual void playSynchronizedSound(__int32, Vec3 const&, int, bool);  // 178
private:
	virtual void function_179();  // 179
public:
	virtual void onSynchedFlagUpdate(int, long, long);  //180
	virtual void onSynchedDataUpdate(int); // 181
	virtual void canAddPassenger(entity&); // 182
	virtual void canPickupItem(ItemStack const&); // 183
	virtual void canBePulledIntoVehicle(void);  //184
	virtual void inCaravan(void);  //185
	virtual bool isLeashableType(void);  //186
	virtual void tickLeash(void);  //187
	virtual void sendMotionPacketIfNeeded(void);  //188
	virtual void canSynchronizeNewEntity(void);  //189
	virtual void stopRiding(bool, bool, bool);  //190
	virtual void startSwimming(void);  //191
	virtual void stopSwimming(void);  //192
	virtual void buildDebugInfo(std::string&);   //193
	virtual int getCommandPermissionLevel(void);  //194
	virtual bool isClientSide(void);  //195
	virtual class AttributeInstance* getMutableAttribute(class Attribute* Attribute);  //196
	virtual class AttributeInstance* getAttribute(class Attribute* Attribute);  //197
	virtual int getDeathTime(void);  //198
	virtual void heal(int);  //199
	virtual bool isInvertedHealAndHarm(void);  //200
	virtual void canBeAffected(int);  //201
	virtual void canBeAffectedByArrow(MobEffectInstance const&);  //202
	virtual void onEffectAdded(MobEffectInstance&);  //203
	virtual void onEffectUpdated(MobEffectInstance&);  //204
	virtual void onEffectRemoved(MobEffectInstance&);  //205
	virtual void canObstructSpawningAndBlockPlacement(void);   //206
	virtual int getAnimationComponent(void);  //207
	virtual void openContainerComponent(Player&);  //208
	virtual void swing(void);  //209
	virtual void useItem(ItemStack&, __int32, bool);  //210
	virtual void hasOutputSignal(char);  //211
	virtual int getOutputSignal(void);  //212
	virtual int getDebugText(std::vector<std::string>&);  //213
	virtual int getMapDecorationRotation(void);   //214
	virtual int getPassengerYRotation(entity const&);  //215
	virtual void add(ItemStack&);  //216
	virtual void drop(ItemStack const&, bool);  //217
	virtual int getInteraction(Player&, __int32&, Vec3 const&);  //218
	virtual void canDestroyBlock(Block const&);  //219
	virtual void setAuxValue(int);  //220
	virtual void setSize(float, float);  //221
	virtual void onOrphan(void);  //222
	virtual void wobble(void);  //223
	virtual void wasHurt(void);  //224
	virtual void startSpinAttack(void);  //225
	virtual void stopSpinAttack(void);  //226
	virtual void setDamageNearbyEntitys(bool); // 227
	virtual void reloadLootTable(void);  //228
	virtual void reloadLootTable(__int32 const&);  //229
	virtual int getDeletionDelayTimeSeconds(void); // 230
	virtual void kill(void);  //231
	virtual void die(__int32 const&); // 232
	virtual void shouldDropDeathLoot(void); // 233
private:
	virtual void function_234();  // 234
	virtual void function_235();  // 235
	virtual void function_236();  // 236
	virtual void function_237();  // 237
	virtual void function_238();  // 238
	virtual void function_239();  // 239
	virtual void function_240();  // 240
	virtual void function_241();  // 241
	virtual void function_242();  // 242
	virtual void function_243();  // 243
	virtual void function_244();  // 244
	virtual void function_245();  // 245
	virtual void function_246();  // 246
	virtual void function_247();  // 247
	virtual void function_248();  // 248
	virtual void function_249();  // 249
	virtual void function_250();  // 250
	virtual void function_251();  // 251
	virtual void function_252();  // 252
	virtual void function_253();  // 253
	virtual void function_254();  // 254
	virtual void function_255();  // 255
	virtual void function_256();  // 256
	virtual void function_257();  // 257
	virtual void function_258();  // 258
	virtual void function_259();  // 259
	virtual void function_260();  // 260
	virtual void function_261();  // 261
	virtual void function_262();  // 262
	virtual void function_263();  // 263
	virtual void function_264();  // 264
public:
	virtual void _doAutoAttackOnTouch(entity&);  // 265
	virtual void knockback(entity*, int, float, float, float, float, float);  // 266
	virtual void __spawnAnim(void);  // 267
	virtual void setSprinting(bool);  //268
	virtual int getHurtSound(void);// 269
	virtual int getDeathSound(void); // 270
	virtual float getSpeed(void);
	virtual void setSpeed(float); // 272
private:
	virtual void function_273();  // 273
	virtual void function_274();  // 274
	virtual void function_275();  // 275
	virtual void function_276();  // 276
	virtual void function_277();  // 277
	virtual void function_278();  // 278
	virtual void function_279();  // 279
	virtual void function_280();  // 280
	virtual void function_281();  // 281
	virtual void function_282();  // 282
	virtual void function_283();  // 283
	virtual void function_284();  // 284
	virtual void function_285();  // 285
	virtual void function_286();  // 286
	virtual void function_287();  // 287
	virtual void function_288();  // 288
	virtual void function_289();
	virtual void function_290();  // 290
	virtual void function_291();  // 291
	virtual void function_292(void);  // 292
	virtual void function_293(void);       // 293
	virtual void function_294(void);    // 294
	virtual void function_295();  // 295
	virtual void function_296();  // 296
	virtual void function_297();  // 297
	virtual void function_298();  // 298
	virtual void function_299();  // 299
	virtual void function_300();  // 300
	virtual void function_301();  // 301
	virtual void function_302();  // 302
	virtual void function_303();  // 303
	virtual void function_304();  // 304
	virtual void function_305();  // 305
	virtual void function_306();  // 306
	virtual void function_307();  // 307
	virtual void function_308();  // 308
	virtual void function_309();  // 309
	virtual void function_310();  // 310
	virtual void function_311();  // 311
	virtual void function_312();  // 312
	virtual void function_313();  // 313
	virtual void function_314();  // 314
	virtual void function_315();  // 315
	virtual void function_316();  // 316
	virtual void function_317();  // 317
	virtual void function_318();  // 318
	virtual void function_319();  // 319
	virtual void function_320();  // 320
	virtual void function_321();  // 321
	virtual void function_322();  // 322
	virtual void function_323();  // 323
	virtual void function_324();  // 324
	virtual void function_325();  // 325
	virtual void function_326();  // 326
	virtual void function_327();  // 327
	virtual void function_328();  // 328
	virtual void function_329();  // 329
	virtual void function_330();  // 330
	virtual void function_331();  // 331
	virtual void function_332();  // 332
	virtual void function_333();  // 333
	virtual void function_334();  // 334
	virtual void function_335();  // 335
	virtual void function_336();  // 336
	virtual void function_337();  // 337
	virtual void function_338();  // 338
	virtual void function_339();  // 339
public:
	virtual void _fireWillChangeDimension(void);  //340
	virtual void _fireDimensionChanged(void);  // 341
	virtual void changeDimensionWithCredits(class Dimension, int);  // 342
private:
	virtual void function_343();  // 343
public:
	virtual void tickWorld(__int32 const&);  // 344
private:
	virtual void function_345();  // 345
	virtual void function_346();  // 346
	virtual void function_347();  // 347
	virtual void function_348();  // 348
	virtual void function_349();  // 349
	virtual void function_350();  // 350
	virtual void function_351();  // 351
	virtual void function_352();  // 352
	virtual void function_353();  // 353
public:
	virtual int getTravelledMethod(void); // 354
	virtual void checkMovementStats(Vec3 const&); // 355
	virtual int getCurrentStructureFeature(void);  // 356
	virtual bool isAutoJumpEnabled(void);  // 357
	virtual void respawn(void);  // 358
	virtual void resetRot(void);  // 359
	virtual bool isInTrialMode(void); // 360
	virtual void hasResource(int);  // 361
	virtual void completeUsingItem(void); // 362
	virtual void startDestroying(void);  // 363
	virtual void stopDestroying(void);  // 364
	virtual void openPortfolio(void); // 365
	virtual void openBook(int, bool, int, class BlockActor*);  // 366
	virtual void openTrading(uint32_t const&, bool); // 367
	virtual bool canOpenContainerScreen(void); // 368
	virtual void openChalkboard(__int32&, bool);  // 369
private:
	virtual void function_370();  // 370
public:
	virtual void openInventory(void); // 371
private:
	virtual void function_372();  // 372
public:
	virtual void displayClientMessage(TextHolder*);  // 373
	virtual void displayTextObjectMessage(__int64 const&, std::string const&, std::string const&); // 374
private:
	virtual void function_375();  // 375
	virtual void function_376();  // 376
public:
	virtual void displayWhisperMessage(std::string const&, std::string const&, std::string const&, std::string const&); // 377
	virtual void startSleepInBed(Vec3i const&);  //378
	virtual void stopSleepInBed(bool, bool); // 379
	virtual void canStartSleepInBed(void); // 380
	virtual int getSleepTimer(void); // 381
	virtual int getPreviousTickSleepTimer(void); // 382
	virtual void openSign(Vec3i const&, bool);// 383
	virtual void playEmote(std::string const&, bool);  //384
	virtual bool isHostingPlayer(void);  // 385
	virtual bool isLoading(void);  //386
	virtual bool isPlayerInitialized(void);   //387
	virtual void stopLoading(void);  //388
	virtual void registerTrackedBoss(uint64_t);  //389
	virtual void unRegisterTrackedBoss(uint64_t);// 390
	virtual void setPlayerGameType(int);  // 391
	virtual void initHUDContainerManager(void);  // 392
	virtual void _crit(entity&); // 393
	virtual int getEventing(void); // 394
	virtual int getUserId(void); // 395
	virtual void sendEventPacket(__int32&);// 396
private:
	virtual void function_397();  // 397
	virtual void function_398();  // 398
	virtual void function_399();  // 399
	virtual void function_400();  // 400
	virtual void function_401();  // 401
	virtual void function_402(int, bool, int, __int32*);                                               //402
	virtual void function_403();  // 403
	virtual void function_404(void); // 404
	virtual void function_405();  // 405
	virtual void function_406();  // 406
	virtual void function_407();  // 407
	virtual void function_408();  // 408
	virtual void function_409();      // 409
	virtual void function_410();  // 410
	virtual void function_411();  // 411
	virtual void function_412();  // 412
	virtual void function_413();  // 413
	virtual void function_414();  // 414
	virtual void function_415(void);                                                                  // 415
	virtual void function_416(void);    //416
	virtual void function_417(Vec3 const&);           // 417
	virtual void function_418(std::string);  // 418
	virtual void function_419(void);   // 419
	virtual void function_420(void);        // 420
	virtual void function_421();  // 421
	virtual void function_422();  // 422
	virtual void function_423();  // 423
	virtual void function_424();  // 424
	virtual void function_425();  // 425
public:
	void displayClientMessageVA(const char* fmt, va_list lis);

	void displayClientMessageF(const char* fmt, ...);
	void displayClientMessageNoSendF(const char* fmt, ...);
	void displayClientMessage(std::string* a2);

	Level* getlevel() {
		return *reinterpret_cast<class Level**>(reinterpret_cast<__int64>(this) + 0x25C);
	}

	IPlayerMovementProxy* getMovementProxy() {
		using getMovementProxySharedPtr = void(__fastcall*)(entity*, std::shared_ptr<void>*);
		static getMovementProxySharedPtr getMovementProxySharedPtrFunc = reinterpret_cast<getMovementProxySharedPtr>(FindSignature("55 8b ec 83 ec ? 53 56 8b f1 57 8b 46 ? 8b 08 8b 46 ? 51 8b d4 89 02 e8 ? ? ? ? 8d 4d ? 51 8b c8 e8 ? ? ? ? 8b 78 ? 8b 10 c7 00 ? ? ? ? c7 40 ? ? ? ? ? 8b 45 ? 8d 4f ? c7 00 ? ? ? ? c7 40 ? ? ? ? ? 85 ff 74 ? f0 ff ? 89 10 89 78 ? 85 d2 74 ? 83 cb ? 85 ff 74 ? 8b c3 f0 0f ? ? 75 ? 8b 07 8b 30 8b ce ff 15 ? ? ? ? 8b cf ff d6 8b c3 f0 0f c1 47 ? 75 ? 8b 07 8b 70 ? 8b ce ff 15 ? ? ? ? 8b cf ff d6 8b 7d ? 85 ff 74 ? 8b c3 f0 0f c1 47 ? 75 ? 8b 07 8b 30 8b ce ff 15 ? ? ? ? 8b cf ff d6 f0 0f c1 5f ? 4b 75 ? 8b 17 8b 72 ? 8b ce ff 15 ? ? ? ? 8b cf ff d6 8b 45 ? 5f 5e 5b 8b e5 5d c2 ? ? e8 ? ? ? ? cc cc cc cc cc cc cc cc cc cc cc cc cc cc cc cc 55 8b ec 8b c1"));

		std::shared_ptr<void> ptr;
		getMovementProxySharedPtrFunc(this, &ptr);
		return reinterpret_cast<IPlayerMovementProxy*>(ptr.get());
	}
};

class Player : public entity {
public:
	PlayerInventoryProxy* getSupplies();
};

class Localplayer : public Player {
public:
	GameMode* GetGamemode() {
		return *reinterpret_cast<GameMode**>((uintptr_t)(this) + 0x11D4);
	}
};