#include "DrawUtils.h"
#include "../include/ImGui/imgui.h"
#include "../Simple/Module/ModuleManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
std::shared_ptr<glmatrixf> refdef;
GuiData* guiData;
Vec2 fov;
Vec2 screenSize;
Vec3 origin;
ImVec4 colorHolder;
DrawUtils::DrawUtils() {
}
void DrawUtils::setCtx(GuiData* gui) {
	guiData = gui;
	fov = Game.getClientInstance()->getFov();
//	origin = Game.getClientInstance()->levelRenderer->getOrigin();
	screenSize = gui->windowSize;
	glmatrixf* badrefdef = Game.getClientInstance()->getRefDef();
	refdef = std::shared_ptr<glmatrixf>(badrefdef->correct());
}
void DrawUtils::setColor(float r, float g, float b, float a) {
	colorHolder.x = r;
	colorHolder.y = g;
	colorHolder.z = b;
	colorHolder.w = a;
}

ImVec2 DrawUtils::getTextLength(std::string* textStr) {
	return  ImGui::CalcTextSize(textStr->c_str());
}

ImFont* DrawUtils::getFont(int font) {
	ImGuiIO& io = ImGui::GetIO();
	return io.Fonts->Fonts[font];
}

void DrawUtils::drawTriangle(const Vec2& p1, const ImVec2& p2, const Vec2& p3, ImU32 col, float thickness) {
	ImGui::GetBackgroundDrawList()->AddTriangle(ImVec2(p1.x, p1.y), ImVec2(p2.x, p2.y), ImVec2(p3.x, p3.y), col, thickness);
}

void DrawUtils::drawNgon(const Vec2& center, float radius, ImU32 col, int num_segments, float thickness)
{
	ImGui::GetBackgroundDrawList()->AddNgon(ImVec2(center.x, center.y), radius, col, num_segments, thickness);
}

void DrawUtils::drawCircle(const Vec2& center, float radius, ImU32 col, int num_segments, float thickness) {
	ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(center.x, center.y), radius, col, num_segments, thickness);
}

void DrawUtils::drawQuad(const Vec2& p1, const Vec2& p2, const Vec2& p3, const Vec2& p4, ImU32 col, float thickness) {
	ImGui::GetBackgroundDrawList()->AddQuad(ImVec2(p1.x, p1.y), ImVec2(p2.x, p2.y), ImVec2(p3.x, p3.y), ImVec2(p4.x, p4.y), col, thickness);
}

void DrawUtils::drawLine(const Vec2& start, const Vec2& end, ImU32 col, float lineWidth) {
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(start.x, start.y), ImVec2(end.x, end.y),col != NULL ? col : (ImU32)ImColor(colorHolder.x, colorHolder.y, colorHolder.z), lineWidth);
}

void DrawUtils::drawLinestrip3d(const std::vector<Vec3>& points) {
}

void DrawUtils::drawLine3d(const Vec3& start, const Vec3& end)
{
}

void DrawUtils::drawBox3d(const Vec3& lower, const Vec3& upper){
}

void DrawUtils::fillRectangle(const Vec4& pos, const ImU32 col, float alpha) {
	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(pos.z, pos.w), ImVec2(pos.x, pos.y), col);
}
void DrawUtils::drawBezierQuadratic(const Vec2& p1, const Vec2& p2, const Vec2& p3, ImU32 col, float thickness, int num_segments) {
	ImGui::GetBackgroundDrawList()->AddBezierQuadratic(ImVec2(p1.x, p1.y), ImVec2(p2.x, p2.y), ImVec2(p3.x, p3.y), col, thickness, num_segments);
}
void DrawUtils::drawBezierCubic(const Vec2& p1, const Vec2& p2, const Vec2& p3, const Vec2& p4, ImU32 col, float thickness, int num_segments) {
	ImGui::GetBackgroundDrawList()->AddBezierCubic(ImVec2(p1.x, p1.y), ImVec2(p2.x, p2.y), ImVec2(p3.x, p3.y), ImVec2(p4.x, p4.y), col, thickness, num_segments);
}
void DrawUtils::drawCircleFilled(const Vec2& center, float radius, ImU32 col, int num_segments) {
	ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(center.x, center.y), radius, col, num_segments);
}
void DrawUtils::drawNgonFilled(const Vec2& center, float radius_x, float radius_y, ImU32 col, float rot, int num_segments, float thickness)
{
	ImGui::GetBackgroundDrawList()->AddEllipse(ImVec2(center.x, center.y), radius_x, radius_y, col, rot, num_segments, thickness);
}
void DrawUtils::drawImage(std::string filePath, const Vec2& p_min, const Vec2& p_max, const Vec2& uv_min, const Vec2& uv_max, ImU32 col) {
	int width, height;
	ImGui::GetBackgroundDrawList()->AddImage(
		(void*)(intptr_t)stbi_load(filePath.c_str(), &width, &height, 0, 4),
		ImVec2(p_min.x, p_min.y),
		ImVec2(p_min.x + p_max.x, p_min.y + p_max.y),
		ImVec2(uv_min.x, uv_min.y),
		ImVec2(uv_max.x, uv_max.y),
		col
	);
}

void DrawUtils::drawImageRounded(std::string filePath, const Vec2& imagePos, const Vec2& imageDimension, const Vec2& idk, const Vec2& idk2, const Vec2& uv1, const Vec2& uv2, const Vec2& uv3, const Vec2& uv4, ImU32 col)
{
}

void DrawUtils::drawText(const Vec2& pos, std::string* text, ImU32 color, float alpha, int Font, float textSize) {
	ImGuiIO& io = ImGui::GetIO();
	ImGui::GetBackgroundDrawList()->AddText(io.Fonts->Fonts[Font], textSize == -1.f ? io.Fonts->Fonts[Font]->FontSize : textSize, ImVec2(pos.x, pos.y), color, text->c_str());
}

void DrawUtils::drawBox(const Vec3& lower, const Vec3& upper, float lineWidth, bool outline) {
	Vec3 diff;
	diff.x = upper.x - lower.x;
	diff.y = upper.y - lower.y;
	diff.z = upper.z - lower.z;

	Vec3 vertices[8];
	vertices[0] = Vec3(lower.x, lower.y, lower.z);
	vertices[1] = Vec3(lower.x + diff.x, lower.y, lower.z);
	vertices[2] = Vec3(lower.x, lower.y + diff.y, lower.z);
	vertices[3] = Vec3(lower.x + diff.x, lower.y + diff.y, lower.z);
	vertices[4] = Vec3(lower.x, lower.y, lower.z + diff.z);
	vertices[5] = Vec3(lower.x + diff.x, lower.y, lower.z + diff.z);
	vertices[6] = Vec3(lower.x, lower.y + diff.y, lower.z + diff.z);
	vertices[7] = Vec3(lower.x + diff.x, lower.y + diff.y, lower.z + diff.z);

	std::vector<std::tuple<int, Vec2>> screenCords;
	for (int i = 0; i < 8; i++) {
		Vec2 screen;
		if (refdef->OWorldToScreen(origin, vertices[i], screen, fov, screenSize)) {
			screenCords.emplace_back(outline ? (int)screenCords.size() : i, screen);
		}
	}
	if (screenCords.size() < 2)
		return;  // No lines possible
	if (!outline) {
		for (auto it = screenCords.begin(); it != screenCords.end(); it++) {
			auto from = *it;
			auto fromOrig = vertices[std::get<0>(from)];

			for (auto to : screenCords) {
				auto toOrig = vertices[std::get<0>(to)];

				bool shouldDraw = false;
				// X direction
				shouldDraw |= fromOrig.y == toOrig.y && fromOrig.z == toOrig.z && fromOrig.x < toOrig.x;
				// Y direction
				shouldDraw |= fromOrig.x == toOrig.x && fromOrig.z == toOrig.z && fromOrig.y < toOrig.y;
				// Z direction
				shouldDraw |= fromOrig.x == toOrig.x && fromOrig.y == toOrig.y && fromOrig.z < toOrig.z;

				if (shouldDraw)
					drawLine(std::get<1>(from), std::get<1>(to), ImColor(colorHolder.x, colorHolder.y, colorHolder.z) ,lineWidth);
			}
		}

		return;
	}
	auto it = screenCords.begin();
	std::tuple<int, Vec2> start = *it;
	it++;
	for (; it != screenCords.end(); it++) {
		auto cur = *it;
		if (std::get<1>(cur).x < std::get<1>(start).x) {
			start = cur;
		}
	}

	// Follow outer line
	std::vector<int> indices;

	auto current = start;
	indices.push_back(std::get<0>(current));
	Vec2 lastDir(0, -1);
	do {
		float smallestAngle = PI * 2;
		Vec2 smallestDir;
		std::tuple<int, Vec2> smallestE;
		auto lastDirAtan2 = atan2(lastDir.y, lastDir.x);
		for (auto cur : screenCords) {
			if (std::get<0>(current) == std::get<0>(cur))
				continue;

			// angle between vecs
			Vec2 dir = Vec2(std::get<1>(cur)).sub(std::get<1>(current));
			float angle = atan2(dir.y, dir.x) - lastDirAtan2;
			if (angle > PI) {
				angle -= 2 * PI;
			}
			else if (angle <= -PI) {
				angle += 2 * PI;
			}
			if (angle >= 0 && angle < smallestAngle) {
				smallestAngle = angle;
				smallestDir = dir;
				smallestE = cur;
			}
		}
		indices.push_back(std::get<0>(smallestE));
		lastDir = smallestDir;
		current = smallestE;
	} while (std::get<0>(current) != std::get<0>(start) && indices.size() < 8);

	Vec2 lastVertex;
	bool hasLastVertex = false;
	for (auto& indice : indices) {
		Vec2 curVertex = std::get<1>(screenCords[indice]);
		if (!hasLastVertex) {
			hasLastVertex = true;
			lastVertex = curVertex;
			continue;
		}

		drawLine(lastVertex, curVertex, ImColor(colorHolder.x, colorHolder.y, colorHolder.z), lineWidth);
		lastVertex = curVertex;
	}
}

//void DrawUtils::drawEntityBox(Entity* ent, float lineWidth) {
//	Vec3 end = *ent->getPos();
//	AABB render(end, ent->width, ent->width, end.y - ent->aabb.lower.y);
//	render.upper.y += 0.1f;
//
//	drawBox(render.lower, render.upper, lineWidth, true);
//}
//
//void DrawUtils::draw2D(Entity* ent, float lineWidth) {
//	Vec3 base = *ent->getPos();
//	float ofs = (Game.getLocalPlayer()->yaw + 90.f) * (PI / 180);
//
//	Vec3 corners[4];
//	Vec2 corners2d[4];
//
//	corners[0] = Vec3(base.x - ent->width / 1.5f * -sin(ofs), ent->aabb.upper.y + 0.1f, base.z - ent->width / 1.5f * cos(ofs));
//	corners[1] = Vec3(base.x + ent->width / 1.5f * -sin(ofs), ent->aabb.upper.y + 0.1f, base.z + ent->width / 1.5f * cos(ofs));
//	corners[2] = Vec3(base.x - ent->width / 1.5f * -sin(ofs), ent->aabb.lower.y, base.z - ent->width / 1.5f * cos(ofs));
//	corners[3] = Vec3(base.x + ent->width / 1.5f * -sin(ofs), ent->aabb.lower.y, base.z + ent->width / 1.5f * cos(ofs));
//	/*printf("fov [x %f,y %f]screenSize[x %f,y %f]origin[x%f,y%f,z%f] \nrefdef[0%f 1%f 2%f 3%f 4%f 5%f 6%f 7%f 8%f 9%f 10%f 11%f 12%f 13%f 14%f 15%f]\n", fov.x, fov.y, screenSize.x, screenSize.y, origin.x, origin.y, origin.z
//		, refdef->v[0], refdef->v[1], refdef->v[2], refdef->v[3], refdef->v[4]
//		, refdef->v[5], refdef->v[6], refdef->v[7], refdef->v[8], refdef->v[9]
//		, refdef->v[10], refdef->v[11], refdef->v[12], refdef->v[13], refdef->v[14]
//		, refdef->v[15]);
//	printf("pos[x%f y%f z%f]", base.x, base.y, base.z);
//	printf("lower[x%f y%f z%f]\n", ent->aabb.lower.x, ent->aabb.lower.y, ent->aabb.lower.z);
//	printf("upper[x%f y%f z%f]\n", ent->aabb.upper.x, ent->aabb.upper.y, ent->aabb.upper.z);*/
//
//	if (refdef->OWorldToScreen(origin, corners[0], corners2d[0], fov, screenSize) &&
//		refdef->OWorldToScreen(origin, corners[1], corners2d[1], fov, screenSize) &&
//		refdef->OWorldToScreen(origin, corners[2], corners2d[2], fov, screenSize) &&
//		refdef->OWorldToScreen(origin, corners[3], corners2d[3], fov, screenSize)) {
//		drawLine(corners2d[0], corners2d[1], ImColor(colorHolder.x, colorHolder.y, colorHolder.z), lineWidth);
//		drawLine(corners2d[0], corners2d[2], ImColor(colorHolder.x, colorHolder.y, colorHolder.z), lineWidth);
//		drawLine(corners2d[3], corners2d[1], ImColor(colorHolder.x, colorHolder.y, colorHolder.z), lineWidth);
//		drawLine(corners2d[3], corners2d[2], ImColor(colorHolder.x, colorHolder.y, colorHolder.z), lineWidth);
//	}
//}
//
//void DrawUtils::draw2DCorners(Entity* ent, float lineWidth) {
//	Vec3 base = *ent->getPos();
//	float ofs = (Game.getLocalPlayer()->yaw + 90.f) * (PI / 180);
//
//	Vec3 upperCorner = Vec3(base.x - ent->width / 2.f * -sin(ofs), ent->aabb.upper.y + 0.1f, base.z - ent->width / 2.f * cos(ofs));
//	Vec3 lowerCorner = Vec3(base.x + ent->width / 2.f * -sin(ofs), ent->aabb.lower.y, base.z + ent->width / 2.f * cos(ofs));
//	fov.x = fov.x * (PI / 180.0);
//	fov.y = fov.y * (PI / 180.0);
//	Vec2 corners[4];
//	if (refdef->OWorldToScreen(origin, upperCorner, corners[0], fov, screenSize) && refdef->OWorldToScreen(origin, lowerCorner, corners[3], fov, screenSize)) {
//		corners[0] = Vec2(fmin(corners[0].x, corners[3].x), fmin(corners[0].y, corners[3].y));
//		corners[1] = Vec2(fmax(corners[0].x, corners[3].x), fmin(corners[0].y, corners[3].y));
//		corners[2] = Vec2(fmin(corners[0].x, corners[3].x), fmax(corners[0].y, corners[3].y));
//		corners[3] = Vec2(fmax(corners[0].x, corners[3].x), fmax(corners[0].y, corners[3].y));
//
//		float length = (corners[1].x - corners[0].x) / 4.f;
//		drawLine(corners[0], Vec2(corners[0].x + length, corners[1].y), ImColor(colorHolder.x, colorHolder.y, colorHolder.z), lineWidth);
//		drawLine(corners[0], Vec2(corners[2].x, corners[0].y + length), ImColor(colorHolder.x, colorHolder.y, colorHolder.z), lineWidth);
//		drawLine(Vec2(corners[1].x - length, corners[0].y), corners[1], ImColor(colorHolder.x, colorHolder.y, colorHolder.z), lineWidth);
//		drawLine(corners[1], Vec2(corners[3].x, corners[1].y + length), ImColor(colorHolder.x, colorHolder.y, colorHolder.z), lineWidth);
//		drawLine(Vec2(corners[2].x, corners[2].y - length), corners[2], ImColor(colorHolder.x, colorHolder.y, colorHolder.z), lineWidth);
//		drawLine(corners[2], Vec2(corners[2].x + length, corners[3].y), ImColor(colorHolder.x, colorHolder.y, colorHolder.z), lineWidth);
//		drawLine(Vec2(corners[3].x - length, corners[2].y), corners[3], ImColor(colorHolder.x, colorHolder.y, colorHolder.z), lineWidth);
//		drawLine(Vec2(corners[1].x, corners[3].y - length), corners[3], ImColor(colorHolder.x, colorHolder.y, colorHolder.z), lineWidth);
//	}
//}
//
//void DrawUtils::draw2DFill(Entity* ent, ImU32 color, float opacity) {
//	Vec3 base = *ent->getPos();
//	float ofs = (Game.getLocalPlayer()->yaw + 90.f) * (PI / 180);
//
//	Vec3 corners[2];
//	Vec2 corners2d[2];
//
//	corners[0] = Vec3(base.x - ent->width / 1.5f * -sin(ofs), ent->aabb.upper.y + (float)0.1, base.z - ent->width / 1.5f * cos(ofs));
//	corners[1] = Vec3(base.x + ent->width / 1.5f * -sin(ofs), ent->aabb.lower.y, base.z + ent->width / 1.5f * cos(ofs));
//
//	if (refdef->OWorldToScreen(origin, corners[0], corners2d[0], fov, screenSize) &&
//		refdef->OWorldToScreen(origin, corners[1], corners2d[1], fov, screenSize)) {
//		fillRectangle(Vec4(corners2d[0].x, corners2d[0].y, corners2d[1].x, corners2d[1].y), color, opacity);
//	}
//}
//
//void DrawUtils::drawNameTags(Entity* ent, float textSize, bool drawHealth, bool useUnicodeFont) {
//	static auto nametagsMod = moduleMgr->getModule<NameTags>();
//	Vec2 textPos;
//	Vec4 rectPos;
//	std::string text;
//	std::string entityName = ent->GetNameTag()->getText();
//	if (nametagsMod->displayDistance) {
//		float distance = ent->getPos()->dist(*Game.getLocalPlayer()->getPos());
//		text = entityName + std::string(" ") + std::string("[") + std::to_string((int)distance) + std::string("blocks") + std::string("]");// +std::to_string((int)std::hex << (int)ent);
//	}
//	else {
//		text = entityName;
//	}
//	//text = Utils::sanitize(text);
//	float textWidth = getTextWidth(&text, textSize).x;
//	float textHeight = DrawUtils::getFont(0)->FontSize * textSize;
//
//	if (refdef->OWorldToScreen(origin, ent->eyePos0.add(0, 0.5f, 0), textPos, fov, screenSize)) {
//		textPos.y -= textHeight;
//		textPos.x -= textWidth + (textWidth * 4)+ textWidth;
//		rectPos.x = textPos.x - 1.f * textSize;
//		rectPos.y = textPos.y - 1.f * textSize;
//		rectPos.z = textPos.x + textWidth + 1.f * textSize;
//		rectPos.w = textPos.y + textHeight + 2.f * textSize;
//		/*Vec4 subRectPos = rectPos;
//		subRectPos.y = subRectPos.w - 1.f * textSize;
//
//		if (nametagsMod->underline) {
//			fillRectangle(subRectPos, ImColor(85, 85, 85), 0.9f);
//		}*/
//		drawText(textPos, &text, ImColor(255, 255, 255), 1);
//	}
//}

void DrawUtils::chromaText(std::string text, float sat, float value, float alpha, float speed, float offset, float range){
	for (int i = 0; i < text.length(); i++) {
		char c = text.c_str()[i];
		std::string s(1, text.at(i));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(-0.5, 4)); // not the best way, calculating string width will be slightly inaccurate
		float r, g, b;
		Utils::ColorConvertHSVtoRGB(Utils::getTimeHue(i * range, speed, offset), sat, value, r, g, b);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(r, g, b, alpha));
		ImGui::Text(s.c_str());
		ImGui::PopStyleColor();

		if (i != text.length() - 1) ImGui::SameLine();
		ImGui::PopStyleVar();
	}
}
