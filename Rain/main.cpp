#include <stdio.h>
#include <stdlib.h>
// #include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <tinyobj/tiny_obj_loader.h>
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
#include "objParser/objParser.h"

using namespace std;

void printParsedObj(vector<vertex>& verts, vector<GLuint>& indexes){    
    FILE *file = fopen ("log/obj.txt","w");
    
    fprintf(file, "num verts: %i\n", verts.size());
    for(int i = 0; i < verts.size(); i++){
        fprintf(file, "x: %f\ty: %f\tz: %f\n", verts[i].x, verts[i].y, verts[i].z);
        fprintf(file, "nx: %f\tny: %f\tnz: %f\n", verts[i].nx, verts[i].ny, verts[i].nz);
        fprintf(file, "u: %f\tu: %f\n\n", verts[i].u, verts[i].v);
    }

    fprintf(file, "\n\n\n");

    for(int i = 0; i < indexes.size()-3; i+=3){
        fprintf(file, "%i %i %i\n", indexes[i], indexes[i+1], indexes[i+2]);
    }

    fclose (file);
}

int main(int argc, char* argv[]) {

    string str = "1111/789/125433 2222/789/123345 3333/789/123456";

    int num;
    string curNum;
    int start = 0;
    int end = 0;
    int length = str.length();
    int numTokens = 0;
    for(int i=0; i < length; i++){
        if(str[i] == '/' || str[i] == ' '){
            end = i;
            curNum = str.substr(start, end-start);
            num = strtol(curNum.c_str(), NULL, 10);
            start = i+1;
            if(numTokens%3 == 0){
                printf("num: %i\n", num);
            }
            numTokens++;
        }
    };

    //char * pch;
    //char * inner;
    //int a;
    //pch = strtok ((char *) str.c_str()," ");
    //while (pch != NULL){
    //    // a = strtol(pch, NULL, 10);
    //    //inner = strtok(pch, "/");
    //    printf ("outer %s\n",pch);
    //    /*while (inner != NULL){
    //        printf("inner: %s\n", inner);
    //        inner = strtok(NULL, "/");
    //    }*/
    //    // printf ("%i\n",a);
    //    
    //    pch = strtok (NULL, " ");
    //}



    vector<mesh> meshes;
    // parseObj("meshes/cornellBox/cornell_box.obj", meshes);
    // parseObj("meshes/teapot.obj", meshes);
    parseObj("meshes/crytek-sponza/sponza.obj", meshes);
    if(meshes.size()){
        printParsedObj(meshes[0].verts, meshes[0].indexes);
    }

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

    TexturePlane depthDebugPanel(depthSystem->depthMap, 0.5, -0.7, 0.7);
    
    sm->initializeAll();

    glm::vec3 squarePos = glm::vec3(0.0f, 0.5f, 0.0f);
    glm::vec3 scenePos = glm::vec3(0.0f, 0.0f, 0.0f);
    float planeRot = 300.0f;
    float squareRot = 0.0f;
    glm::vec3 lightDir = glm::vec3(0.4,0.5, 0.5);

    double brightness = 0.0;
    double specularity = 0.0;

    // TransformationComponent *trans1 = new TransformationComponent(
    //     &glm::vec3(0.0f, 0.0f, 0.0f),
    //     &planeRot, &glm::vec3(1.0f, 0.0f, 0.0f)
    // );

    // artemis::Entity &plane = entityFactory.makePlaneEntity();
    // plane.addComponent(new PhongComponent(&phongShader, &brightness, &specularity, &lightDir));
    // plane.addComponent(trans1);
    // plane.refresh();

    // TransformationComponent* trans = new TransformationComponent(
    //     &squarePos,
    //     &squareRot, &glm::vec3(0.0f, 1.0f, 0.0f)
    // );

    // artemis::Entity &square = em->create();
    // square.addComponent(geoManager.create(boxVerts, boxVertIndex));
    // square.addComponent(new PhongComponent(&phongShader, &brightness, &specularity, &lightDir));
    // square.addComponent(trans);
    // square.refresh();

    double __angle = 0.0;
    double *_angle = &__angle;
    glm::vec3 scale = glm::vec3(0.001f);
    TransformationComponent *sceneTrans = new TransformationComponent(
        &scenePos,
        &scale,
        &squareRot,
        &glm::vec3(1.0f,0.5f, 0.5f)
    );
    artemis::Entity &scene = em->create();
    scene.addComponent(geoManager.create(meshes[0].verts, meshes[0].indexes));
    // scene.addComponent(geoManager.create(boxVerts, boxVertIndex));
    scene.addComponent(new PhongComponent(&phongShader, &brightness, &specularity, &lightDir));
    scene.addComponent(new DebugComponent(&glm::vec4(0.4, 0.3, 0.2, 1.0)));
    scene.addComponent(sceneTrans);
    scene.refresh();
    

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
            } else if (event.key.code == sf::Keyboard::E && event.type == sf::Event::KeyPressed){
                if(toggleCull) {
                    toggleCull = false;
                } else {
                    toggleCull = true;
                }
            } else if (event.key.code == sf::Keyboard::S && event.type == sf::Event::KeyPressed){
                scale[0] -= 0.05;
                scale[1] -= 0.05;
                scale[2] -= 0.05;
            }
        }

        world.loopStart();
        world.setDelta(0.0016f);
        // depthSystem->process();
        // shadowSystem->process();
        renderSystem->process();

        depthDebugPanel.render();

        window.display();
    }

    return 0;
}