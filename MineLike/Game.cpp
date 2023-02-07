#include "Game.h"

using namespace Core;
using namespace Game;

Texture* NULL_TEXTURE;
Texture* BASE_TEXTURE;

const Model CUBE_MODEL = Model::LoadFromFile("CubeModel.model");

const properties EMPTY = properties();
const properties SOLID = properties{ "solid" };


const id AIR_ID = id("base:air");
class AirBlock : public Block
{
public:
	void update() {}

	const properties* getProperties() { return &EMPTY; }
	const id* getId() { return &AIR_ID; }
	data* getNBT() { return NULL; }
	Core::Model getModel() { return Model(); }

	AirBlock() {}
	AirBlock(Chunk* chunk, const Core::uvec3& posInChunk, const data& additionalData) {}
};


const id STONE_BRICKS_ID = id("base:stone_bricks");
class StoneBricksBlock : public Block
{
public:
	Core::uvec3 pos;
	Chunk* chunk;

	void update() {}

	const properties* getProperties() { return &SOLID; }
	const id* getId() { return &STONE_BRICKS_ID; }
	data* getNBT() { return NULL; }
	Core::Model getModel() {
		Model model = Model(std::vector<polygon>());

		auto pals = chunk->getBlockSides(pos);

		for (int i = 0; i < 6; i++)
		{
			if (!pals[i]->getProperties()->has("solid"))
			{
				model += CUBE_MODEL.polys[i * 2];
				for (auto& v : model.polys[model.polys.size() - 1].verts) v.tex = 1;
				model += CUBE_MODEL.polys[i * 2 + 1];
				for (auto& v : model.polys[model.polys.size() - 1].verts) v.tex = 1;
			}
		}

		return model;
	}

	StoneBricksBlock(Chunk* chunk, const Core::uvec3& posInChunk, const data& additionalData) : chunk(chunk), pos(posInChunk) {}
};


const properties GLASS_PROPERTIES = properties{ "glass" };
const id GLASS_ID = id("base:glass");
class GlassBlock : public Block
{
public:
	Core::uvec3 pos;
	Chunk* chunk;

	void update() {}

	const properties* getProperties() { return &GLASS_PROPERTIES; }
	const id* getId() { return &STONE_BRICKS_ID; }
	data* getNBT() { return NULL; }
	Core::Model getModel() {
		Model model = Model(std::vector<polygon>());

		auto pals = chunk->getBlockSides(pos);

		for (int i = 0; i < 6; i++)
		{
			if (!pals[i]->getProperties()->has("solid") && !pals[i]->getProperties()->has("glass"))
			{
				model += CUBE_MODEL.polys[i * 2];
				for (auto& v : model.polys[model.polys.size() - 1].verts) v.tex = 2;
				model += CUBE_MODEL.polys[i * 2 + 1];
				for (auto& v : model.polys[model.polys.size() - 1].verts) v.tex = 2;
			}
		}

		return model;
	}

	GlassBlock(Chunk* chunk, const Core::uvec3& posInChunk, const data& additionalData) : chunk(chunk), pos(posInChunk) {}
};


void Game::initGame()
{
	registerNewBlock<AirBlock>(AIR_ID);
	registerNewBlock<StoneBricksBlock>(STONE_BRICKS_ID);
	registerNewBlock<GlassBlock>(GLASS_ID);

	NULL_TEXTURE = Texture::LoadFromFile("ZeroTexture.png");
	BASE_TEXTURE = Texture::LoadFromFile("Textures.png");
}


const AirBlock AIR_BLOCK = AirBlock();
const Block* Game::getAirBlock()
{
	return &AIR_BLOCK;
}

Core::Texture* Game::getBaseTexture()
{
	return BASE_TEXTURE;
}

Core::Texture* Game::getNullTexture()
{
	return NULL_TEXTURE;
}
