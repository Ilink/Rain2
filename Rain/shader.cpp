#include "shader.h"

using namespace std;
using namespace util;

Shader::Shader(const char* vsFilename, const char* fsFilename){
    ensureGlewInit();
    string vs = getFileContents(vsFilename);
    string fs = getFileContents(fsFilename);
    program = glCreateProgram();
    compile(vs, fs);
}

Shader::Shader(){}

bool Shader::load(const char* vsFilename, const char* fsFilename){
    ensureGlewInit();
    string vs = getFileContents(vsFilename);
    string fs = getFileContents(fsFilename);
    program = glCreateProgram();
    return compile(vs, fs);
}

Shader::~Shader(){
}

bool Shader::compile(string& _vs, string& _fs){
	GLchar const *vs = _vs.c_str();
	GLchar const *fs = _fs.c_str();
    GLint success;

    // Create and compile the shader
    GLhandleARB vertexShader = glCreateShader(GL_VERTEX_SHADER_ARB);
    glCheck(glShaderSource(vertexShader, 1, &vs, NULL));
    glCheck(glCompileShader(vertexShader));

    // Check the compile log
    glCheck(glGetProgramiv(vertexShader, GL_OBJECT_COMPILE_STATUS_ARB, &success));
    if (success == GL_FALSE){
        char log[1024];
        glCheck(glGetShaderInfoLog(vertexShader, sizeof(log), 0, log));
        cout << "Failed to compile vertex shader:" << std::endl
                << log << std::endl;
        glCheck(glDeleteShader(vertexShader));
        glCheck(glDeleteProgram(program));
        program = 0;
        return false;
    } else {
        cout << "compiled vert shader?" << endl;
    }

    // Attach the shader to the program, and delete it (not needed anymore)
    glCheck(glAttachShader(program, vertexShader));
    glCheck(glDeleteShader(vertexShader));
    

    // Create and compile the shader
    GLhandleARB fragmentShader = glCreateShader(GL_FRAGMENT_SHADER_ARB);
    glCheck(glShaderSource(fragmentShader, 1, &fs, NULL));
    glCheck(glCompileShader(fragmentShader));

    // Check the compile log
    glCheck(glGetProgramiv(fragmentShader, GL_OBJECT_COMPILE_STATUS_ARB, &success));
    if (success == GL_FALSE){
        char log[1024];
        glCheck(glGetShaderInfoLog(fragmentShader, sizeof(log), 0, log));
        cout << "Failed to compile fragment shader:" << std::endl
                << log << std::endl;
        glCheck(glDeleteShader(fragmentShader));
        glCheck(glDeleteProgram(program));
        program = 0;
        return false;
    } else {
        cout << "compiled frag shader?" << endl;
    }

    // Attach the shader to the program, and delete it (not needed anymore)
    glCheck(glAttachShader(program, fragmentShader));
    glCheck(glDeleteShader(fragmentShader));
    

    // Link the program
    glCheck(glLinkProgram(program));

    // Check the link log
    glCheck(glGetProgramiv(program, GL_OBJECT_LINK_STATUS_ARB, &success));
    if (success == GL_FALSE){
        char log[1024];
        glCheck(glGetShaderInfoLog(program, sizeof(log), 0, log));
        cout << "Failed to link shader:" << std::endl
              << log << std::endl;
        glCheck(glDeleteProgram(program));
        program = 0;
        return false;
    } else {
        cout << "linked shaders" << endl;
    }

    return true;
}
