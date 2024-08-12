#include "Arraylist.h"
#include "../ModuleManager.h"
#include "../../../Utils/DrawUtils.h"
Arraylist::Arraylist() : IModule(0, Category::VISUAL, "Display your enabled modules on the HUD!") {
	registerFloatSetting("Opacity", &alpha, alpha, 0.f, 1.f);
	registerFloatSetting("Color Speed", &cycleSpeed, cycleSpeed, 0.f, 5.f);
	registerFloatSetting("Saturation", &saturation, saturation, 0.f, 1.f);
	registerFloatSetting("Range", &rangeML, rangeML, 0.f, 0.1f);
	registerFloatSetting("Offset", &offsetML, offsetML, 0.f, 0.4f);
}

Arraylist::~Arraylist()
{
}

const char* Arraylist::getModuleName()
{
	return ("Arraylist");
}

const char* Arraylist::getRawModuleName()
{
	return ("Arraylist");
}
struct IModuleContainer {
	// Struct used to Sort IModules in a std::set
	std::shared_ptr<IModule> backingModule;
	std::string moduleName;
	bool enabled;
	int keybind;
	float textWidth;
	Vec2* pos;
	bool shouldRender = true;

	IModuleContainer(std::shared_ptr<IModule> mod) {
		static auto arrayMod = moduleMgr->getModule<Arraylist>();
		static auto hudMod = moduleMgr->getModule<HudModule>();
		const char* moduleNameChr = mod->getModuleName();
		this->enabled = mod->isEnabled();
		this->keybind = mod->getKeybind();
		this->backingModule = mod;
		this->pos = mod->getPos();

		if (keybind == 0x0)
			moduleName = moduleNameChr;
		else {
			char text[50];
			sprintf_s(text, 50, "%s%s", moduleNameChr, hudMod->keybinds ? std::string(" [" + std::string(Utils::getKeybindName(keybind)) + "]").c_str() : "");
			moduleName = text;
		}

		if (!this->enabled && *this->pos == Vec2(0.f, 0.f))
			this->shouldRender = false;
		this->textWidth = DrawUtils::getTextLength(&moduleName).x;
	}

	bool operator<(const IModuleContainer& other) const {
		if (this->textWidth == other.textWidth)
			return moduleName < other.moduleName;
		return this->textWidth > other.textWidth;
	}
};
//void Arraylist::onPostRender() {
//
//    ImVec2 winPadding = ImGui::GetStyle().WindowPadding;
//    std::vector<std::string> modules;
//    float calcHeight = winPadding.y * 2;
//    float longestStr = 0;
//
//    auto lock = moduleMgr->lockModuleList();
//    std::vector<std::shared_ptr<IModule>>* moduleList = moduleMgr->getModuleList();
//    for (int i = 0; i < moduleList->size(); i++) {
//        IModule* m = moduleList->at(i).get();
//        if (!m->isEnabled()) continue;
//
//        std::string moduleName = m->getRawModuleName(); // Store a copy of the module name
//        ImVec2 vec2 = ImGui::CalcTextSize(moduleName.c_str());
//        if (vec2.x > longestStr) longestStr = vec2.x;
//        calcHeight += vec2.y;
//
//        modules.push_back(moduleName); // Store the module name copy
//    }
//
//    if (modules.empty()) return; // No module active
//
//    std::sort(modules.begin(), modules.end(), [](const std::string& a, const std::string& b) {
//        return a.length() > b.length();
//        });
//
//    calcHeight += ImGui::GetStyle().ItemSpacing.y * (modules.size() - 1); // Item spacing
//
//    ImVec2 windowPos = ImVec2(ImGui::GetIO().DisplaySize.x - (longestStr + winPadding.x * 2), 0);
//    ImVec2 windowSize = ImVec2(longestStr + winPadding.x * 2, calcHeight);
//
//    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always, ImVec2(1.0f, 0.0f));
//    ImGui::SetNextWindowSize(windowSize);
//    ImGui::SetNextWindowBgAlpha(0.0f);
//    ImGui::Begin("  ", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMouseInputs);
//
//    // Iterate through each module and draw sideRect behind the text
//    for (int i = 0; i < modules.size(); i++) {
//        std::string& str = modules.at(i);
//        float h, s, v;
//        ImVec4 ccolML = DrawUtils::rgbaToVec4(255, 100, 100, 255);
//        //ColorH::RGBtoHSV((255 / 2, 100 / 2, 255 / 2, h, s, v);
//        Utils::ColorConvertRGBtoHSV(ccolML.x, ccolML.y, ccolML.z, h, s, v);
//        if (true) {
//            ImVec2 textSize = ImGui::CalcTextSize(str.c_str());
//            ImVec2 textPos = ImGui::GetCursorScreenPos(); // Current position of the text
//
//            // Define sideRect with some padding around the text
//            Vec4 sideRect = Vec4(
//                textPos.x + textSize.x - ImGui::GetStyle().ItemSpacing.x, // Left
//                textPos.y - ImGui::GetStyle().FramePadding.y, // Top
//                textPos.x + textSize.x + ImGui::GetStyle().ItemSpacing.x, // Right
//                textPos.y + textSize.y + ImGui::GetStyle().FramePadding.y // Bottom
//            );
//
//            //if (alpha > 0) {
//            //    int seperation = 50;  // Adjust this to change the separation of the colors
//            //    int index = 0;
//            //    auto arrayColor = DrawUtils::getRainbowColor(cycleSpeed, saturation, 1, index * (seperation * 2));
//            //    DrawUtils::fillRectangle(sideRect, arrayColor, 1.f);
//            //}
//
//            // Adjust the position for the text
//            ImGui::Dummy(ImVec2(longestStr - textSize.x - ImGui::GetStyle().ItemSpacing.x, 0));
//            ImGui::SameLine();
//
//            // Replace `DrawUtils::chromaText` with the appropriate function for rendering rainbow text
//            DrawUtils::chromaText(str, s, v, alpha, i * (offsetML + 1), cycleSpeed, rangeML);
//        }
//    }
//
//    ImGui::End();
//}




void Arraylist::onPostRender() {
	static auto hudMod = moduleMgr->getModule<HudModule>();
	ImVec2 winPadding = ImGui::GetStyle().WindowPadding;
	float calcHeight = winPadding.y * 2;
	float longestStr = 0;

	std::vector<std::string> modContainerList;

	auto lock = moduleMgr->lockModuleList();
	std::vector<std::shared_ptr<IModule>>* moduleList = moduleMgr->getModuleList();

	for (auto& module : *moduleList) {
		if (!module->isEnabled()) continue;

		std::string moduleName = module->getRawModuleName();
		ImVec2 vec2 = ImGui::CalcTextSize(moduleName.c_str());
		longestStr = (std::max)(longestStr, vec2.x);
		calcHeight += vec2.y;

		modContainerList.push_back(moduleName);
	}

	if (modContainerList.empty()) return; // no active modules

	calcHeight += ImGui::GetStyle().ItemSpacing.y * (modContainerList.size() - 1);

	ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - (winPadding.x * 2), 0), ImGuiCond_Always, ImVec2(1.0f, 0.0f));
	ImGui::SetNextWindowSize({ longestStr + winPadding.x * 2, calcHeight });

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
	ImGui::Begin("  ", 0, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMouseInputs);
	ImGui::PopStyleColor();

	for (int i = 0; i < modContainerList.size(); i++) {
		std::string& str = modContainerList[i];
		float h, s, v;

		//ImVec4 ccolML = DrawUtils::rgbaToVec4(255, 100, 100, 255);
		Utils::ColorConvertRGBtoHSV(0, 0, 0, h, s, v);

	
			float width = ImGui::CalcTextSize(str.c_str()).x;
			ImGui::Dummy(ImVec2(longestStr - width - ImGui::GetStyle().ItemSpacing.x, 0));
			ImGui::SameLine();


		DrawUtils::chromaText(str, s, v, alpha, i * (offsetML + 1), cycleSpeed, rangeML);
	}

	ImGui::End();
}