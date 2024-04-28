#include "../header_files/shaders.hpp"

GLuint createProgram(char* vertexFile, char* fragmentFile) {
	int success;
	char infoLog[512];

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	GLchar* vertexShader = readShaderSource(vertexFile);
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, (const char**)&vertexShader, NULL);
	glCompileShader(vertexShaderId);

	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
		glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);

	GLchar* fragmentShader = readShaderSource(fragmentFile);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, (const char**)&fragmentShader, NULL);
	glCompileShader(fragmentShaderId);


	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
		glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not create the shaders: %s \n",
			gluErrorString(error)
		);
		exit(-1);
	}

	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	return programId;
}

char* readShaderSource(char* shaderFile)
{
	FILE* fp = fopen(shaderFile, "rb");
	if (fp == NULL)
		return NULL;

	fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);

	fseek(fp, 0L, SEEK_SET);
	char* buf = new char[size + 1];
	fread(buf, 1, size, fp);

	buf[size] = '\0';
	fclose(fp);

	return buf;
}