#ifndef SCENE_LOADER_H
#define SCENE_LOADER_H

#include <fstream>
#include <string>
#include <vector>
#include "assimp/Importer.hpp"  //OO version Header!
#include "assimp/PostProcess.h"
#include "assimp/Scene.h"
#include "assimp/DefaultLogger.hpp"
#include "assimp/LogStream.hpp"
#include "../types.h"
#include "mesh.h"

struct MeshFileHeader {
    int numVerts;
    int numTriIndexes;
    int numQuadIndexes;
    int version;
};

class SceneLoader
{
private:
    void compact(const aiScene* scene, Mesh& compactMesh);
public:
    SceneLoader();
    ~SceneLoader();
    bool SceneLoader::writeMesh(const char* filename, Mesh& mesh);
    bool SceneLoader::objToCmesh(const char* filename, const char* filenameOut);
    void SceneLoader::readMesh(const char* filename, Mesh& mesh);

    /* data */
};

#endif