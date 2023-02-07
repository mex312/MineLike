#pragma once
#include "Object.h"

namespace Game
{

	class Entity : public Core::Object
	{
	public:
		virtual void update() = 0;
	};

}