#ifndef COMPOSITE_RENDERER_H
#define COMPOSITE_RENDERER_H

#include "Artemis-Cpp/Artemis.h"
#include "components/geoComponent.h"
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

class CompositeRenderer
{
private:
    GLuint vbo;
    GLuint ibo;
    GLuint vao;
    GLuint texCoords;
    vector<GLuint> passes; // each pass is a texture
    Shader texShader;
public:
    CompositeRenderer(vector<GLuint>& passes);
    ~CompositeRenderer();
    void CompositeRenderer::setPasses(vector<GLuint>& passes);
    void CompositeRenderer::render();
};

#endif