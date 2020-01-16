#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <Engine/Core/OpenGL.hpp>

#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader(const std::string& vertexFile, const std::string& fragmentFile);

	~Shader();

	void bind();
	void unbind();

	void setInt(const std::string& uniform, int value);

	void setFloat(const std::string& uniform, float value);
	void setVec2(const std::string& uniform, const glm::vec2& value);
	void setVec3(const std::string& uniform, const glm::vec3& value);
	void setVec4(const std::string& uniform, const glm::vec3& value);

	void setMat4(const std::string& uniform, const glm::mat4& value);
private:
	unsigned int id;

	void linkProgram(unsigned int vertShader, unsigned int fragShader);
};
