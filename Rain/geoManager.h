#ifndef GEOMANAGER_H
#define GEOMANAGER_H

#include <GL/glew.h>
#include <vector>
// #include "geo.h"
#include "Artemis-Cpp/Artemis.h"
#include "components/geoComponent.h"
#include "util.h"
#include "types.h"

using namespace std;

/*
GeoManager
This is designed to be the centralized data storage/factory for all geometry.
Right now, I don't want to get bogged down with implementing it.
So it just creates a new VBO and IBO every time the user calls create.
Don't need anything fancy yet.
*/

class GeoManager {
    GLenum error;
    // need a structure to index by ID?
public:
    vector<GLuint> VBOs;
    vector<GLuint> VAOs;
    vector<GLuint> IBOs;
    //vector<geo> geometry;
    GeoManager();
    ~GeoManager();
    GeoComponent* create(vector <vertex>& verts, vector<GLuint>& triIndex);
    void freeAll();
};

#endif