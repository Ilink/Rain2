/*
geometry data, i dont know what else it will have
*/

#ifndef GEO_COMPONENT_H
#define GEO_COMPONENT_H

#include <GL/glew.h>
#include <Artemis-Cpp/Artemis.h>
#include <vector>

using namespace std;

class GeoComponent : public artemis::Component{
public:
    GLuint vao;
    GLuint vboGeo;
    int start;
    int end;

    // i could have the vbos and vaos as constructor parameters
    // that way the geometry manager would provide them
    GeoComponent(int& verts, vector<GLuint>& triIndex, int& start, int& end, GLuint& vbo, GLuint& vao){
        
    };
    ~GeoComponent(){};
};

#endif