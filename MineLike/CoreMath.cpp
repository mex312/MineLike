#include "CoreMath.h"
#include <fstream>

using namespace Core;

Model Model::operator+(const polygon& poly)
{
	Model out(*this); 
	out.polys.push_back(poly); 
	return out;
}

Model Core::Model::operator+(const Model& other)
{
	Model out(*this);
	for (auto p : other.polys)
	{
		out += p;
	}
	return out;
}

Model& Core::Model::operator+=(const polygon& poly)
{
	polys.push_back(poly);
	return *this;
}

Model& Core::Model::operator+=(const Model& other)
{
	for (auto p : other.polys)
	{
		*this += p;
	}
	return *this;
}

Model Core::Model::LoadFromFile(const char* pathToModel)
{
	std::ifstream file(pathToModel, std::ios_base::binary);

	u64 size;

	file.seekg(0, std::ios_base::_Seekend);
	size = file.tellg();
	size -= size % sizeof(polygon);
	file.seekg(0, std::ios_base::_Seekbeg);

	byte* buffer = new byte[size];

	file.read((char*)buffer, size);

	Model out = Model(std::vector<polygon>((polygon*)buffer, (polygon*)(buffer + size)));

	delete[] buffer;
	file.close();

	return out;
}

Texture* Core::Texture::LoadFromFile(const char* pathToImage, u32 pixelsPerUnit)
{
	u32 width, height;
	unsigned char* image = SOIL_load_image(pathToImage, (int*)&width, (int*)&height, 0, SOIL_LOAD_RGBA);
	uvec2 resolution = { width, height };

	u32 texture;
	glGenTextures(1, (GLuint*)&texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	return new Texture(texture, resolution, pixelsPerUnit);
}

Core::Texture::~Texture()
{
	glDeleteTextures(1, (GLuint*)&texture);
}
