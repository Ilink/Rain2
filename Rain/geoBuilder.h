#ifndef GEOBUILDER_H
#define GEOBUILDER_H

#include "util.h"
#include "types.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "components/geoComponent.h"

using namespace std;
void makeBox(double height, double width, double depth, vector <vertex>& verts, vector<GLuint>& triIndex);
void makePlane(double height, double width, double depth, vector <vertex>& verts, vector<GLuint>& triIndex);
// geoComponent makeBox(double height, double width, double depth, vector <vertex>& verts, vector<GLuint>& triIndex);


#endif