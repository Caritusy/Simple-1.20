
#include "Hooks.h"
#include <windows.h>
#include <algorithm>
#include <iomanip>
#include "../Utils/Utils.h"
#include "../Simple/Loader.h"
using namespace std;

Hooks g_Hooks;
void Hooks::Init() {
	LOG(INFO) << "Setting up Hooks...";
	{	
		uintptr_t _sendChatMessage = FindSignature(XorString("55 8b ec 6a ? 68 ? ? ? ? 64 a1 ? ? ? ? 50 81 ec ? ? ? ? a1 ? ? ? ? 33 c5 89 45 ? 53 56 57 50 8d 45 ? 64 a3 ? ? ? ? 8b c1 89 85 ? ? ? ? 8b 78 ? 8d 58"));
		g_Hooks.ClientInstanceScreenModel_sendChatMessageHook = std::make_unique<FuncHook>(_sendChatMessage, Hooks::ClientInstanceScreenModel_sendChatMessage);
		uintptr_t keyMap =FindSignature(XorString("55 8b ec 8b 4d ? 83 ec ? 85 c9 78"));
		g_Hooks.KeyMap = std::make_unique<FuncHook>(keyMap, Hooks::KeyMapHookCallback);
		uintptr_t fullbright = FindSignature(XorString("55 8b ec 51 56 57 8b f9 8d 45 ? 80 bf ? ? ? ? ? 8b 37 8b 76 ? 8b ce 74 ? 68 ? ? ? ? 50 ff 15 ? ? ? ? 8b cf ff d6 8b 08 85 c9 74 ? e8 ? ? ? ? 5f 5e 8b e5 5d c3 6a ? eb ? e8 ? ? ? ? cc cc cc cc cc cc cc cc cc cc cc 55 8b ec 51 56"));
		g_Hooks.GetGammaHook = std::make_unique<FuncHook>(fullbright, Hooks::GetGamma);
		uintptr_t ontick = FindSignature(XorString("56 57 8b f9 68 ? ? ? ? 8b 07 8b b0 ? ? ? ? 8b ce ff 15 ? ? ? ? 8b cf ff d6 8b c8 e8 ? ? ? ? 51 d9 1c ? e8 ? ? ? ? 83 c4 ? 5f 5e c3 cc cc cc cc cc cc cc cc cc cc cc cc cc 8d 81"));
		g_Hooks.onTickHook = std::make_unique<FuncHook>(ontick, Hooks::onTick);

		if (GetModuleHandleA("opengl32.dll")) {
			uintptr_t oWGLSwapBuffers = (uintptr_t)GetProcAddress(GetModuleHandleA("opengl32.dll"), "wglSwapBuffers");
			if (oWGLSwapBuffers == 0x0)
				LOG(INFO) << "oWGLSwapBuffers  signature not working!!!";
			else {
			//	g_Hooks.oWGLSwapBuffers = std::make_unique<FuncHook>(oWGLSwapBuffers, Hooks::hkWGLSwapBuffers);
			}
		}

		// Vtables
		{
			if (Game.getClientInstance()->loopbackPacketSender != nullptr) {
				uintptr_t** packetSenderVtable = reinterpret_cast<uintptr_t**>(*(uintptr_t*)Game.getClientInstance()->loopbackPacketSender);
				if (packetSenderVtable == nullptr)
					LOG(INFO) << "LoopbackPacketSenderVtable is invalid";
				else {
					g_Hooks.LoopbackPacketSender_sendToServerHook = std::make_unique<FuncHook>(packetSenderVtable[2], Hooks::LoopbackPacketSender_sendToServer);
				    g_Hooks.LoopbackPacketSender_sendToClientHook = std::make_unique<FuncHook>(packetSenderVtable[4], Hooks::LoopbackPacketSender_sendToClient); //I use the second sendToClient
				}
			}

			if (Game.getClientInstance()->getCILocalPlayer() != nullptr) {
				uintptr_t** localPlayerVtable = reinterpret_cast<uintptr_t**>(*(uintptr_t*)Game.getClientInstance()->getCILocalPlayer());
				if (localPlayerVtable == 0x0)
					LOG(INFO) << "LocalPlayer signature not working!!!";
				else {
				//	g_Hooks.Actor_lerpMotionHook = std::make_unique<FuncHook>(localPlayerVtable[43], Hooks::Actor_lerpMotion);
					g_Hooks.Actor_normalTickHook = std::make_unique<FuncHook>(localPlayerVtable[45], Hooks::Actor_normalTickTick);
					g_Hooks.Actor_baseTickHook = std::make_unique<FuncHook>(localPlayerVtable[46], Hooks::Actor_baseTick);
					g_Hooks.Player_tickWorldHook = std::make_unique<FuncHook>(localPlayerVtable[344], Hooks::Player_tickWorld);


				}LOG(DEBUG) << "localPlayerVtable: " << std::hex << localPlayerVtable;

				uintptr_t** gameModeVtable = reinterpret_cast<uintptr_t**>(*(uintptr_t*)Game.getClientInstance()->getCILocalPlayer()->GetGamemode());
				if (gameModeVtable == 0x0)
					LOG(INFO) << "GameMode signature not working!!!";
				else {
					LOG(DEBUG) << "gameModeVtable: " << std::hex << gameModeVtable;

					g_Hooks.GameMode_startDestroyBlockHook = std::make_unique<FuncHook>(gameModeVtable[1], Hooks::GameMode_startDestroyBlock);

					g_Hooks.GameMode_getPickRangeHook = std::make_unique<FuncHook>(gameModeVtable[10], Hooks::GameMode_getPickRange);

					g_Hooks.GameMode_attackHook = std::make_unique<FuncHook>(gameModeVtable[14], Hooks::GameMode_attack);
				}
			}
		}
	}
	LOG(INFO) << "Hooks initialized";
}

void Hooks::Restore() {
	MH_DisableHook(MH_ALL_HOOKS);
	LOG(INFO) << "DisableHook";
	Sleep(10);
}

void Hooks::Enable() {

	LOG(INFO) << "Hooks enabled";
	MH_EnableHook(MH_ALL_HOOKS);
	Game.getClientInstance()->getGuiData()->displayClientMessageF((const char*)u8"%s[SimpleMod] >> 加载成功 ✓", GREEN);
	Game.getClientInstance()->getGuiData()->displayClientMessageF((const char*)u8"%s[SimpleMod] >> 交流群: 320443172 & bug反馈|建议:Developer-QwQ@outlook.com", GREEN);
}

BOOL __stdcall Hooks::hkWGLSwapBuffers(HDC hdc)
{
	static auto oWGLSwapBuffers = g_Hooks.oWGLSwapBuffers->Getstdcall<BOOL, HDC>();
	GuiData* dat = Game.getClientInstance()->getGuiData();
	DrawUtils::setCtx(dat);
	opengl::init(hdc);
	return oWGLSwapBuffers(hdc);
}

void _fastcall Hooks::LoopbackPacketSender_sendToServer(LoopbackPacketSender* a, uintptr_t edx, Packet* packet)
{
	static auto oFunc = g_Hooks.LoopbackPacketSender_sendToServerHook->GetFastcall<void, LoopbackPacketSender*, uintptr_t, Packet*>();

	static auto noPacketMod = moduleMgr->getModule<NoPacket>();

	if (noPacketMod->isEnabled())
		return;

	moduleMgr->onSendPacket(packet);

	oFunc(a,edx, packet);
}

void __fastcall Hooks::LoopbackPacketSender_sendToClient(networkhandler* _this, uintptr_t edx, const void* networkIdentifier, Packet* packet)
{
	auto func = g_Hooks.LoopbackPacketSender_sendToClientHook->GetFastcall<void, networkhandler*, uintptr_t, const void*, Packet*>();

	moduleMgr->onSendClientPacket(packet);

	func(_this,edx, networkIdentifier, packet);
}

void __fastcall Hooks::ClientInstanceScreenModel_sendChatMessage(void* _this, uintptr_t edx, TextHolder* text){
	static auto oSendMessage = g_Hooks.ClientInstanceScreenModel_sendChatMessageHook->GetFastcall<void, void*, uintptr_t, TextHolder*>();

	if (text->getTextLength() <= 0)
		return oSendMessage(_this,edx, text);

	auto message = text->getText();
	if (*message == cmdMgr->prefix) {
		cmdMgr->execute(message);
		return;
	}
	else if (*message == '.') {
		static std::once_flag flag;
		std::call_once(flag, [] {
			Game.getClientInstance()->getGuiData()->displayClientMessageF("%sYour SimpleMod prefix is: \"%s%c%s\"", RED, YELLOW, cmdMgr->prefix, RED);
			Game.getClientInstance()->getGuiData()->displayClientMessageF("%sEnter \"%s%cprefix .%s\" to reset your prefix", RED, YELLOW, cmdMgr->prefix, RED);
			});
	}
	return oSendMessage(_this,edx, text);
}

void __fastcall Hooks::onTick(uintptr_t* _this){
	static auto oTick = g_Hooks.onTickHook->GetFastcall<void, uintptr_t*>();
	GameMode* gm = Game.getLocalPlayer()->GetGamemode();
	if (gm != nullptr) moduleMgr->onTick(gm);
	oTick(_this);
//	GameData::EntityList_tick(_this);
}

void _fastcall Hooks::KeyMapHookCallback(uintptr_t* _this, uintptr_t edx, unsigned char key, bool isDown){
	static auto oFunc = g_Hooks.KeyMap->GetFastcall<void, uintptr_t*, uintptr_t, unsigned char, bool>();
	bool shouldCancel = false;
	GameData::keys[key] = isDown;
	moduleMgr->onKey((int)key, isDown, shouldCancel);
	moduleMgr->onKeyUpdate((int)key, (isDown && GameData::canUseMoveKeys()));
	//LOG(INFO) << "key: " << (int)key<<" canUseMoveKeys: " << GameData::canUseMoveKeys() << "isDown: " << isDown;
	if (shouldCancel) return;
	return oFunc(_this, edx, key, isDown);
}

float _fastcall Hooks::GetGamma(uintptr_t* a1){
	static auto ofunc = g_Hooks.GetGammaHook->GetFastcall<float, uintptr_t*>();
	static auto fullbright = moduleMgr->getModule<FullBright>();
	if (fullbright->isEnabled())
		return fullbright->intensity;


	return ofunc(a1);
}

void __fastcall Hooks::GameMode_startDestroyBlock(GameMode* _this, uintptr_t edx, Vec3i* a2, uint8_t face, void* a4)
{
	static auto oFunc = g_Hooks.GameMode_startDestroyBlockHook->GetFastcall<void, GameMode*, uintptr_t, Vec3i*, uint8_t, void*>();

	static auto nukerModule = moduleMgr->getModule<Nuker>();

	if (nukerModule->isEnabled()) {
		Vec3i tempPos;
		int range = nukerModule->getNukerRadius();
		const bool isVeinMiner = nukerModule->isVeinMiner();
		const bool isAutoMode = nukerModule->isAutoMode();
		//BlockSource* region = Game.getLocalPlayer()->region;
		//auto selectedBlockId = ((region->getBlock(*a2)->blockLegacy))->blockId;
	//	uint8_t selectedBlockData = region->getBlock(*a2)->data;
		if (!isAutoMode) {
			for (int x = -range; x < range; x++) {
				for (int y = -range; y < range; y++) {
					for (int z = -range; z < range; z++) {
						tempPos.x = a2->x + x;
						tempPos.y = a2->y + y;
						tempPos.z = a2->z + z;
						if (tempPos.y > -64) {
							//Block* blok = region->getBlock(tempPos);
							//	uint8_t data = blok->data;
							//	auto id = blok->blockLegacy->blockId;
							//	if (blok->blockLegacy->material->isSolid == true && (!isVeinMiner || (id == selectedBlockId && data == selectedBlockData)))
							_this->destroyBlock(&tempPos, face,1);
							//}
						}
					}
				}
			}
		}
	return;
	}
	oFunc(_this, edx, a2, face, a4);
}
float __fastcall Hooks::GameMode_getPickRange(GameMode* _this, uintptr_t edx, __int32 a2, char a3){
	static auto oFunc = g_Hooks.GameMode_getPickRangeHook->GetFastcall<float, GameMode*, uintptr_t, __int32, char>();

	if (Game.getLocalPlayer() != nullptr) {
		static auto BlockReachModule = moduleMgr->getModule<BlockReach>();
		if (BlockReachModule->isEnabled())
			return BlockReachModule->getBlockReach();

		/*static auto teleportModule = moduleMgr->getModule<Teleport>();
		if (teleportModule->isEnabled())
			return 255;*/
	}

	return oFunc(_this,edx, a2, a3);
}

__int32 __fastcall Hooks::GameMode_attack(GameMode* _this, uintptr_t edx, entity* ent){
	auto func = g_Hooks.GameMode_attackHook->GetFastcall<__int32, GameMode*, uintptr_t, entity*>();
	moduleMgr->onAttack(ent);
	return func(_this,edx, ent);
}

void __fastcall Hooks::Actor_baseTick(entity* ent){
	static auto oFunc = g_Hooks.Actor_baseTickHook->GetFastcall<void, entity*>();

	Localplayer* player = Game.getLocalPlayer();
	if (!player || !player->getlevel()) return oFunc(ent);

	static int tickCountThen = 0;
	int tickCountNow = *(int*)((__int32)player->getlevel() + 0x758);

	if (tickCountNow != tickCountThen) {
		g_Hooks.entityList.clear();
		tickCountThen = tickCountNow;
	}

	moduleMgr->onBaseTick(ent);

	if (true) {
		EntityListPointerHolder e;
		e.addedTick = tickCountNow;
		e.ent = ent;

		bool found = false;
		for (const auto& entity : g_Hooks.entityList)
			if (entity.ent == ent && entity.addedTick == tickCountNow) {
				found = true;
				break;
			}

		if (!found)
			g_Hooks.entityList.push_back(e);
	}

	return oFunc(ent);
}

void __fastcall Hooks::Actor_normalTickTick(entity* _this){
	static auto oFunc = g_Hooks.Actor_normalTickHook->GetFastcall<void, entity*>();

	cmdMgr->onTick();

	return oFunc(_this);
}

void __fastcall Hooks::Player_tickWorld(Player* _this, uintptr_t edx, __int32 a1){
	static auto oTick = g_Hooks.Player_tickWorldHook->GetFastcall<void, Player*, uintptr_t,__int32>();
	//auto o = oTick(_this,edx,a1);

	if (_this != nullptr && Game.getLocalPlayer() != nullptr && _this == Game.getLocalPlayer()) {
		GameMode* gm = Game.getLocalPlayer()->GetGamemode();
		if (_this && gm) {
			GameData::updateGameData(gm);
			moduleMgr->onWorldTick(gm);
		}
	}
	return oTick(_this, edx, a1);
}

void __fastcall Hooks::Actor_lerpMotion(entity* _this, uintptr_t edx, Vec3 motVec)
{
	static auto oLerp = g_Hooks.Actor_lerpMotionHook->GetFastcall<void, entity*,uintptr_t, Vec3>();
	
	//if (Game.getLocalPlayer() != _this)
	//	return oLerp(_this, edx, motVec);

	//static auto noKnockbackmod = moduleMgr->getModule<Velocity>();
	//if (noKnockbackmod->isEnabled()) {
	//	static void* networkSender = nullptr;
	//	if (!networkSender)
	//		networkSender = reinterpret_cast<void*>(6 + FindSignature("FF 90 C0 00 00 00 C6 47 11 01 8B 4D F4 64 89 0D 00 00 00 00 59 5F 5E 5B 8B E5 5D"));

	//	if (networkSender == _ReturnAddress()) {
	//		motVec = Game.getLocalPlayer()->velocity.lerp(motVec, noKnockbackmod->xModifier, noKnockbackmod->yModifier, noKnockbackmod->xModifier);
	//	}
	//}
	oLerp(_this, edx,motVec);
}

