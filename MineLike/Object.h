#pragma once
#include "CoreMath.h"

namespace Core
{

	class Object
	{
		Core::u64 id;

		virtual void update() = 0;
	};

}