#pragma once

#include "CoreMath.h"

namespace Core
{

	class Object;

	class Scene
	{
	private:
		std::list<Object*> objects;

	public:
		void load();

		void update();
	};

}