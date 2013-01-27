#ifndef GEOMANAGER_H
#define GEOMANAGER_H

#include <GL/glew.h>
#include <vector>
// #include "geo.h"
#include "Artemis-Cpp/Artemis.h"
#include "components/geoComponent.h"


using namespace std;

struct basicGeo {
    int start;
    int end;
    GLuint vbo; // ref
    GLuint vao; // ref
    GLuint ibo; // ref
};

class GeoManager {
    // need a structure to index by ID?
public:
    vector<GLuint> VBOs;
    vector<GLuint> VAOs;
    vector<GLuint> IBOs;
    //vector<geo> geometry;
    GeoManager();
    ~GeoManager();
    GeoComponent* create(vector <GLfloat>& verts, vector<GLuint>& triIndex);
};

#endif