#include "CoreGraphics.h"
#include <fstream>
#include <sstream>
#include "GLCamera.h"

using namespace Core;

Core::Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // Удостоверимся, что ifstream объекты могут выкидывать исключения
    vShaderFile.exceptions(std::ifstream::failbit);
    fShaderFile.exceptions(std::ifstream::failbit);
    try
    {
        // Открываем файлы
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // Считываем данные в потоки
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // Закрываем файлы
        vShaderFile.close();
        fShaderFile.close();
        // Преобразовываем потоки в массив GLchar
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        printf("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n");
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // 2. Сборка шейдеров
    Core::u32 vertex, fragment;
    Core::i32 success;
    char infoLog[512];

    // Вершинный шейдер
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // Если есть ошибки - вывести их
    glGetShaderiv(vertex, GL_COMPILE_STATUS, (GLint*)&success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
    };
    //printf("--VERTEX SHADER--\n%s\n-BEGIN-\n\n%s\n\n-END-\n", vertexPath, vertexCode.c_str());

    // Фрагментный шейдер
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // Если есть ошибки - вывести их
    glGetShaderiv(fragment, GL_COMPILE_STATUS, (GLint*)&success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
    };
    //printf("--FRAGMENT SHADER--\n%s\n-BEGIN-\n\n%s\n\n-END-\n", fragmentPath, fragmentCode.c_str());

    // Шейдерная программа
    this->program = glCreateProgram();
    glAttachShader(this->program, vertex);
    glAttachShader(this->program, fragment);
    glLinkProgram(this->program);
    //Если есть ошибки - вывести их
    glGetProgramiv(this->program, GL_LINK_STATUS, (GLint*)&success);
    if (!success)
    {
        glGetProgramInfoLog(this->program, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    }

    // Удаляем шейдеры, поскольку они уже в программу и нам больше не нужны.
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Core::Shader::use() const
{
    glUseProgram(this->program);
}


void Core::ModelHolder::regen()
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, model->polys.size() * sizeof(polygon), model->polys.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    lastArrayLen = model->polys.size();
}

void Core::ModelHolder::reload(u64 offset, u64 count)
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferSubData(GL_ARRAY_BUFFER, offset, (count == -1 ? lastArrayLen * sizeof(polygon) : count) - offset, model->polys.data());

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Core::ModelHolder::update(u64 offset, u64 count)
{
    if (model->polys.size() == lastArrayLen)
        reload(offset, count);
    else
        regen();
}

Core::ModelHolder::ModelHolder(Model* model) : model(model)
{
    glGenVertexArrays(1, (GLuint*)&VAO);
    glGenBuffers(1, (GLuint*)&VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(f32), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(f32), (void*)(3 * sizeof(f32)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(f32), (void*)(5 * sizeof(f32)));
    glEnableVertexAttribArray(2);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Core::ModelHolder::ModelHolder() : model(new Model())
{
    glGenVertexArrays(1, (GLuint*)&VAO);
    glGenBuffers(1, (GLuint*)&VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(f32), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(f32), (void*)(3 * sizeof(f32)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(f32), (void*)(5 * sizeof(f32)));
    glEnableVertexAttribArray(2);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Core::ModelHolder::~ModelHolder()
{
    glDeleteVertexArrays(1, (GLuint*)&VAO);
    glDeleteBuffers(1, (GLuint*)&VBO);
}



glm::mat4 Camera::getViewMatrix()
{
    if (mode == PERSPECTIVE) {
        //return glm::perspectiveFov(fov, viewport.x, viewport.y, nearClip, farClip) * gameObject->transform.localMatrix;
        return glm::perspectiveFov(fov, (f32)viewport.x, (f32)viewport.y, nearClip, farClip) * glm::mat4_cast(rotation) * glm::translate(glm::mat4(1), -position);
    }
    else {
        return glm::mat4(1);
    }
}

void Core::CameraRenderContext::drawModel(const ModelHolder& modelHolder, const glm::mat4& modelTransform, const Shader& shader)
{
    glBindVertexArray(modelHolder.getVAO());

    u32 u_view = glGetUniformLocation(shader.program, "u_view");
    u32 u_model = glGetUniformLocation(shader.program, "u_model");
    u32 u_textureSizeInTilesInv = glGetUniformLocation(shader.program, "u_textureSizeInTilesInv");

    shader.use();

    //glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(glm::mat4(1)));
    glUniformMatrix4fv(u_view,  1, GL_FALSE, glm::value_ptr(camera->view)  );
    glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(modelTransform));
    glUniform2f(u_textureSizeInTilesInv, (f32)modelHolder.model->texture->pixelsPerUnit / (f32)modelHolder.model->texture->getResolution().x, (f32)modelHolder.model->texture->pixelsPerUnit / (f32)modelHolder.model->texture->getResolution().y);

    glBindTexture(GL_TEXTURE_2D, modelHolder.model->texture->getTexture());

    glDrawArrays(GL_TRIANGLES, 0, modelHolder.model->polys.size() * 3);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}

Core::CameraRenderContext::CameraRenderContext(Camera* camera) : camera(camera) {}
