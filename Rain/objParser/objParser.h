#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H

#include <vector>
#include <string>
#include <iostream>
#include <istream>
#include <fstream>
#include "../types.h"
#include <sstream>

using namespace std;

struct mesh {
    vector<vertex> verts;
    vector<GLuint> indexes;
};

struct pos {
    GLfloat x, y, z;
};

struct tex {
    GLfloat u, v;
};

struct normal {
    GLfloat nx, ny, nz;
};

extern void parseObj(string filename, vector<mesh>& meshes);

#endif