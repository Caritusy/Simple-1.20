#pragma once
#include <functional>
#include <map>
#include <mutex>
#include <queue>
#include <unordered_set>
#include "../SDK/ClientInstance.h"
#include "../SDK/GameMode.h"
#include "../Utils/TextFormat.h"
#include "SlimMem.h"
struct InfoBoxData {
	bool isOpen = true;
	float fadeTarget = 1;
	float fadeVal = 0;
	float closeTimer = -1;
	std::string title;
	std::string message;

	InfoBoxData(std::string title, std::string message) : title(title), message(message) {};

	void fade() {
		fadeVal += (fadeTarget - fadeVal) * 0.04f;  // Adjust the fade factor as needed
		if (fadeTarget == 0 && abs(fadeVal) < 0.001f) {
			fadeVal = 0.0f;
			isOpen = false;
		}
	}
};

struct SkinData;

struct AABBHasher {
	size_t operator()(const AABB& i) const;
};

class GameData{
private:
	ClientInstance* clientInstance = nullptr;
	Localplayer* localPlayer = nullptr;
	GameMode* gameMode = nullptr;
//	EntityList* entityList = nullptr;
//	RakNetConnector* raknetConnector = nullptr;
	void* hDllInst = 0;
	std::unordered_set<AABB, AABBHasher> chestList;
	std::vector<std::string> textPrintList;
	std::mutex textPrintLock;
	std::mutex chestListMutex;
	int lastRequestId = 0;
	std::shared_ptr<std::string> customGeometry;
	bool customGeoActive = false;
	std::shared_ptr<std::tuple<std::shared_ptr<unsigned char[]>, size_t>> customTexture;
	bool customTextureActive = false;
private:
	bool injectorConnectionActive = false;
	const SlimUtils::SlimModule* gameModule = 0;
	bool shouldTerminateB = false;
	bool shouldHideB = false;
	bool isAllowingWIPFeatures = false;
	__int32 lastUpdate;
	static void retrieveClientInstance();
	TextHolder* fakeName;
public:
	//DController* hidController = nullptr;
	std::vector<std::shared_ptr<InfoBoxData>> infoBoxQueue;
	static SlimUtils::SlimMem* slimMem;
	static bool keys[0x256];


	static bool canUseMoveKeys();
	static bool isKeyDown(int key);
	static bool isKeyPressed(int key);
	static bool isRightClickDown();
	static bool isLeftClickDown();
	static bool isWheelDown();
	static bool shouldTerminate();
	static bool shouldHide();
	static void hide();
	static void terminate();
	static void updateGameData(GameMode* gameMode);
	static void initGameData(const SlimUtils::SlimModule* gameModule, SlimUtils::SlimMem* slimMem, void* hDllInst);
	//static void addChestToList(ChestBlockActor* ChestBlock2);
	//static void EntityList_tick(EntityList* list);
	//static void setHIDController(HIDController* Hid);
	//static void setRakNetConnector(RakNetConnector* raknet);
	static void displayMessages(entity* Data);
	static void log(const char* fmt, ...);

	void clearChestList() {
		std::lock_guard<std::mutex> listGuard(chestListMutex);
		chestList.clear();
	}
	inline std::shared_ptr<InfoBoxData> getFreshInfoBox() {
		while (!infoBoxQueue.empty()) {
			auto state = infoBoxQueue.front();
			if (!state->isOpen) {
				infoBoxQueue.erase(infoBoxQueue.begin());
				continue;
			}
			return state;
		}
		return std::shared_ptr<InfoBoxData>();
	}

	inline std::vector<std::shared_ptr<InfoBoxData>>& getInfoBoxList() {
		while (!infoBoxQueue.empty()) {
			auto box = infoBoxQueue.front();
			if (!box->isOpen) {
				infoBoxQueue.erase(infoBoxQueue.begin());
				continue;
			}
			break;
		}
		return infoBoxQueue;
	}

	inline std::shared_ptr<InfoBoxData> addInfoBox(std::string title, std::string message) {
		auto notification = std::make_shared<InfoBoxData>(title, message);
		infoBoxQueue.push_back(notification);
		return notification;
	}
	inline void setCustomGeometryOverride(bool setActive, std::shared_ptr<std::string> customGeoPtr) {
		customGeoActive = setActive;
		if (setActive)
			customGeometry.swap(customGeoPtr);
		else
			customGeometry.reset();
	}
	inline std::tuple<bool, std::shared_ptr<std::string>> getCustomGeoOverride() {
		return std::make_tuple(customGeoActive, customGeometry);
	}
	inline void setCustomTextureOverride(bool setActive, std::shared_ptr<std::tuple<std::shared_ptr<unsigned char[]>, size_t>> customTexturePtr) {
		customTextureActive = setActive;
		if (setActive)
			customTexture.swap(customTexturePtr);
		else
			customTexture.reset();
	}
	inline auto getCustomTextureOverride() {
		return std::make_tuple(customTextureActive, customTexture);
	}
	inline void* getDllModule() { return hDllInst; };
	inline ClientInstance* getClientInstance() { return clientInstance; };
	inline GuiData* getGuiData() { return clientInstance->getGuiData(); };
	inline Localplayer* getLocalPlayer() {
		localPlayer = clientInstance->getCILocalPlayer();
		if (localPlayer == nullptr)
			gameMode = nullptr;
		return localPlayer;
	};
	Localplayer** getPtrLocalPlayer() {
		return &localPlayer;
	};
	bool isInGame() {
		return localPlayer != nullptr;
	}
	const SlimUtils::SlimModule* getModule() {
		return gameModule;
	};
	const SlimUtils::SlimMem* getSlimMem() {
		return slimMem;
	};
	GameMode* getGameMode() { return gameMode; };
//	EntityList* getEntityList() { return entityList; };
//	HIDController** getHIDController() { return &hidController; };
//	RakNetConnector* getRakNetConnector() { return raknetConnector; };
	std::unordered_set<AABB, AABBHasher>& getChestList() { return chestList; };
	auto lockChestList() { return std::lock_guard<std::mutex>(chestListMutex); }
	void setFakeName(TextHolder* name) { fakeName = name; };
	TextHolder* getFakeName() { return fakeName; };
	inline __int64 getLastUpdateTime() { return lastUpdate; };
	void forEachEntity(std::function<void(entity*, bool)>);
	void forEachPlayer(std::function<void(entity*, bool)>);
	void forEachMob(std::function<void(entity*, bool)>);

};
extern GameData Game;

