/*
geometry data, i dont know what else it will have
*/

#ifndef GEO_COMPONENT_H
#define GEO_COMPONENT_H

#include <GL/glew.h>
// #include <Artemis-Cpp/Artemis.h>
#include "../include/Artemis-Cpp/Component.h"
#include <Artemis-Cpp/Component.h>
#include <vector>

using namespace std;

class GeoComponent : public artemis::Component{
public:
    GLuint vbo;
    GLuint ibo;
    GLuint vao;
    int start;
    int end;
    vector<GLfloat> verts; // storage for later modification

    // i could have the vbos and vaos as constructor parameters
    // that way the geometry manager would provide them
    GeoComponent(vector <GLfloat>& verts, int start, int end, GLuint vbo, GLuint ibo, GLuint vao){
        this->vbo = vbo;
        this->ibo = ibo;
        this->vao = vao;
        this->verts = verts;
        this->start = start;
        this->end = end;
    };
    ~GeoComponent(){

    };
};

#endif