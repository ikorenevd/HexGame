#include <Engine/Graphics/Shader.hpp>

#include <iostream>
#include <sstream>

static const std::string& loadShaderSource(const std::string& fileName)
{
	auto ss = std::ostringstream{};
	std::ifstream file(fileName);
	ss << file.rdbuf();
	return ss.str();
}

static unsigned int loadShader(GLenum type, const std::string& fileName)
{
	char infoLog[512];
	int success;

	unsigned int shader = glCreateShader(type);
	std::string str_src = loadShaderSource(fileName);

	const char* src = str_src.c_str();
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::clog << "ERROR: CANT COMPILE SHADER" << fileName << "\n";
		std::clog << infoLog << "\n";
	}

	return shader;
}

void Shader::linkProgram(unsigned int vertShader, unsigned int fragShader)
{
	char infoLog[512];
	GLint success;

	id = glCreateProgram();

	glAttachShader(id, vertShader);
	glAttachShader(id, fragShader);

	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR: CANT LINK SHADER"<< "\n";
		std::cout << infoLog << "\n";
	}

	glUseProgram(0);
}

Shader::Shader(const std::string& pathToVertex, const std::string& pathToFrag)
{
	unsigned int vertShader = 0;
	unsigned int fragShader = 0;

	vertShader = loadShader(GL_VERTEX_SHADER, pathToVertex);
	fragShader = loadShader(GL_FRAGMENT_SHADER, pathToFrag);

	linkProgram(vertShader, fragShader);

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
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
	glUniformMatrix4fv(glGetUniformLocation(id, uniform.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
