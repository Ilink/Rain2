#ifndef GEO_H
#define GEO_H

#include <vector>
#include <GL/glew.h>

class Geo {
public:
	GLuint vboGeo;
	// GLuint vboNormals;
	GLuint vao;
	vector<GLfloat> verts;
	vector<int> triIndex;

	Geo(vector <GLfloat>& verts, vector<int>& triIndex);
};

#endif