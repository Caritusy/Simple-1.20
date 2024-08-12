#pragma once

#include <vector>

#include "../SDK/Entity.h"

class Target {
private:
	static bool containsOnlyASCII(const std::string& string);

public:
	static void init(Localplayer** lc);
	static bool isValidTarget(entity* ent);
};
