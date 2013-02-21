#include <stdio.h>
#include <stdlib.h>
// #include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <GL/glew.h>
#include "shader.h"
#include "Artemis-Cpp/Artemis.h"
#include "systems/renderSystem.h"
#include "systems/shadowSystem.h"
#include "systems/depthSystem.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "main.h"
#include "geoManager.h"
#include <string>
#include "types.h"
#include <vector>
#include "normals.h"
#include "geoBuilder.h"
#include "entityFactory.h"
#include "compositeRenderer.h"
#include "texturePlane.h"
#include "components/spotLightComponent.h"
#include "components/idComponent.h"
#include "components/transformationComponent.h"
#include "components/debugComponent.h"
#include "spotlight.h"
#include "settings.h"

using namespace std;

int main(int argc, char* argv[]) {

    Shader shader;
    vector<vertex> boxVerts;
    vector<GLuint> boxVertIndex;
    makeBox(1,1,-1, boxVerts, boxVertIndex);
    calcFaceNormals(boxVerts, boxVertIndex);

    vector<vertex> planeVerts;
    vector<GLuint> planeVertIndex;
    makeBox(1,1,-1, planeVerts, planeVertIndex);
    calcFaceNormals(planeVerts, planeVertIndex);

    sf::Window window(sf::VideoMode(800, 600), "OpenGL");
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    // note this must be called before any opengl operations
    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
        return 1;
    }

    shader.load("shaders/vs.glsl", "shaders/fs.glsl");
    Shader phongShader;
    phongShader.load("shaders/phongVs.glsl", "shaders/phongFs.glsl");

    // glm::vec3 lightPos = glm::vec3(-7.0f, 6.0f, 0.0f);
    glm::vec3 lightPos = glm::vec3(0.0f, 10.0f, 0.0f);
    glm::vec3 lightLookAtPoint = glm::vec3(0.0f, 0.5f, 0.0f);
    Spotlight light(1.0, &lightPos, &lightLookAtPoint);
    // Spotlight light(1.0, glm::vec3(10.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    // light.rotate(90.0, glm::vec3(1.0, ))

    GeoManager geoManager;
    artemis::World world;
    artemis::EntityManager* em = world.getEntityManager();
    artemis::SystemManager* sm = world.getSystemManager();
    EntityFactory entityFactory(em, geoManager);
    // GeoFactory geoFactory;
    
    RenderSystem* renderSystem = (RenderSystem*)sm->setSystem(new RenderSystem());
    DepthSystem* depthSystem = (DepthSystem*)sm->setSystem(new DepthSystem(light));
    ShadowSystem* shadowSystem = (ShadowSystem*)sm->setSystem(new ShadowSystem(depthSystem->depthMap, light));
    
    vector<GLuint> passes;
    passes.push_back(depthSystem->depthMap);
    // passes.push_back(shadowSystem->shadowMap);
    CompositeRenderer compositeRenderer(passes);

    TexturePlane texturePlane(depthSystem->depthMap, 0.5, -0.7, 0.7);
    
    sm->initializeAll();

    glm::vec3 squarePos(0.0f, 0.5f, 0.0f);
    float planeRot = 300.0f;
    float squareRot = 0.0f;

    artemis::Entity &plane = entityFactory.makePlaneEntity();
    plane.addComponent(new PhongComponent(phongShader, 0, 0, glm::vec3(0.1, 0.2, 0.3)));
    plane.addComponent(new IDComponent(0));
    plane.addComponent(new DebugComponent(&glm::vec4(0.0, 0.3, 0.2, 1.0)));
    plane.addComponent(new TransformationComponent(
        &glm::vec3(0.0f, 0.0f, 0.0f),
        &planeRot, &glm::vec3(1.0f, 0.0f, 0.0f)
    ));

    artemis::Entity &square = em->create();
    square.addComponent(geoManager.create(boxVerts, boxVertIndex));
    square.addComponent(new PhongComponent(phongShader, 0, 0, glm::vec3(0.4,0.5, 0.5)));
    square.addComponent(new DebugComponent(&glm::vec4(0.4, 0.3, 0.2, 1.0)));
    square.addComponent(new IDComponent(1));
    square.addComponent(new TransformationComponent(
        &squarePos,
        &squareRot, &glm::vec3(0.0f, 1.0f, 0.0f)
    ));

    plane.refresh();
    square.refresh();

    bool running = true;
    double angle = 0;
    double x = 0;

    while (running){
        // planeRot += 0.5;

        if(!isPaused){
            x+=0.1;
            squarePos[1] = 2.0+1.5*sin(x);
            squareRot += 1;
        } 

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                running = false;
            } else if (event.type == sf::Event::Resized){
                glViewport(0, 0, event.size.width, event.size.height);
            } else if (event.key.code == sf::Keyboard::Space && event.type == sf::Event::KeyPressed){
                if(isPaused) isPaused = false;
                else isPaused = true;
            } else if (event.key.code == sf::Keyboard::S && event.type == sf::Event::KeyPressed){
                if(toggleCull) {
                    toggleCull = false;
                } else {
                    toggleCull = true;
                }
            }
        }

        world.loopStart();
        world.setDelta(0.0016f);
        depthSystem->process();
        shadowSystem->process();
        // renderSystem->process();

        texturePlane.render();

        window.display();
    }

    return 0;
}