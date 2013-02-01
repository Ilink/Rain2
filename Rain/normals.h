#ifndef NORMALS_H
#define NORMALS_H

#include "util.h"
#include "types.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

using namespace std;
void calcFaceNormals(vector <vertex>& verts, vector<GLuint>& triIndex);

#endif