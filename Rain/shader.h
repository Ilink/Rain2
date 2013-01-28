#ifndef SHADER_H
#define SHADER_H

#include "GLCheck.hpp"
#include <SFML/OpenGL.hpp>
#include <string>
#include <fstream>
#include <vector>
#include <SFML/System.hpp>
#include "util.h"
#include "types.h"

using namespace std;

class Shader {
private:
	bool compile(string& vs, string& fs);
	GLenum error;
public:
	Shader(const char* vsFilename, const char* fsFilename);
	Shader();
	~Shader();
	bool load(const char* vsFilename, const char* fsFilename);
	bool bind();
	bool unbind();
	bool setParam(const std::string& name, const float& mat);

	unsigned int program; // public for now
};

#endif