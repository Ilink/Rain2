#include <stdio.h>
#include <stdlib.h>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>  
#include <SFML/Window.hpp>
#include <tinyobj/tiny_obj_loader.h>
#include <GL/glew.h>
#include "shader.h"
#include "Artemis-Cpp/Artemis.h"
#include "systems/renderSystem.h"
#include "systems/shadowSystem.h"
#include "systems/depthSystem.h"
#include "systems/DeferredRenderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <fstream>
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
#include "objParser/objParser.h"
#include "camera.h"
#include "sceneLoader/sceneLoader.h"

using namespace std;

struct FileHeader {
    int numVerts;
    int numTriIndexes;
    int numQuadIndexes;
    int version;
};

struct FileData {
    vector<int> A;
    vector<double> B;
};

void threadFunc(){
    printf("running from other thread\n");
    boost::posix_time::seconds workTime(3);  
    boost::this_thread::sleep(workTime);
}

int main(int argc, char* argv[]) {

    boost::thread testThread(threadFunc);

    printf("waiting on thread\n");

    // testThread.join();

    aiScene scene;
    SceneLoader sceneLoader;
    Mesh tempMesh;
    bool loadSuccess;

    //////////////////////////////////////////////////////
    // These regenerate the *.cmesh files
    //////////////////////////////////////////////////////

    // loadSuccess = sceneLoader.objToCmesh("meshes/spider.obj", &scene, tempMesh);
    // loadSuccess = sceneLoader.objToCmesh("meshes/crytek-sponza/sponza.obj", &scene, tempMesh);
    // loadSuccess = sceneLoader.objToCmesh("meshes/crytek-sponza/sponza_all_tris.obj", &scene, tempMesh);
    loadSuccess = sceneLoader.objToCmesh("meshes/cone.obj", "meshes/cone.cmesh", &scene, tempMesh);
    loadSuccess = sceneLoader.objToCmesh("meshes/sphere.obj", "meshes/sphere.cmesh", &scene, tempMesh);
    // loadSuccess = sceneLoader.objToCmesh("meshes/demondogtris.obj", &scene, tempMesh);
    loadSuccess = sceneLoader.objToCmesh("meshes/teapot.obj", "meshes/teapot.cmesh", &scene, tempMesh);
    // loadSuccess = sceneLoader.objToCmesh("meshes/test.obj", &scene, tempMesh);
    // loadSuccess = sceneLoader.objToCmesh("meshes/cube.obj", &scene, tempMesh);
    // loadSuccess = sceneLoader.objToCmesh("meshes/Lighthouse.obj", &scene, tempMesh);
    // loadSuccess = sceneLoader.objToCmesh("meshes/sibenik.obj", &scene, tempMesh);

    // Mesh sceneMesh;
    Mesh coneMesh;
    Mesh sphereMesh;
    Mesh teapotMesh;
    // sceneLoader.readMesh("meshes/scene.cmesh", sceneMesh);
    sceneLoader.readMesh("meshes/sphere.cmesh", coneMesh);
    sceneLoader.readMesh("meshes/cone.cmesh", sphereMesh);
    sceneLoader.readMesh("meshes/teapot.cmesh", teapotMesh);



    Camera camera(glm::vec3(0.0f, 10.0f, -10.0f));

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
    window.setKeyRepeatEnabled(true);

    // note this must be called before any opengl operations
    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
        return 1;
    }

    shader.load("shaders/vs.glsl", "shaders/fs.glsl");
    Shader phongShader;
    phongShader.load("shaders/phongVs.glsl", "shaders/phongFs.glsl");

    glm::vec3 lightPos = glm::vec3(2.0f, 3.0f, -10.0f);
    glm::vec3 lightLookAtPoint = glm::vec3(0.0f, 0.0f, 0.0f);
    Spotlight light(1.0, &lightPos, &lightLookAtPoint);

    GeoManager geoManager;
    artemis::World world;
    artemis::EntityManager* em = world.getEntityManager();
    artemis::SystemManager* sm = world.getSystemManager();
    EntityFactory entityFactory(em, geoManager);
    // GeoFactory geoFactory;
    
    glm::vec3 lightPosition = glm::vec3(0.408248, -0.816497, 0.408248);

    RenderSystem* renderSystem = (RenderSystem*)sm->setSystem(new RenderSystem(&camera.viewMatrix, &lightPosition));
    DepthSystem* depthSystem = (DepthSystem*)sm->setSystem(new DepthSystem(light, &camera.viewMatrix));
    ShadowSystem* shadowSystem = (ShadowSystem*)sm->setSystem(new ShadowSystem(depthSystem->depthMap, light, &camera.viewMatrix));
    // MovementSystem* movementSystem = (MovementSystem*)sm->setSystem(new MovementSystem());
    DeferredRenderer deferredRenderer(sm, camera);
    
    vector<GLuint> passes;
    passes.push_back(depthSystem->depthMap);
    // passes.push_back(shadowSystem->shadowMap);
    CompositeRenderer compositeRenderer(passes);

    // TexturePlane depthDebugPanel(depthSystem->depthMap, 0.5, -0.7, 0.7);
    //TexturePlane depthDebugPanel(depthSystem->depthMap, 0.5, -0.7, 0.7);
    
    sm->initializeAll();

    glm::vec3 squarePos = glm::vec3(0.0f, 0.5f, 0.0f);
    glm::vec3 scenePos = glm::vec3(0.0f, 0.5f, 0.0f);
    float planeRot = 300.0f;
    float squareRot = 0.0f;
    glm::vec3 lightDir = glm::vec3(0.4,0.5, 0.5);

    double brightness = 0.0;
    double specularity = 0.0;

    TransformationComponent* trans = new TransformationComponent(
        &squarePos,
        &squareRot, &glm::vec3(0.0f, 1.0f, 0.0f)
    );

    artemis::Entity &box = em->create();
    box.addComponent(geoManager.create(boxVerts, boxVertIndex));
    box.addComponent(new PhongComponent(phongShader, brightness, specularity, lightDir));
    box.addComponent(trans);
    box.refresh();

    // glm::vec3 scale = glm::vec3(0.1f);
    glm::vec3 scale = glm::vec3(1.0f);
    // glm::vec3 scale = glm::vec3(6.0f);
    TransformationComponent *sceneTrans = new TransformationComponent(
        &scenePos,
        &scale,
        &squareRot,
        &glm::vec3(1.0f,0.5f, 0.5f)
    );

    TransformationComponent *planeTrans = new TransformationComponent(
        &scenePos,
        &glm::vec3(2.0f),
        new float (-90.0f),
        &glm::vec3(1.0f,0.0f, 0.0f)
    );

    TransformationComponent *lightTrans = new TransformationComponent(
        &lightPosition,
        &glm::vec3(0.5)
    );

    artemis::Entity &plane = entityFactory.makePlaneEntity();
    plane.addComponent(new PhongComponent(phongShader,brightness, specularity, lightDir));
    plane.addComponent(planeTrans);
    plane.refresh();

    artemis::Entity &lightModel = em->create();
    lightModel.addComponent(geoManager.create(boxVerts, boxVertIndex));
    lightModel.addComponent(new PhongComponent(phongShader, brightness, specularity, lightDir));
    lightModel.addComponent(lightTrans);
    lightModel.refresh();

    glm::vec3 scaleLight = glm::vec3(0.1f);
    TransformationComponent *mainLightTrans = new TransformationComponent(
        &scenePos,
        &scaleLight,
        &squareRot,
        &glm::vec3(1.0f,0.5f, 0.5f)
    );

    artemis::Entity &mainLight = em->create();
    mainLight.addComponent(geoManager.create(coneMesh.verts, coneMesh.triIndexes));
    mainLight.addComponent(mainLightTrans);
    mainLight.addComponent(new LightComponent(glm::vec3(0.0, 0.0, 0.0), 1.0f));
    mainLight.refresh();

    artemis::Entity &geo = em->create();
    // geo.addComponent(geoManager.create(meshes[0].verts, shapes[0].mesh.indices));
    geo.addComponent(geoManager.create(teapotMesh.verts, teapotMesh.triIndexes));
    // geo.addComponent(geoManager.create(meshes[0].verts, meshes[0].indexes));
    // geo.addComponent(geoManager.create(boxVerts, boxVertIndex));
    geo.addComponent(new PhongComponent(phongShader, brightness, specularity, lightDir));
    geo.addComponent(new DebugComponent(&glm::vec4(0.4, 0.3, 0.2, 1.0)));
    geo.addComponent(sceneTrans);
    geo.refresh();

    // artemis::Entity &geo = em->create();
    // // geo.addComponent(geoManager.create(meshes[0].verts, shapes[0].mesh.indices));
    // geo.addComponent(geoManager.create(sphereMesh.verts, sphereMesh.triIndexes));
    // // geo.addComponent(geoManager.create(meshes[0].verts, meshes[0].indexes));
    // // geo.addComponent(geoManager.create(boxVerts, boxVertIndex));
    // geo.addComponent(new PhongComponent(phongShader, brightness, specularity, lightDir));
    // geo.addComponent(new DebugComponent(&glm::vec4(0.4, 0.3, 0.2, 1.0)));
    // geo.addComponent(sceneTrans);
    // geo.refresh();

    // artemis::Entity &cone = em->create();
    // cone.addComponent(geoManager.create(coneMesh.verts, coneMesh.triIndexes));
    // cone.addComponent(new PhongComponent(phongShader, brightness, specularity, lightDir));
    // cone.addComponent(new DebugComponent(&glm::vec4(0.4, 0.3, 0.2, 1.0)));
    // cone.addComponent(sceneTrans);
    // cone.refresh();
    

    bool running = true;
    double angle = 0;
    double x = 0;
    sf::Vector2i posDelta(0,0);
    sf::Vector2i prevPos(0,0);
    bool mouseHeld = false;
    float initialCameraPos = 0.0f;
    float moveAmount = 1.0f;

    glClearColor(0.8, 1.0, 0.85, 1.0);

    camera.translate(initialCameraPos);

    while (running){
        // planeRot += 0.5;

        if(!isPaused){
            x+=0.06;
            // squarePos[1] = 2.0+1.5*sin(x);
            lightPosition[1] = 10.5*sin(x);
            lightPosition[2] = 10.5*cos(x);
            // squareRot += 1;
        }
        glEnable(GL_CULL_FACE);
        // glFrontFace(GL_CW);
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
            } else if (event.key.code == sf::Keyboard::E && event.type == sf::Event::KeyPressed){
                if(toggleCull) {
                    toggleCull = false;
                } else {
                    toggleCull = true;
                }
            } else if (event.key.code == sf::Keyboard::S && event.type == sf::Event::KeyPressed){
                camera.translate(-moveAmount);
            } else if (event.key.code == sf::Keyboard::W && event.type == sf::Event::KeyPressed){
                camera.translate(moveAmount);
            } else if (event.key.code == sf::Keyboard::A && event.type == sf::Event::KeyPressed){
                camera.strafe(-moveAmount);
            } else if (event.key.code == sf::Keyboard::D && event.type == sf::Event::KeyPressed){
                camera.strafe(moveAmount);
            } else if (event.key.code == sf::Keyboard::R && event.type == sf::Event::KeyPressed){
                if(toggleWireframe){
                    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
                    toggleWireframe = false;
                } else {
                    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
                    toggleWireframe = true;
                }
            } else if (event.key.code == sf::Keyboard::F && event.type == sf::Event::KeyPressed){
                // reset camera position
                camera.translate(initialCameraPos);
                camera.reset();
            } else if (event.key.code == sf::Keyboard::Q && event.type == sf::Event::KeyPressed){
                if(toggleCW){
                    glFrontFace(GL_CW);
                    // glDisable(GL_CULL_FACE);
                    toggleCW = false;
                } else {
                    glFrontFace(GL_CCW);
                    // glEnable(GL_CULL_FACE);
                    toggleCW = true;
                }
                
            }
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                sf::Vector2i position = sf::Mouse::getPosition(window);
                if(!mouseHeld){
                    prevPos.x = position.x;
                    prevPos.y = position.y;
                    posDelta.x = 0;
                    posDelta.y = 0;
                    mouseHeld = true;
                } else {
                    posDelta.x = prevPos.x - position.x;
                    posDelta.y = position.y -prevPos.y;
                    prevPos.x = position.x;
                    prevPos.y = position.y;
                }

                camera.pitch(((float) -posDelta.y) / 10.0);
                camera.yaw(((float) posDelta.x / 10.0));
                
                printf("%i, %i\n", posDelta.x, posDelta.y);
            } else {
                mouseHeld = false;
            }

            
        }

        world.loopStart();
        world.setDelta(0.0016f);
        // depthSystem->process();
        // shadowSystem->process();
        renderSystem->process();
        deferredRenderer.process();
        deferredRenderer.renderDepthPanel();
        deferredRenderer.renderColorPanel();
        deferredRenderer.renderNormalsPanel();

        // depthDebugPanel.render();

        window.display();
    }

    return 0;
}