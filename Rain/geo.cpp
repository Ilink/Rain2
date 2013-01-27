#include "geo.h"

Geo::Geo(vector <GLfloat>& verts, vector<int>& triIndex){
	this->triIndex = triIndex;
	this->verts = verts;
	glGenBuffers(1, this->vboGeo);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
};