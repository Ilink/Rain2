#ifndef DEFERRED_RENDERER_H
#define DEFERRED_RENDERER_H

/*
DeferredRenderer
This is basically a wrapper around LightSystem and GBufferSystem
Deferred rendering is a two step process. It's a tiny encapsulation to make sure they are 
coupled together like this.
*/

#include "../Artemis-Cpp/Artemis.h"
#include <GL/glew.h>
#include "../util.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../types.h"
#include "../settings.h"
#include "GBufferSystem.h"
#include "LightSystem.h"
#include "../camera.h"
#include "../texturePlane.h"

class DeferredRenderer {
private:
    GBufferSystem* gBufferSystem;
    LightSystem* lightSystem;
    artemis::SystemManager* sm;
    TexturePlane depthDebugPanel;
    TexturePlane colorDebugPanel;
    TexturePlane normalsDebugPanel;
public:
    DeferredRenderer(artemis::SystemManager* sm, Camera& camera);
    void process();
    void renderDepthPanel();
    void renderColorPanel();
    void renderNormalsPanel();
};

#endif