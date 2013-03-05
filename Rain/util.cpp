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

