#include "Gui.h"
#include <D3D11.h>
#include "Fonts.hpp"
#include "../../include/ImGui/imgui.h"
#include "../../include/ImGui/backends/imgui_impl_win32.h"

#include "../../include/ImGui/gl3w.h"
#include "../../include/ImGui/backends/imgui_impl_opengl3.h"
#include "../../include/ImGui/backends/imgui_impl_opengl3_loader.h"

#include "../../include/ImGui/backends/imgui_impl_dx11.h"

#include "../Module/Modules/GuiMod.h"

#include "../../Utils/easylogging++.h"
#include <Windows.h>
#include "../../Utils/Json.hpp"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
static WNDPROC oWndProcHandler = nullptr;
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) return true;
	return CallWindowProc(oWndProcHandler, hWnd, uMsg, wParam, lParam);
}

void opengl::init(HDC hdc)
{
	static bool init = false;
	try {
		if (!init) {
			auto hwid = WindowFromDC(hdc);
			oWndProcHandler = (WNDPROC)SetWindowLongPtr(hwid, GWL_WNDPROC, (LONG)WndProc);
			ImGui::CreateContext();
			ImGui_ImplWin32_Init(hwid);

			gl3wInit();
			ImGuiIO& io = ImGui::GetIO();
			io.Fonts->Clear();

			//ImFontConfig font_cfg;
			//font_cfg.FontDataOwnedByAtlas = false; // if true it will try to free memory and fail
			//io.Fonts->AddFontFromMemoryTTF((void*)poppinsFont, sizeof(poppinsFont), 18, &font_cfg);
			io.Fonts->AddFontFromFileTTF("Downloaded\\fusion-pixel-10px-monospaced-zh_hant.ttf", 20, nullptr, io.Fonts->GetGlyphRangesChineseFull());

			//io.Fonts->AddFontFromFileTTF("Downloaded\\fusion-pixel-10px-monospaced-zh_hant.ttf", 20, nullptr, io.Fonts->GetGlyphRangesChineseFull());
			io.Fonts->AddFontFromFileTTF("data\\fonts\\Mojangles.ttf", 20, nullptr, io.Fonts->GetGlyphRangesChineseFull());
			io.Fonts->AddFontFromFileTTF("data\\fonts\\MinecraftTen.ttf", 13, nullptr, io.Fonts->GetGlyphRangesChineseFull());


			ImGui_ImplOpenGL3_Init();
			LOG(INFO) << "Using OpenGL renderer.";
			init = true;
		}
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		auto clickGuiModule = moduleMgr->getModule<GuiMod>();
		static auto hudModule = moduleMgr->getModule<HudModule>();
		static auto arrayListModule = moduleMgr->getModule<Arraylist>();

		moduleMgr->onPreRender();


		bool shouldPostRender = true;

		{
		if (clickGuiModule->isEnabled()) {
			Gui::render();
		}
		
		}

		if (shouldPostRender) moduleMgr->onPostRender();

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	catch (...) {
		Game.getGuiData()->displayClientMessageF("%s%s%sOpenGL failure.", RED, BOLD, RESET);
		LOG(INFO) << "OpenGL failure.";
		return;
	}

}

void opengl::disable()
{
}

void D3D11::init(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
}

void D3D11::ResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
}

void D3D11::disable()
{
}

void Gui::renderTooltip(std::string* text)
{
}

void Gui::renderCategory(Category category)
{
}

inline void Gui::getModuleListByCategory(Category category, std::vector<std::shared_ptr<IModule>>* modList)
{

}

void Gui::init()
{
}

void Gui::render()
{

}
