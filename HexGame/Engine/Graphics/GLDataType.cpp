#include <Engine/Graphics/GLDataType.hpp>

unsigned int getGLDataTypeSize(GLDataType value)
{
	switch (value)
	{
	case GLDataType::Int:
		return 4;
		break;
	case GLDataType::Bool:
		return 1;
		break;
	case GLDataType::Float1:
		return 4;
		break;
	case GLDataType::Float2:
		return 4 * 2;
		break;
	case GLDataType::Float3:
		return 4 * 3;
		break;
	case GLDataType::Float4:
		return 4 * 4;
		break;
	case GLDataType::Mat3:
		return 4 * 3 * 3;
		break;
	case GLDataType::Mat4:
		return 4 * 4 * 4;
		break;
	}
}

unsigned int getGLDataTypeElementsCount(GLDataType value)
{
	switch (value)
	{
	case GLDataType::Int:
		return 1;
		break;
	case GLDataType::Bool:
		return 1;
		break;
	case GLDataType::Float1:
		return 1;
		break;
	case GLDataType::Float2:
		return 2;
		break;
	case GLDataType::Float3:
		return 3;
		break;
	case GLDataType::Float4:
		return 4;
		break;
	case GLDataType::Mat3:
		return 3 * 3;
		break;
	case GLDataType::Mat4:
		return 4 * 4;
		break;
	}
}

GLenum getGLDataTypeToBaseOpenGLType(GLDataType value)
{
	switch (value)
	{
	case GLDataType::Int:
		return GL_INT;
		break;
	case GLDataType::Bool:
		return GL_BOOL;
		break;
	case GLDataType::Float1:
		return GL_FLOAT;
		break;
	case GLDataType::Float2:
		return GL_FLOAT;
		break;
	case GLDataType::Float3:
		return GL_FLOAT;
		break;
	case GLDataType::Float4:
		return GL_FLOAT;
		break;
	case GLDataType::Mat3:
		return GL_FLOAT;
		break;
	case GLDataType::Mat4:
		return GL_FLOAT;
		break;
	}
}
