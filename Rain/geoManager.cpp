#include "geoManager.h"

GeoManager::GeoManager(){

}

GeoManager::add(vector <GLfloat> verts, vector<int> triIndex){
	GLuint vbo = 0;
	GLuint vao = 0;

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray(vao);
	// this->VBOs.push(VBO);
}