#include "util.h"

std::string getFileContents(const char *filename){
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (in){
        return(std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>()).c_str());
    }
    throw(errno);
}

void printGlError(){
    GLenum error = glGetError();
    if(error)
        fprintf(stderr, "GL Error: %s\n", glewGetErrorString(error));
}

void vaoSetup(GLuint& vao, GLuint& vbo, GLuint& ibo){
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);

    // Normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex),  BUFFER_OFFSET(sizeof(float)*3));
    glEnableVertexAttribArray(1);

    // // Textures
    // glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex),  BUFFER_OFFSET(sizeof(float)*2));
    // glEnableVertexAttribArray(2);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void printFboErrors(char* name){
    GLenum FBOstatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    switch(FBOstatus){
        case GL_FRAMEBUFFER_UNDEFINED: 
            printf("%s GL_FRAMEBUFFER_UNDEFINED\n", name);
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: 
            printf("%s GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT\n", name);
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: 
            printf("%s GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT\n", name);
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
            printf("%s GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER\n", name);
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            printf("%s GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER\n", name);
            break;
        default:
            printf("%s fbo OK\n", name);
    }
}