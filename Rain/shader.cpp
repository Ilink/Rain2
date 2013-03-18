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

// from http://content.gpwiki.org/index.php/OpenGL:Codes:Simple_GLSL_example
void printShaderInfoLog(GLuint shader){
    int infologLength = 0;
    char infoLog[1024];
 
	if (glIsShader(shader))
		glGetShaderInfoLog(shader, 1024, &infologLength, infoLog);
	else
		glGetProgramInfoLog(shader, 1024, &infologLength, infoLog);
 
    if (infologLength > 0)
		printf("%s\n", infoLog);
}

bool Shader::compile(string& _vs, string& _fs){
	GLchar const *vs = _vs.c_str();
	GLchar const *fs = _fs.c_str();
    GLint success;

    // Create and compile the shader
    GLhandleARB vertexShader = glCreateShader(GL_VERTEX_SHADER_ARB);
    glCheck(glShaderSource(vertexShader, 1, &vs, NULL));
    glCheck(glCompileShader(vertexShader));

    // Attach the shader to the program, and delete it (not needed anymore)
    glCheck(glAttachShader(program, vertexShader));
    glCheck(glDeleteShader(vertexShader));    

    // Create and compile the shader
    GLhandleARB fragmentShader = glCreateShader(GL_FRAGMENT_SHADER_ARB);
    glCheck(glShaderSource(fragmentShader, 1, &fs, NULL));
    glCheck(glCompileShader(fragmentShader));

    // Attach the shader to the program, and delete it (not needed anymore)
    glCheck(glAttachShader(program, fragmentShader));
    glCheck(glDeleteShader(fragmentShader));
    
    glBindAttribLocation(program, 0, "pos");
    glBindAttribLocation(program, 1, "normal");
    glBindAttribLocation(program, 2, "texCoord");
    
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

    cout << "handling binding: ";
    printGlError();
    printShaderInfoLog(program);

    return true;
}
