#ifndef GEOMANAGER_H
#define GEOMANAGER_H

#include <vector>
#include <GL/glew.h>

class GeoManager(){
	vector<GLuint> VBOs;
	vector<GLuint> VAOs;
	db index;
public:
	GeoManager();
	~GeoManager();
	start, end, geo get(enum geoToFetch); // so you can draw with start end and the vbo
}

#endif