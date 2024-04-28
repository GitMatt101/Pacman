#pragma once
#include "../lib.h"

GLuint createProgram(char* vertexFile, char *fragmentFile);

char* readShaderSource(char* shaderFile);