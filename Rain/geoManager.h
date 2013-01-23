#ifndef GEOMANAGER_H
#define GEOMANAGER_H

#include <vector>
#include <GL/glew.h>

struct geo {
	int start;
	int end;
	GLuint vbo;
	vector<int> triIndex;
};

class GeoManager {
	vector<GLuint> VBOs;
	vector<GLuint> VAOs;
	int highestVBO = 0;
	int highestVAO = 0;
	// need a structure to index by ID
public:
	GeoManager();
	~GeoManager();
	int add(vector <GLfloat> verts, vector<int> triIndex); // returns an ID of the inserted geometry or -1 if fail
	geo get(int id);
};

/*
data structure needs to hold:
	vbo & vao & start & end
indexed by
	id

probably other things as well. Until I need it, im not making it!
*/

#endif