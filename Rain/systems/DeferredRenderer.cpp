#include "DeferredRenderer.h"

DeferredRenderer::DeferredRenderer(artemis::SystemManager* sm, Camera& camera){
    this->sm = sm;
    gBufferSystem = (GBufferSystem*)sm->setSystem(new GBufferSystem(camera));
    lightSystem = (LightSystem*)sm->setSystem(new LightSystem(camera, gBufferSystem->gBuffer));

    depthDebugPanel = TexturePlane(gBufferSystem->gBuffer.depth, 0.5, -0.7, 0.7, 0);
    colorDebugPanel = TexturePlane(gBufferSystem->gBuffer.color, 0.5, -0.7, 0.0, 1);
    normalsDebugPanel = TexturePlane(gBufferSystem->gBuffer.normals, 0.5, -0.7, -0.5, 1);
}

void DeferredRenderer::process(){
    gBufferSystem->process();
    // lightSystem->process();
}

void DeferredRenderer::renderColorPanel(){
    colorDebugPanel.render();
}

void DeferredRenderer::renderDepthPanel(){
    depthDebugPanel.render();
}

void DeferredRenderer::renderNormalsPanel(){
    normalsDebugPanel.render();
}