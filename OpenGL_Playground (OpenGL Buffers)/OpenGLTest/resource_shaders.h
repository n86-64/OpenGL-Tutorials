#pragma once

#include "SDL.h"
#include "GL\glew.h"


// TODO - check to see if two shaders are needed
const GLchar* vertex_shader_source[] = {
	"#version 410 core                       \n"
	"                                        \n"
	"layout (location = 0) in vec4 position; \n"
	"layout (location = 1) in vec4 colours;  \n"
	"                                        \n"
	"uniform mat4  perspective;              \n"
	"uniform mat4  lookAt;                   \n"
	"uniform mat4  World;                    \n"
	"                                        \n"
	"                                        \n"
	"void main(void)                         \n"
	"{                                       \n"
	"    gl_Position = perspective * lookAt * World * position;  \n"
	"}                                       \n"
	"                                        \n"
};

const GLchar* fragment_shader_source[] = {
	"#version 410 core               \n"
	"                                \n"
	"                                \n"
	"void main(void)                 \n"
	"{                               \n"
	"    gl_FragColor =  vec4(1.0,1.0,1.0,1.0); \n"
	"}                               \n"
	"                                \n"
};