#include "Containers.h"

bool Game::properties::has(const std::string& prop) const
{
	return find(prop) != end();
}
