#version 330 core

out vec4 color;

uniform sampler2D u_texture;

uniform vec2 u_textureSizeInTilesInv;

in vec2 real_uv;

//in vec4 test_pos;

void main()
{
	color = texture(u_texture, vec2(real_uv.x - floor(real_uv.x), real_uv.y + floor(real_uv.x) * u_textureSizeInTilesInv.y));
	if(color.a <= 0.0f) {
		//color = vec4(0, 0, 0, 1);
		discard;
	}

	//color = vec4(test_pos.xyz / 1000000000, 1);

	//color = vec4(0, 0, 0, 1);
}