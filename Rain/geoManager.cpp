#include "geoManager.h"

using namespace std;

GeoManager::GeoManager(){

}

GeoManager::~GeoManager(){

}

/*
Note that the VAO is only partially set up here. It needs to be initialized with more shader-specific stuff later.
*/
GeoComponent* GeoManager::create(vector <vertex>& verts, vector<GLuint>& triIndex){
    this->VBOs.push_back((GLuint) this->VBOs.size()+1);
    this->IBOs.push_back((GLuint) this->IBOs.size()+1);
    this->VAOs.push_back((GLuint) this->VAOs.size()+1);

    glGenBuffers(1, &this->VBOs.back());
    glBindBuffer(GL_ARRAY_BUFFER, this->VBOs.back());
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex)*verts.size(), &verts[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &this->IBOs.back());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBOs.back());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*triIndex.size(), &triIndex[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &this->VAOs.back());

    printGlError();

    /*
    something would have to store and chunk up the geometry into various VBOs. I dont know a good way of doing that.
    group by:
        => shader
        => transformation matrix

    you can still change uniforms/attributes, it just means drawing parts of the VBO at a time.
    So it probably makes sense to group things that are similar, based upon both of those criteria.
    For instance, a set of boxes could tkae the same shader. 

    Another consideration is multiple shaders per mesh. I dont have a good way of dealing with that.
    Right now, a single entity has a shader component and a mesh component. Can I have a list of mesh and shader components?
    */

    return new GeoComponent(verts, triIndex, -1, -1, this->VBOs.back(), this->IBOs.back(), this->VAOs.back());
}

void GeoManager::freeAll(){
    vector<GLuint>::iterator iter;
}