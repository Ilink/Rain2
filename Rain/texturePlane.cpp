#include "texturePlane.h"

TexturePlane::TexturePlane(GLuint& texture, double size, double x, double y){
    shader.load("shaders/texVs.glsl", "shaders/texFs.glsl");

    this->texture = texture;

    vector<vertex> planeVerts;
    vector<GLuint> planeVertIndex;
    makePlane(size,size, planeVerts, planeVertIndex);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex)*planeVerts.size(), &planeVerts[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*planeVertIndex.size(), &planeVertIndex[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glUseProgram(shader.program);
    uSampler = glGetUniformLocation(shader.program, "sampler");
    uView = glGetUniformLocation(shader.program, "uView");
    glUseProgram(0);

    view = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
}

void TexturePlane::render(){
    glUseProgram(shader.program);
    glBindVertexArray(vao);
    uSampler = glGetUniformLocation(shader.program, "sampler");
    uView = glGetUniformLocation(shader.program, "uView");

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //glActiveTexture(GL_TEXTURE0); // might be 1?
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(uSampler, 0);

    glUniformMatrix4fv(uView, 1, FALSE, (const GLfloat*) glm::value_ptr(view));

    // pos
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(0));

    // tex coordinate
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(24));
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex),  ((GLubyte *)NULL + (24)));
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    // cleanup
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(2);
}


TexturePlane::~TexturePlane(){
    
}