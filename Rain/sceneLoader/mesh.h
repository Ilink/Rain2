#ifndef MESH_H
#define MESH_H

#include <vector>
#include "../types.h"
#include <GL/glew.h>

using namespace std;

struct Mesh {
    vector<GLuint> quadIndexes;
    vector<vertex> verts;
    vector<GLuint> triIndexes;
};

#endif