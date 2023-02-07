#include <stdio.h>
#include <fstream>
#include "Game.h"

using namespace Core;
using namespace Game;


void writeModelToFile(const Model& model, const char* fileName)
{
	std::ofstream file(fileName, std::ios_base::binary);

	file.write((char*)model.polys.data(), model.polys.size() * sizeof(polygon));

	file.close();
}








int main() {
	init();
	initGame();

	/*
	Model model(std::vector<polygon>
	{
		{ //NORTH
			{
				{ {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f},  0.0f },
				{ {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f},  0.0f },
				{ {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f},  0.0f },
			}
		},
		{
			{
				{ {1.0f, 1.0f, 0.0f}, {0.0f, 0.0f},  0.0f },
				{ {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f},  0.0f },
				{ {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f},  0.0f },
			}
		},
		{ //SOUTH
			{
				{ {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f},  0.0f },
				{ {1.0f, 0.0f, 1.0f}, {1.0f, 1.0f},  0.0f },
				{ {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f},  0.0f },
			}
		},
		{
			{
				{ {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f},  0.0f },
				{ {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f},  0.0f },
				{ {1.0f, 0.0f, 1.0f}, {1.0f, 1.0f},  0.0f },
			}
		},
		{ //EAST
			{
				{ {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f},  0.0f },
				{ {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f},  0.0f },
				{ {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f},  0.0f },
			}
		},
		{
			{
				{ {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f},  0.0f },
				{ {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f},  0.0f },
				{ {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f},  0.0f },
			}
		},
		{ //WEST
			{
				{ {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f},  0.0f },
				{ {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f},  0.0f },
				{ {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f},  0.0f },
			}
		},
		{
			{
				{ {0.0f, 1.0f, 1.0f}, {1.0f, 0.0f},  0.0f },
				{ {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f},  0.0f },
				{ {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f},  0.0f },
			}
		},
		{ //UP
			{
				{ {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f},  0.0f },
				{ {0.0f, 1.0f, 1.0f}, {0.0f, 1.0f},  0.0f },
				{ {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f},  0.0f },
			}
		},
		{
			{
				{ {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f},  0.0f },
				{ {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f},  0.0f },
				{ {0.0f, 1.0f, 1.0f}, {0.0f, 1.0f},  0.0f },
			}
		},
		{ //DOWN
			{
				{ {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f},  0.0f },
				{ {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f},  0.0f },
				{ {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f},  0.0f },
			}
		},
		{
			{
				{ {1.0f, 0.0f, 1.0f}, {1.0f, 0.0f},  0.0f },
				{ {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f},  0.0f },
				{ {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f},  0.0f },
			}
		},
	});

	writeModelToFile(model, "CubeModel.model");
	*/

	//writeModelToFile(model, "Mystery.model");

	Camera camera(PERSPECTIVE);
	CameraRenderContext context(&camera);
	Shader shader("shader.vert", "shader.frag");

	//float rot = glm::pi<f32>() * 2.0f / 2.0f;
	fvec2 rot(0, 0);

	Chunk chunk;
	TestWorldGenerator wGen;
	wGen.fillChunk(&chunk);

	float time = 0;
	u32 frames = 0;

	while (true) {
		glfwPollEvents();
		Input::updateInput();
		Time::updateTime();

		time += Time::deltaTime();
		frames++;

		if (time >= 1)
		{
			time--;

			printf("%u\n", frames);

			frames = 0;
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		rot.y += Input::getMouseInput().x / 300.0f;
		rot.x += Input::getMouseInput().y / 300.0f;

		camera.rotation = glm::normalize(quat(fvec3(rot.x, 0, 0)) * quat(fvec3(0, rot.y, 0)));

		fvec3 deltaPos(0, 0, 0);
		if (Input::getKey(GLFW_KEY_D)) {
			deltaPos.x++;
		}
		if (Input::getKey(GLFW_KEY_A)) {
			deltaPos.x--;
		}
		if (Input::getKey(GLFW_KEY_W)) {
			deltaPos.z--;
		}
		if (Input::getKey(GLFW_KEY_S)) {
			deltaPos.z++;
		}
		if (Input::getKey(GLFW_KEY_SPACE)) {
			deltaPos.y++;
		}
		if (Input::getKey(GLFW_KEY_LEFT_SHIFT)) {
			deltaPos.y--;
		}

		if (Input::getKeyDown(GLFW_KEY_Q)) printf("Q\n");

		camera.position += (deltaPos * (f32)Time::deltaTime() * 2.0f) * camera.rotation;

		//Model* chunkModel = chunk.getModelHolder(getBaseTexture());

		//ModelHolder holder(chunkModel);
		//holder.update();

		context.drawModel(*chunk.getModelHolder(getBaseTexture()), glm::translate(glm::mat4(1), fvec3(0, 0, 0)), shader);

		glfwSwapBuffers(getMainWindow());
	}
}