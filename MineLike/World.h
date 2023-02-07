#pragma once

#include "CoreMath.h"
#include "Containers.h"

namespace Game
{

	__interface Block;
	class Chunk;
	class World;




	typedef std::function<Block* (Chunk*, const Core::uvec3&, const data&)> BlockConstructor;

	void addBlockConstructor(const BlockConstructor& constr, const id& blockId);

	template<class T>
	void registerNewBlock(const id& blockId)
	{
		addBlockConstructor(BlockConstructor([](Chunk* chunk, const Core::uvec3& posInChunk, const data& additionalNBT) -> Block* { return new T(chunk, posInChunk, additionalNBT); }), blockId);
	}

	const BlockConstructor* getBlockConstructor(const id& blockId);






	enum BlockSides
	{
		NORTH,
		SOUTH,
		EAST,
		WEST,
		UP,
		DOWN
	};

	static const Core::uvec3 BlockSidesDeltaPoses[6] = {
		Core::uvec3(0, 0, -1),
		Core::uvec3(0, 0, 1),
		Core::uvec3(1, 0, 0),
		Core::uvec3(-1, 0, 0),
		Core::uvec3(0, 1, 0),
		Core::uvec3(0, -1, 0)
	};

	__interface Block
	{
		void update();
		
		const properties* getProperties();
		const id* getId();
		data* getNBT();
		Core::Model getModel();
	};

	class Chunk
	{
	private:
		Chunk* sides[6];
		Block* blocks[4096];

		std::map<Core::Texture*, Core::Model> models = std::map<Core::Texture*, Core::Model>();

		Core::uvec3 position;

		Block* getBlockUnsafe(const Core::uvec3 pos);

		void setCreatedBlock(Block* block, const Core::uvec3 pos);

	public:
		Block* getBlock(const Core::uvec3& blockPos);
		Block* setBlock(const Core::uvec3& blockPos, const id& blockId);

		Core::uvec3 getPosition() { return position; }

		std::array<Block*, 6> getBlockSides(const Core::uvec3& blockPos);

		void updateBlocksAround(const Core::uvec3& centerBlockPos);

		Core::Model* getModel(Core::Texture* texture);

		Chunk();
	};


	__interface WorldGenerator
	{
		void fillChunk(Chunk* chunk);
	};

	class TestWorldGenerator : public WorldGenerator
	{
	public:
		void fillChunk(Chunk* chunk);
	};
}