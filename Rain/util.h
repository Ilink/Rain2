#ifndef UTIL_H
#define UTIL_H

#include <fstream>
#include <streambuf>
#include <string>
#include <cerrno>
#include <GL/glew.h>

std::string getFileContents(const char *filename);
void printGlError(GLenum error);

#endif