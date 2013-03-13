/*
geometry data, i dont know what else it will have
*/

#ifndef GEO_COMPONENT_H
#define GEO_COMPONENT_H

#include <GL/glew.h>
#include "Artemis.h"
#include <vector>
#include "../types.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <tinyobj/tiny_obj_loader.h>

using namespace std;
using namespace glm;

class GeoComponent : public artemis::Component{
public:
    GLuint vbo;
    GLuint ibo;
    GLuint vao;
    int start;
    int end;
    bool isVaoReady;
    // it doesn't really make sense to store this here, given that it isn't used and modification should happen at the level above...so it can regen VBOs etc
    vector<vertex> verts; // storage for later modification
    vector<GLuint> triIndex;

    // i could have the vbos and vaos as constructor parameters
    // that way the geometry manager would provide them
    GeoComponent(vector <vertex>& verts, vector<GLuint>& triIndex, int& start, int& end, GLuint& vbo, GLuint& ibo, GLuint& vao)
    :verts(verts),
    triIndex(triIndex),
    start(start),
    end(end),
    vbo(vbo),
    vao(vao),
    ibo(ibo)
    {
        this->isVaoReady = false;
    };

    ~GeoComponent(){

    };
};

#endif