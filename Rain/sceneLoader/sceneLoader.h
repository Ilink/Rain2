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

class SceneLoader
{
private:
    void compact(const aiScene* scene, Mesh& compactMesh);
public:
    SceneLoader();
    bool load(const char* fileName, const aiScene *scene, Mesh& compactMesh);
    ~SceneLoader();

    /* data */
};

#endif