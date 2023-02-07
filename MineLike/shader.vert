#version 330 core

layout (location = 0) in vec3 raw_position;
layout (location = 1) in vec2 raw_uv;
layout (location = 2) in float raw_textureTileNum;

uniform mat4 u_view;
uniform mat4 u_model;
uniform vec2 u_textureSizeInTilesInv;

out vec2 real_uv;

//out vec4 test_pos;

void main()
{
	gl_Position = u_view * u_model * vec4(raw_position, 1.0f);
	//gl_Position = u_model * vec4(raw_position, 1.0f);

	float n = raw_textureTileNum * u_textureSizeInTilesInv.x;
	float m = n - floor(n);
	vec2 pos = vec2(m, floor(n) * u_textureSizeInTilesInv.y);

	real_uv = raw_uv * u_textureSizeInTilesInv + pos;

	//test_pos = u_view * u_model * vec4(raw_position, 1.0f)

	//test_pos = u_view * vec4(raw_position, 1.0f);
	//gl_Position = vec4(raw_position, 1.0f);
	//real_uv = raw_uv;
}