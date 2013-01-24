#include "geoManager.h"

GeoManager::GeoManager(){

}

// note that we do not destroy verts - they might be modified later.
GeoManager::getGeo(vector <GLfloat>& verts, vector<GLuint>& triIndex){
	GLuint vboGeo = highestVBO+1;
	GLuint vao = highestVAO+1; // until i have things working i am not going to bother using VAOs
	highestVAO++;
	highestVBO++;

	glGenBuffers(1, &vboGeo);
	glGenVertexArrays(1, &vao);

	glBindBuffer(GL_ARRAY_BUFFER, vboGeo);
	glBindVertexArray(vao);

	// do the rest of the initialization..

	// unused until i actually start doing batched geometry stuff
	// this->vboGeos.push(vboGeo);
	// this->VAOs.push(vao);

	return new GeoComponent(verts, triIndex, &vbo, &triIndexBuffer, &vao);
}