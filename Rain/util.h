#ifndef UTIL_H
#define UTIL_H

#include <fstream>
#include <streambuf>
#include <string>
#include <cerrno>
#include <GL/glew.h>
#include "types.h"

std::string getFileContents(const char *filename);
void printGlError();
void vaoSetup(GLuint& vao, GLuint& vbo, GLuint& ibo);
void printFboErrors(char* name);

#endif