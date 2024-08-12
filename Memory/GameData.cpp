#include "GameData.h"
#include <Windows.h>
#include <set>
#include "../Utils/easylogging++.h"
#include "../Utils/Utils.h"
#include "Hooks.h"

GameData Game;
bool GameData::keys[0x256];
SlimUtils::SlimMem* GameData::slimMem;

void GameData::retrieveClientInstance(){
	static uintptr_t clientInstanceOffset = 0x0;
	if (clientInstanceOffset == 0x0) {
		clientInstanceOffset = *reinterpret_cast<int*>(Game.gameModule->ptrBase + 0x403CF94);
	}
	Game.clientInstance = reinterpret_cast<ClientInstance*>(/*Utils::readPointer<uintptr_t*>(clientInstanceOffset, { 0x648,0x0,0x14})*/Game.getSlimMem()->ReadPtr<uintptr_t*>(clientInstanceOffset,{ 0x648,0x0,0x14 }));
#ifdef _DEBUG
	if (Game.clientInstance == 0)
		throw std::exception("Client Instance is 0");
#endif
}
void GameData::initGameData(const SlimUtils::SlimModule* gameModule, SlimUtils::SlimMem* slimMem, void* hDllInst){
	Game.gameModule = gameModule;
	Game.slimMem = slimMem;
	Game.hDllInst = hDllInst;
	retrieveClientInstance();

#ifdef _DEBUG
	LOG(DEBUG) << "Base: " << std::hex << Game.getModule()->ptrBase;
	if (Game.clientInstance != nullptr) {
		LOG(DEBUG) << "ClientInstance: " << std::hex << Game.clientInstance;
		LOG(DEBUG) << "LocalPlayer:" << std::hex << Game.getLocalPlayer();
		LOG(DEBUG) << "MinecraftGame:" << std::hex << Game.clientInstance->minecraftGame;
	}
#else
#endif
}

void GameData::displayMessages(entity* Data)
{
}

void GameData::log(const char* fmt, ...){
	va_list arg;
	va_start(arg, fmt);
	char message[300];
	vsprintf_s(message, fmt, arg);
	va_end(arg);
	std::unique_lock<std::mutex> lock(Game.textPrintLock);
	Game.textPrintList.emplace_back(message);
}

void GameData::forEachEntity(std::function<void(entity*, bool)>callback)
{
}

void GameData::forEachPlayer(std::function<void(entity*, bool)>callback){
	//if (this->localPlayer && this->localPlayer->getlevel()) {
	//	for (const auto& ent : g_Hooks.entityList) if (ent.ent != nullptr && ent.ent->isPlayer()) callback(ent.ent, false); //get all players
	//}
}

void GameData::forEachMob(std::function<void(entity*, bool)>callback)
{
}

bool GameData::canUseMoveKeys() {
	MinecraftGame* mc = Game.clientInstance->minecraftGame;
	if (mc == nullptr) {
		return false;
	}
	return mc->canUseKeybinds();
}

bool GameData::isKeyDown(int key) {
	return keys[(int)key];
}

bool GameData::isKeyPressed(int key) {
	if (isKeyDown(key)) {
		while (isKeyDown(key))
			Sleep(1);
		return true;
	}
	return false;
}

bool GameData::isRightClickDown() {
	/*if (Game.hidController == 0)
		return false;
	return Game.hidController->rightClickDown;*/
	return false;
}

bool GameData::isLeftClickDown() {
	/*if (Game.hidController == 0)
		return false;
	return Game.hidController->leftClickDown;*/
	return false;
}

bool GameData::isWheelDown() {
	//if (Game.hidController == 0)
	//	return false;
	//return Game.hidController->wheelDown;
	return false;
}

bool GameData::shouldTerminate() {
	return Game.shouldTerminateB;
}

void GameData::terminate() {
	Game.getClientInstance()->minecraft->setTimerSpeed(20.f);
	g_Hooks.entityList.clear();
	Game.shouldTerminateB = true;
}

bool GameData::shouldHide() {
	return Game.shouldHideB;
}

void GameData::hide() {
	Game.shouldHideB = !(Game.shouldHideB);
}

void GameData::updateGameData(GameMode* gameMode) {
	retrieveClientInstance();
	Game.localPlayer = Game.getLocalPlayer();

	if (Game.localPlayer != nullptr) {
		Game.gameMode = gameMode;
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&Game.lastUpdate));

		if (Game.localPlayer != nullptr) {
			GuiData* guiData = Game.clientInstance->getGuiData();
		/*	if (guiData != nullptr) {
				displayMessages(guiData);*/
			
		}
	}
}