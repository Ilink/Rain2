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

void writeMesh(Mesh mesh){
    vector<vertex> verts;
    vertex vert = {1.0f, 2.0f, 3.0f};
    verts.push_back(vert);
    vertex vert2 = {1.5f, 2.5f, 3.5f};
    verts.push_back(vert2);

    // Write
    FileData fileDataWrite;
    
    FileHeader fileHeaderWrite = {2,2,2,0};
    fstream fileOut("testFile.cmesh", ios::out | ios::binary);
    fileOut.write((const char*) &fileHeaderWrite, sizeof(FileHeader));

    for(int i=0; i < verts.size(); i++){
        fileOut.write((const char*) &verts[i], sizeof(vertex));
    }

    fileOut.close();
}

void readMesh(){
    // Read
    FileData fileDataRead;
    FileHeader fileHeaderRead;
    
    fstream fileIn("testFile.cmesh", ios::in | ios::binary);
    fileIn.read((char*) &fileHeaderRead, sizeof(FileHeader));
    printf("verts: %i num tri indexes: %i num quad indexes%i\n", fileHeaderRead.numVerts, fileHeaderRead.numTriIndexes, fileHeaderRead.numQuadIndexes);
    
    vertex vertBuffer;
    vector<vertex> vertsRead(fileHeaderRead.numVerts);
    for(int i = 0; i < fileHeaderRead.numVerts; i++){
        fileIn.read((char*) &vertBuffer, sizeof(vertex));
        // printf("vert from file: %f\n", vertBuffer.x);
        vertsRead[i] = vertBuffer;
    }

    GLuint buffer;
    vector<GLuint> triIndexRead(fileHeaderRead.numTriIndexes);
    for(int i = 0; i < triIndexRead.size(); i++){
        fileIn.read((char*) &buffer, sizeof(GLuint));
        triIndexRead[i] = buffer;
    }

    vector<GLuint> quadIndexRead(fileHeaderRead.numQuadIndexes);
    for(int i = 0; i < quadIndexRead.size(); i++){
        fileIn.read((char*) &buffer, sizeof(GLuint));
        quadIndexRead[i] = buffer;
    }

    for(int i = 0; i < vertsRead.size(); i++){
        printf("vert from file: %f\n", vertsRead[i].x);
    }

    fileIn.close();
}

void printParsedObj(vector<vertex>& verts, vector<GLuint>& indexes){    
    FILE *file = fopen ("log/obj.txt","w");
    
    fprintf(file, "num verts: %i\n", verts.size());
    for(int i = 0; i < verts.size(); i++){
        fprintf(file, "x: %f\ty: %f\tz: %f\n", verts[i].x, verts[i].y, verts[i].z);
        fprintf(file, "nx: %f\tny: %f\tnz: %f\n", verts[i].nx, verts[i].ny, verts[i].nz);
        fprintf(file, "u: %f\tu: %f\n\n", verts[i].u, verts[i].v);
    }

    fprintf(file, "\n\n\n");

    fprintf(file, "num faces: %i\n", indexes.size()/3);

    for(int i = 0; i < indexes.size(); i++){
        // fprintf(file, "%i %i %i\n", indexes[i], indexes[i+1], indexes[i+2]);
        if(i%3==0 && i > 0){
            fprintf(file, "\n");
        }
        fprintf(file, "%i", i);
        
    }

    fclose (file);
}

int main(int argc, char* argv[]) {

    aiScene scene;
    SceneLoader sceneLoader;
    Mesh _compactMesh;
    // bool loadSuccess = sceneLoader.objToCmesh("meshes/spider.obj", &scene, compactMesh);
    // bool loadSuccess = sceneLoader.objToCmesh("meshes/crytek-sponza/sponza.obj", &scene, _compactMesh);
    // bool loadSuccess = sceneLoader.objToCmesh("meshes/demondogtris.obj", &scene, compactMesh);
    //bool loadSuccess = sceneLoader.objToCmesh("meshes/teapot.obj", &scene, _compactMesh);
    // bool loadSuccess = sceneLoader.objToCmesh("meshes/test.obj", &scene, compactMesh);
    // bool loadSuccess = sceneLoader.objToCmesh("meshes/cube.obj", &scene, compactMesh);
    // bool loadSuccess = sceneLoader.objToCmesh("meshes/Lighthouse.obj", &scene, compactMesh);
    // bool loadSuccess = sceneLoader.objToCmesh("meshes/sibenik.obj", &scene, compactMesh);

    Mesh compactMesh;
    sceneLoader.readMesh(compactMesh);

    //printf("scene loaded: %i\n", loadSuccess);

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

    // const sf::Vector2i windowCenter( 400, 300 );
    // sf::Mouse::setPosition( windowCenter, window );

    // note this must be called before any opengl operations
    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
        return 1;
    }

    shader.load("shaders/vs.glsl", "shaders/fs.glsl");
    Shader phongShader;
    phongShader.load("shaders/phongVs.glsl", "shaders/phongFs.glsl");

//    glm::vec3 lightPos = glm::vec3(0.0f, 10.0f, 0.0f);
    glm::vec3 lightPos = glm::vec3(2.0f, 3.0f, -10.0f);
    glm::vec3 lightLookAtPoint = glm::vec3(0.0f, 0.0f, 0.0f);
    Spotlight light(1.0, &lightPos, &lightLookAtPoint);

    // lookAtPoint = glm::vec3(0.0f, 0.0f, 0.0f);
    // eye = glm::vec3(0.0f, 0.0f, -10.0f);
    // upVector = glm::vec3(0.0f, 1.0f, 0.0f);

    // Spotlight light(1.0, glm::vec3(10.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    // light.rotate(90.0, glm::vec3(1.0, ))

    GeoManager geoManager;
    artemis::World world;
    artemis::EntityManager* em = world.getEntityManager();
    artemis::SystemManager* sm = world.getSystemManager();
    EntityFactory entityFactory(em, geoManager);
    // GeoFactory geoFactory;
    
    RenderSystem* renderSystem = (RenderSystem*)sm->setSystem(new RenderSystem(&camera.viewMatrix));
    DepthSystem* depthSystem = (DepthSystem*)sm->setSystem(new DepthSystem(light, &camera.viewMatrix));
    ShadowSystem* shadowSystem = (ShadowSystem*)sm->setSystem(new ShadowSystem(depthSystem->depthMap, light, &camera.viewMatrix));
    
    vector<GLuint> passes;
    passes.push_back(depthSystem->depthMap);
    // passes.push_back(shadowSystem->shadowMap);
    CompositeRenderer compositeRenderer(passes);

    TexturePlane depthDebugPanel(depthSystem->depthMap, 0.5, -0.7, 0.7);
    
    sm->initializeAll();

    glm::vec3 squarePos = glm::vec3(0.0f, 0.5f, 0.0f);
    glm::vec3 scenePos = glm::vec3(0.0f, 0.5f, 0.0f);
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

    // glm::vec3 scale = glm::vec3(0.01f);
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

    artemis::Entity &plane = entityFactory.makePlaneEntity();
    plane.addComponent(new PhongComponent(&phongShader, &brightness, &specularity, &lightDir));
    plane.addComponent(planeTrans);
    plane.refresh();

    artemis::Entity &geo = em->create();
    // geo.addComponent(geoManager.create(meshes[0].verts, shapes[0].mesh.indices));
    geo.addComponent(geoManager.create(compactMesh.verts, compactMesh.triIndexes));
    //geo.addComponent(geoManager.create(meshes[0].verts, meshes[0].indexes));
    // geo.addComponent(geoManager.create(boxVerts, boxVertIndex));
    geo.addComponent(new PhongComponent(&phongShader, &brightness, &specularity, &lightDir));
    geo.addComponent(new DebugComponent(&glm::vec4(0.4, 0.3, 0.2, 1.0)));
    geo.addComponent(sceneTrans);
    geo.refresh();
    

    bool running = true;
    double angle = 0;
    double x = 0;
    sf::Vector2i posDelta(0,0);
    sf::Vector2i prevPos(0,0);
    bool mouseHeld = false;
    float initialCameraPos = 0.0f;
    float moveAmount = 1.0f;

    camera.translate(initialCameraPos);

    while (running){
        // planeRot += 0.5;

        if(!isPaused){
            x+=0.1;
            squarePos[1] = 2.0+1.5*sin(x);
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

        depthDebugPanel.render();

        window.display();
    }

    return 0;
}