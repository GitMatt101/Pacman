#pragma once
#include "../lib.hpp"

GLuint createProgram(char* vertexFile, char *fragmentFile);

char* readShaderSource(char* shaderFile);