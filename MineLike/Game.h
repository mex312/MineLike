#pragma once

#include "Core.h"
#include "World.h"

namespace Game
{
	void initGame();

	const Block* getAirBlock();

	Core::Texture* getBaseTexture();
	Core::Texture* getNullTexture();
}