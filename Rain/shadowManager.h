#ifndef SHADOW_MANAGER_H
#define SHADOW_MANAGER_H 

#include <GL/glew.h>
#include <vector>
#include "Artemis-Cpp/Artemis.h"
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
    vector<GLuint> shadowMaps;
    GeoManager();
    ~GeoManager();
    GeoComponent* create(int width, int height);
    void freeAll();
};

#endif