#pragma once

#include "SDL.h"
#include "GL\glew.h"

const int numVerticies = 36;
int index = 0;

// arrays which will store the verticies of the cube.
glm::vec4  vPositions[numVerticies];
glm::vec4  vColours[numVerticies];


glm::vec4 cubePositions[8] = {
	glm::vec4(-0.5f,-0.5f, 0.5f, 1.0f),
	glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f),
	glm::vec4(0.5f , 0.5f, 0.5f, 1.0f),
	glm::vec4( 0.5f,-0.5f, 0.5f, 1.0f),
	glm::vec4(-0.5f,-0.5f,-0.5f, 1.0f),
	glm::vec4(-0.5f, 0.5f,-0.5f, 1.0f),
	glm::vec4( 0.5f, 0.5f,-0.5f, 1.0f),
	glm::vec4( 0.5f,-0.5f,-0.5f, 1.0f)
};

glm::vec4 cubeColours[8] = {
	glm::vec4(0.0, 0.0, 0.0, 1.0),
	glm::vec4(1.0, 0.0, 0.0, 1.0),
	glm::vec4(0.0, 1.0, 0.0, 1.0),
	glm::vec4(0.0, 0.0, 1.0, 1.0),
	glm::vec4(1.0, 0.0, 1.0, 1.0),
	glm::vec4(1.0, 1.0, 1.0, 1.0),
	glm::vec4(1.0, 1.0, 0.0, 1.0),
	glm::vec4(0.0, 1.0, 1.0, 1.0),
};

GLint vboIndex[24] = {
	1, 0, 3, 2,
	2, 3, 7, 6,
	3, 0, 4, 7,
	6, 5, 1, 2,
	4, 5, 6, 7,
	5, 4, 0, 1,
};

void createCubeQuads(int VertexA, int VertexB, int VertexC, int VertexD)
{
	vColours[index] = cubeColours[VertexA]; vPositions[index] = cubePositions[VertexA]; index++;
	vColours[index] = cubeColours[VertexB]; vPositions[index] = cubePositions[VertexB]; index++;
	vColours[index] = cubeColours[VertexC]; vPositions[index] = cubePositions[VertexC]; index++;
	vColours[index] = cubeColours[VertexA]; vPositions[index] = cubePositions[VertexA]; index++;
	vColours[index] = cubeColours[VertexC]; vPositions[index] = cubePositions[VertexC]; index++;
	vColours[index] = cubeColours[VertexD]; vPositions[index] = cubePositions[VertexD]; index++;
}


void setUpCube() 
{
	createCubeQuads(1, 0, 3, 2);
	createCubeQuads(2, 3, 7, 6);
	createCubeQuads(3, 0, 4, 7);
	createCubeQuads(6, 5, 1, 2);
	createCubeQuads(4, 5, 6, 7);
	createCubeQuads(5, 4, 0, 1);
}