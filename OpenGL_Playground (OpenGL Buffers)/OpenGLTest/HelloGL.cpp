// HelloGL.
// A test to see if we can write a 3D rendered image in openGL. 
// yes it works and I migh save this project. 

#include <iostream>
#include <fstream>

#include "SDL.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\vec3.hpp"
#include "glm\matrix.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "GL\glew.h"

#include "resource_shaders.h"
#include "resources_cube.h"


#undef main

SDL_Window* win;

// resources
GLfloat verticies[] = { // our openGL triangle.
	-0.5,-0.5,0.0,
	0.5,-0.5,0.0,
	0.0,0.5,0.0
};

// the matracies to pass in for rendering.
glm::mat4 perspective;
glm::mat4 lookAt;
glm::mat4 World; 

GLint perspectiveLocation;
GLint lookAtLocation;
GLint worldLocation;


GLuint program;

int ticks = 0;
Uint32 last = 0, now = SDL_GetTicks();

// set up the matracies to render in 3D. 
void setUpResources() 
{
	GLint success = GL_TRUE;
	GLchar  infoLog[500];

	GLuint vertex_shader;
	GLuint fragment_shader;

	perspective = glm::perspective(glm::radians(90.0f), (16.0f / 9.0f), 0.1f, 1000.0f);
	lookAt = glm::lookAt(glm::vec3(2,1,1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	World = glm::mat4();

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(vertex_shader, sizeof(infoLog), NULL, infoLog);

	glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(fragment_shader, sizeof(infoLog), NULL, infoLog);

	if (success == GL_FALSE) 
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "OpenGL shader compiler Error", infoLog, win);
	}


	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	perspectiveLocation = glGetUniformLocation(program, "perspective");
	lookAtLocation = glGetUniformLocation(program, "lookAt");
	worldLocation = glGetUniformLocation(program, "World");
}

int main(int argc, char* argv[]) 
{
	bool run = true;
	SDL_Init(SDL_INIT_EVERYTHING);

	glm::mat4x4 rotateMatrix;

	GLuint vao;
	GLuint vbo;
	GLuint eao; // eao = Element array object \ index buffer object (indicates the order that vertex arrays should be drawn in).

	// openGL variables go here.

	win = SDL_CreateWindow("HelloGL", 20, 20, 1280, 720, SDL_WINDOW_OPENGL);
	SDL_Event eventQueue;
	SDL_GLContext GLContext = SDL_GL_CreateContext(win);

	if (glewInit() != GLEW_OK)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Damn glew didnt start. NOOOOOOO", win);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetSwapInterval(0);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	// glEnable(GL_CULL_FACE);

	setUpResources();
	setUpCube();

	// set up data buffers so openGL and recieve and send the data to the pipeline.
	glCreateBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferStorage(GL_ARRAY_BUFFER, sizeof(vPositions) + sizeof(vColours), NULL, NULL);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vPositions) + sizeof(vColours), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vPositions), vPositions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vPositions), sizeof(vColours), vColours);

	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexArrayAttrib(vao, 0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (GLvoid*)sizeof(vPositions));
	glEnableVertexArrayAttrib(vao, 1);
	
	last = SDL_GetTicks();

	while (run) 
	{
		while (SDL_PollEvent(&eventQueue))
		{
			switch (eventQueue.type) 
			{
			case SDL_QUIT:
				run = false;
				break;
			case SDL_KEYDOWN:
				if (eventQueue.key.keysym.scancode == SDL_SCANCODE_ESCAPE) 
				{
					run = false;
				}
				break;
			}

		}

		// rotates our triangle in 3D space. 
	    rotateMatrix = glm::rotate(glm::mat4(1.0f), 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
	    World = World * rotateMatrix;
		//lookAt = lookAt * rotateMatrix;

		// Update and render the OpenGL stuff here. 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(program);

		glUniformMatrix4fv(perspectiveLocation, 1, GL_FALSE, glm::value_ptr(perspective));
		glUniformMatrix4fv(lookAtLocation, 1, GL_FALSE, glm::value_ptr(lookAt));
		glUniformMatrix4fv(worldLocation, 1, GL_FALSE, glm::value_ptr(World));

		
		 //glDrawElements(GL_TRIANGLES, 36, GL_INT, (GLvoid*)0);
	    glDrawArrays(GL_TRIANGLES, 0, numVerticies);
		ticks++;

//#ifdef _DEBUG
		now = SDL_GetTicks();
		system("cls");
		std::cout << "Frame Time - " "\x1b[38;5;6" << std::endl;
		last = now;
//#endif

		SDL_GL_SwapWindow(win);
	}

	// cleanup the system. 

	SDL_DestroyWindow(win);
	SDL_GL_DeleteContext(GLContext);
	SDL_Quit();
	return 0;
}