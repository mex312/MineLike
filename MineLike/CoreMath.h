#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <array>

namespace Core
{
	typedef glm::vec2 fvec2;
	typedef glm::vec3 fvec3;
	typedef glm::vec4 fvec4;

	typedef glm::uvec2 uvec2;
	typedef glm::uvec3 uvec3;
	typedef glm::uvec4 uvec4;

	typedef glm::ivec2 ivec2;
	typedef glm::ivec3 ivec3;
	typedef glm::ivec4 ivec4;

	typedef glm::quat  quat;


	typedef unsigned char      byte;
	typedef unsigned char      u8;
	typedef unsigned short     u16;
	typedef unsigned long      u32;
	typedef unsigned long long u64;

	typedef signed char        i8;
	typedef signed short       i16;
	typedef signed long        i32;
	typedef signed long long   i64;

	typedef float              f32;
	typedef long double        f64;


	struct vertex
	{
		fvec3 pos;
		fvec2 uv;
		Core::f32 tex;
	};

	struct polygon
	{
		vertex verts[3];

		vertex& operator[] (int i) { return verts[i]; }
	};

	const byte POLY_SIZE = sizeof(vertex) * 3;

	struct Texture
	{
	private:

		u32 texture;
		uvec2 resolution;

	public:
		u32 pixelsPerUnit;

		u32 getTexture() const { return texture; }
		uvec2 getResolution() const { return resolution; }

		static Texture* LoadFromFile(const char* pathToImage, u32 pixelsPerUnit = 16u);
		
		Texture(u32 texture, uvec2 resolution, u32 pixelsPerUnit = 16u) : resolution(resolution), texture(texture), pixelsPerUnit(pixelsPerUnit) {}

		~Texture();
	};
	
	struct Model
	{
		std::vector<polygon> polys;

		Texture* texture = NULL;

		Model operator+(const polygon& poly);
		Model operator+(const Model& other);

		Model& operator+=(const polygon& poly);
		Model& operator+=(const Model& other);

		static Model LoadFromFile(const char* pathToModel);

		Model() : polys(std::vector<polygon>()) {}
		Model(const Model& original) : polys(original.polys) {}
		Model(const std::list<polygon>& polys) : polys(polys.begin(), polys.end()) {}
		Model(const std::vector<polygon>& polys) : polys(polys) {}
		template<i64 S> Model(const std::array<polygon, S>& polys) : polys(polys) {}
		Model(polygon* polys, i64 size) : polys(polys, polys + size) {}
	};
}