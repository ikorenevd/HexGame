#pragma once

#include <Engine/Core/OpenGL.hpp>

enum class GLDataType
{
	Int = 0,
	Bool,
	Float1,
	Float2,
	Float3,
	Float4,
	Mat3,
	Mat4
};

unsigned int getGLDataTypeSize(GLDataType value);

unsigned int getGLDataTypeElementsCount(GLDataType value);

GLenum getGLDataTypeToBaseOpenGLType(GLDataType value);
