#ifndef TEXTUREPLANE_H
#define TEXTUREPLANE_H

#include <GL/glew.h>
#include "util.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "types.h"
#include <vector>
#include <string>
#include "shader.h"
#include "geoBuilder.h"
#include <SFML/Graphics/Image.hpp>

class TexturePlane
{
private:
    GLuint texture;
    Shader shader;
    GLuint vbo;
    GLuint vao;
    GLuint ibo;
    GLuint uSampler;
    GLuint uView;
    glm::mat4 view;
public:
    TexturePlane(GLuint& texture, double size, double x, double y);
    void render();
    ~TexturePlane();
};

#endif

