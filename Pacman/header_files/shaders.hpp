#pragma once
#include "../lib.hpp"

/**
* Creates the program id for the application.
* 
* @param vertexFile - Name of the vertex shader file.
* @param fragmentFile - Name of the fragment shader file.
* @return the program's id.
*/
GLuint createProgram(char* vertexFile, char *fragmentFile);