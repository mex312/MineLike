#include "Game.h"

using namespace Core;
using namespace Game;

struct comparator {
	bool operator()(const id& a, const id& b) const { return a.asString() < b.asString(); }
};

std::map<id, BlockConstructor, comparator> registeredConstructors = std::map<id, BlockConstructor, comparator>();

void Game::addBlockConstructor(const BlockConstructor& constr, const id& blockId)
{
	registeredConstructors[blockId] = constr;
}

const BlockConstructor* Game::getBlockConstructor(const id& blockId)
{
	auto it = registeredConstructors.find(blockId);

	if (it == registeredConstructors.end())
		return NULL;
	else
		return &(it->second);
}

Block* Game::Chunk::getBlockUnsafe(const Core::uvec3 pos)
{
	auto out = blocks[(pos.x << 8) + (pos.y << 4) + pos.z];
	return (Block*)(out == NULL ? Game::getAirBlock() : out);
}

void Game::Chunk::setCreatedBlock(Block* block, const Core::uvec3 pos)
{
	if (blocks[(pos.x << 8) + (pos.y << 4) + pos.z] != NULL)
		delete blocks[(pos.x << 8) + (pos.y << 4) + pos.z];

	blocks[(pos.x << 8) + (pos.y << 4) + pos.z] = block;
}

Block* Game::Chunk::getBlock(const Core::uvec3& blockPos)
{
	bool good = true;

	if (blockPos.x > 15) {
		good = false;
		if (sides[EAST] != NULL)
			return sides[EAST]->getBlock(blockPos - uvec3(16, 0, 0));
	}
	if (blockPos.x < 0) {
		good = false;
		if (sides[WEST] != NULL)
			return sides[WEST]->getBlock(blockPos + uvec3(16, 0, 0));
	}
	if (blockPos.y > 15) {
		good = false;
		if (sides[UP] != NULL)
			return sides[UP]->getBlock(blockPos - uvec3(0, 16, 0));
	}
	if (blockPos.y < 0) {
		good = false;
		if (sides[DOWN] != NULL)
			return sides[DOWN]->getBlock(blockPos + uvec3(0, 16, 0));
	}
	if (blockPos.z > 15) {
		good = false;
		if (sides[SOUTH] != NULL)
			return sides[SOUTH]->getBlock(blockPos - uvec3(0, 0, 16));
	}
	if (blockPos.z < 0) {
		good = false;
		if (sides[NORTH] != NULL)
			return sides[NORTH]->getBlock(blockPos + uvec3(0, 0, 16));
	}

	if (good)
		return getBlockUnsafe(blockPos);
	else
		return (Block*)getAirBlock();
}

Block* Game::Chunk::setBlock(const Core::uvec3& blockPos, const id& blockId)
{
	Block* block = getBlockConstructor(blockId)->operator()(this, blockPos, data());

	setCreatedBlock(block, blockPos);

	return block;
}

std::array<Block*, 6> Game::Chunk::getBlockSides(const Core::uvec3& blockPos)
{
	std::array<Block*, 6> out;

	for (int i = 0; i < 6; i++)
	{
		out[i] = getBlock(blockPos + BlockSidesDeltaPoses[i]);
	}

	return out;
}

void Game::Chunk::updateBlocksAround(const Core::uvec3& centerBlockPos)
{
	for (auto b : getBlockSides(centerBlockPos))
	{
		b->update();
	}
}

Model* Game::Chunk::getModel(Core::Texture* texture)
{
	Model* out = &models[texture];
	out->texture = texture;

	out->polys.clear();
	for (int i = 0; i < 4096; i++)
	{
		if (blocks[i] != NULL)
		{
			for (auto& p : blocks[i]->getModel().polys)
			{
				for (auto& v : p.verts)
					v.pos += Core::uvec3(i >> 8, (i >> 4) & 15, i & 15);
				*out += p;
			}
		}
	}

	return out;
}

Game::Chunk::Chunk()
{
	for (int i = 0; i < 4096; i++)
	{
		blocks[i] = NULL;
	}

	for (auto& c : sides)
		c = NULL;
}

void Game::TestWorldGenerator::fillChunk(Chunk* chunk)
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++) {
			if (j % 4 == 0)
				chunk->setBlock(uvec3(i, 0, j), id("base:glass"));
			else
				chunk->setBlock(uvec3(i, 0, j), id("base:stone_bricks"));
		}
	}
}
