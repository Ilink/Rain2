#include "geoManager.h"

using namespace std;

GeoManager::GeoManager(){

}

GeoManager::~GeoManager(){

}

// note that we do not destroy verts - they might be modified later.
GeoComponent* GeoManager::create(vector <GLfloat>& verts, vector<GLuint>& triIndex){
    // GLuint vbo, ibo, vao;

    this->VBOs.push_back((GLuint) this->VBOs.size()+1);
    this->IBOs.push_back((GLuint) this->IBOs.size()+1);
	this->VAOs.push_back((GLuint) this->VAOs.size()+1);

	glGenBuffers(1, &this->VBOs.back());
	glBindBuffer(GL_ARRAY_BUFFER, this->VBOs.back());
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*9, &verts, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &this->IBOs.back());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBOs.back());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(GLfloat), &triIndex, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unused until i actually start doing batched geometry stuff
	// this->vboGeos.push(vboGeo);
	// this->VAOs.push(vao);

	// GeoComponent* geo = new GeoComponent(verts, -1, -1, this->VBOs.back(), this->IBOs.back());
    return new GeoComponent(verts, -1, -1, this->VBOs.back(), this->IBOs.back(), this->VAOs.back());
    // return new GeoComponent(verts, -1, -1, (GLuint) 0, (GLuint) 0);
}