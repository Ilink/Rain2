#include "compositeRenderer.h"

CompositeRenderer::CompositeRenderer(vector<GLuint>& passes){
    vector<vertex> planeVerts;
    vector<GLuint> planeVertIndex;
    makePlane(2,2, planeVerts, planeVertIndex);

    glGenVertexArrays(1, &vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex)*planeVerts.size(), &planeVerts[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);  

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*planeVertIndex.size(), &planeVertIndex[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    this->passes = passes;

    texShader.load("shaders/texVs.glsl", "shaders/texFs.glsl");
}

void CompositeRenderer::setPasses(vector<GLuint>& passes){
    this->passes = passes;
}

CompositeRenderer::~CompositeRenderer(){
}

void CompositeRenderer::render(){
    glUseProgram(texShader.program);
    glBindVertexArray(vao);
    GLuint sampler = glGetUniformLocationARB(texShader.program, "sampler");

    for(int i = 0; i < passes.size(); i++){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        // error here
        glActiveTexture(GL_TEXTURE1); // might be 1?
        glBindTexture(GL_TEXTURE_2D, passes[i]);

        // pos
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(0));
        glEnableVertexAttribArray(0);

        // tex coordinate
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex),  BUFFER_OFFSET(sizeof(float)*6));
        glEnableVertexAttribArray(2);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    // cleanup
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(2);
}