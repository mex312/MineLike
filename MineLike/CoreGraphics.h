#pragma once
#include "CoreMath.h"

namespace Core
{

	class Shader
	{
	public:
		u32 program;

		Shader(const char* vertexPath, const char* fragmentPath);

		void use() const;

		~Shader() { glDeleteProgram(program); }
	};


	enum Camera_Modes {
		PERSPECTIVE,
		ORTHOGRAPHIC
	};

	class Camera
	{
	public:
		quat rotation = quat(fvec3(0, 0, 0));
		fvec3 position = fvec3(0, 0, 0);

		Camera_Modes mode;
		f32 fov = 1.5f;
		uvec2 viewport = uvec2(800u, 600u);
		f32 nearClip = 0.1f;
		f32 farClip = 10000.0f;

		glm::mat4 getViewMatrix();

		_declspec (property(get = getViewMatrix)) glm::mat4 view;

		Camera(Camera_Modes mode) : mode(mode) {}
	};

	class ModelHolder
	{
	private:
		u32 VAO;
		u32 VBO;

		u64 lastArrayLen = 0;

		void regen();
		void reload(u64 offset, u64 count);

	public:
		Model* model;

		void update(u64 offset = 0, u64 count = -1);

		u32 getVAO() const { return VAO; }
		u32 getVBO() const { return VBO; }

		ModelHolder(Model* model);
		ModelHolder();

		~ModelHolder();
	};





	__interface RenderContext
	{
		void drawModel(const ModelHolder& modelHolder, const glm::mat4& modelTransform, const Shader& shader);
	};


    class CameraRenderContext : public RenderContext
    {
        Camera* camera;

    public:
        void drawModel(const ModelHolder& modelHolder, const glm::mat4& modelTransform, const Shader& shader);

        CameraRenderContext(Camera* camera);
    };

}