#include <Engine/Graphics/Shader.hpp>

#include <iostream>
#include <sstream>

Shader::Shader(const std::string& pathToVertex, const std::string& pathToFrag)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream VertexShaderFile;
	std::ifstream FragmentShaderFile;

	VertexShaderFile.exceptions(std::ifstream::badbit);
	FragmentShaderFile.exceptions(std::ifstream::badbit);

	VertexShaderFile.open(pathToVertex);
	FragmentShaderFile.open(pathToFrag);

	std::stringstream VertexShaderStream, FragmentShaderStream;

	VertexShaderStream << VertexShaderFile.rdbuf();
	FragmentShaderStream << FragmentShaderFile.rdbuf();

	VertexShaderFile.close();
	FragmentShaderFile.close();

	vertexCode = VertexShaderStream.str();
	fragmentCode = FragmentShaderStream.str();

	const char* VertexShaderCode = vertexCode.c_str();
	const char* FragmentShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;

	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &VertexShaderCode, NULL);
	glCompileShader(vertex);

	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &FragmentShaderCode, NULL);
	glCompileShader(fragment);

	// Shader program
	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{
	glDeleteProgram(id);
}

void Shader::bind()
{
	glUseProgram(id);
}

void Shader::unbind()
{
	glUseProgram(0);
}

void Shader::setInt(const std::string& uniform, int value)
{
	glUniform1i(glGetUniformLocation(id, uniform.c_str()), value);
}

void Shader::setFloat(const std::string& uniform, float value)
{
	glUniform1f(glGetUniformLocation(id, uniform.c_str()), value);
}

void Shader::setVec2(const std::string& uniform, const glm::vec2& value)
{
	glUniform2fv(glGetUniformLocation(id, uniform.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec3(const std::string& uniform, const glm::vec3& value)
{
	glUniform3fv(glGetUniformLocation(this->id, uniform.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec4(const std::string& uniform, const glm::vec3& value)
{
	glUniform4fv(glGetUniformLocation(id, uniform.c_str()), 1, glm::value_ptr(value));
}

void Shader::setMat4(const std::string& uniform, const glm::mat4& value)
{
	int loc = glGetUniformLocation(id, uniform.c_str());
	if (loc != GL_INVALID_OPERATION)
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}
