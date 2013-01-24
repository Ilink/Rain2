#ifndef GEOMANAGER_H
#define GEOMANAGER_H

#include <vector>
#include "geo.h"
#include <GL/glew.h>

// struct geo {
//     uint start;
//     uint end;
//     GLuint vboGeo; // ref
//     GLuint vao; // ref
//     vector<int> triIndex;
// };

class GeoManager {
    int highestVBO = 0;
    int highestVAO = 0;
    // need a structure to index by ID
public:
    vector<GLuint> vboGeos; // unused until i start doing batched geometry stuff
    vector<GLuint> VAOs; // unused until i start doing batched geometry stuff
    vector<geo> geometry;
    GeoManager();
    ~GeoManager();
    geo getGeo(vector <GLfloat>& verts, vector<int>& triIndex);
};

#endif