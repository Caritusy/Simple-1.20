#pragma once
#include <map>
#include <vector>
#include <dxgi.h>
#include "../../Memory/GameData.h"
#include "../../Utils/DrawUtils.h"
#include "../Module/ModuleManager.h"

namespace opengl {
	void init(HDC);
	void disable();
};
namespace D3D11 {
	void init(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	void ResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
	void disable();
}

class Gui{
private:
	static void renderTooltip(std::string* text);

	static void renderCategory(Category category);
	inline static void getModuleListByCategory(Category category, std::vector<std::shared_ptr<IModule>>* modList);
	inline static const char* catToName(Category cat) {
		const char* categoryName = "";
		{
			switch (cat) {
			case Category::COMBAT:
				categoryName = "Combat";
				break;
			case Category::VISUAL:
				categoryName = "Visual";
				break;
			case Category::MOVEMENT:
				categoryName = "Movement";
				break;
			case Category::PLAYER:
				categoryName = "Player";
				break;
			case Category::WORLD:
				categoryName = "World";
				break;
			case Category::MISC:
				categoryName = "Misc";
				break;
			case Category::CLIENT:
				categoryName = "Client";
				break;
			}
		}
		return categoryName;
	}
public:
	static void init();
	static void render();
};

