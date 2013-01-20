#ifndef UTIL_H
#define UTIL_H

#include <fstream>
#include <streambuf>
#include <string>
#include <cerrno>

std::string getFileContents(const char *filename);

#endif