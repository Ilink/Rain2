#include "sceneLoader.h"

SceneLoader::SceneLoader(){
}

SceneLoader::~SceneLoader(){}

bool SceneLoader::writeMesh(Mesh& mesh){
    MeshFileHeader header;
    header.numQuadIndexes = mesh.quadIndexes.size();
    header.numTriIndexes = mesh.triIndexes.size();
    header.numVerts = mesh.verts.size();
    header.version = 0;

    fstream fileOut("testFile.cmesh", ios::out | ios::binary);
    fileOut.write((const char*) &header, sizeof(MeshFileHeader));

    for(int i=0; i < mesh.verts.size(); i++){
        fileOut.write((const char*) &mesh.verts[i], sizeof(vertex));
    }

    for(int i = 0; i < mesh.triIndexes.size(); i++){
        fileOut.write((const char*) &mesh.triIndexes[i], sizeof(GLuint));
    }

    for(int i = 0; i < mesh.quadIndexes.size(); i++){
        fileOut.write((const char*) &mesh.quadIndexes[i], sizeof(GLuint));
    }

    fileOut.close();
    return true;
}

void SceneLoader::readMesh(Mesh& mesh){
    MeshFileHeader header;
    
    fstream fileIn("testFile.cmesh", ios::in | ios::binary);
    fileIn.read((char*) &header, sizeof(MeshFileHeader));
    
    vertex vertBuffer;
    mesh.verts.resize(header.numVerts);
    for(int i = 0; i < header.numVerts; i++){
        fileIn.read((char*) &vertBuffer, sizeof(vertex));
        // printf("vert from file: %f\n", vertBuffer.x);
        mesh.verts[i] = vertBuffer;
    }

    // This isnt working
    GLuint buffer;
    mesh.triIndexes.resize(header.numTriIndexes);
    for(int i = 0; i < mesh.triIndexes.size(); i++){
        fileIn.read((char*) &buffer, sizeof(GLuint));
        mesh.triIndexes[i] = buffer;
    }

    mesh.quadIndexes.resize(header.numQuadIndexes);
    for(int i = 0; i < mesh.quadIndexes.size(); i++){
        fileIn.read((char*) &buffer, sizeof(GLuint));
        mesh.quadIndexes[i] = buffer;
    }

    fileIn.close();
}

bool SceneLoader::objToCmesh(const char* fileName, const aiScene *scene, Mesh& compactMesh){
    Assimp::Importer importer;
    //check if file exists
    std::ifstream fin(fileName);
    if(!fin.fail()){
        fin.close();
    } else {
        // MessageBox(NULL, ("Couldn't open file: " + pFile).c_str() , "ERROR", MB_OK | MB_ICONEXCLAMATION);
        // printf("%s\n",importer.GetErrorString());
        return false;
    }

    //scene = importer.ReadFile( fileName, aiProcess_GenUVCoords | aiProcess_GenSmoothNormals);
    scene = importer.ReadFile( fileName, aiProcess_GenUVCoords | aiProcess_GenSmoothNormals);
    
    //scene = importer.ReadFile( fileName, aiProcess_GenUVCoords | aiProcess_GenSmoothNormals | aiProcess_Triangulate);

    // If the import failed, report it
    if( !scene){
        printf("%s\n",importer.GetErrorString());
        return false;
    }

    printf("scene loaded\n");

    // Now we can access the file's contents.
    //logInfo("Import of scene " + pFile + " succeeded.");

    compact(scene, compactMesh);
    writeMesh(compactMesh);

    // We're done. Everything will be cleaned up by the importer destructor
    return true;
}

void fillVert(vertex& vert){
    vert.x = 0.0;
    vert.y = 0.0;
    vert.z = 0.0;
    vert.nx = 0.0;
    vert.ny = 0.0;
    vert.nz = 0.0;
    vert.u = 0.0;
    vert.v = 0.0;
}

void printer(Mesh& mesh){    
    FILE *file = fopen ("log/obj.txt","w");
    
    fprintf(file, "num verts: %i\n", mesh.verts.size());
    for(int i = 0; i < mesh.verts.size(); i++){
        fprintf(file, "x: %f\ty: %f\tz: %f\n", mesh.verts[i].x, mesh.verts[i].y, mesh.verts[i].z);
        fprintf(file, "nx: %f\tny: %f\tnz: %f\n", mesh.verts[i].nx, mesh.verts[i].ny, mesh.verts[i].nz);
        fprintf(file, "u: %f\tu: %f\n\n", mesh.verts[i].u, mesh.verts[i].v);
    }

    fprintf(file, "\n\n\n");

    // fprintf(file, "num faces: %i\n", indexes.size()/3);

    for(int i = 0; i < mesh.triIndexes.size(); i++){
        // fprintf(file, "%i %i %i\n", indexes[i], indexes[i+1], indexes[i+2]);
        if(i%3==0 && i > 0){
            fprintf(file, "\n");
        }
        fprintf(file, "%i", i);
        
    }

    fclose (file);
}

void SceneLoader::compact(const aiScene* scene, Mesh& compactMesh){
    // Mesh compactMesh;
    std::vector<GLuint>* indexes = NULL;

    const struct aiNode* currentNode = scene->mRootNode;
    const struct aiMesh* mesh = scene->mMeshes[0];

    for (int t = 0; t < mesh->mNumFaces; ++t) {
        const struct aiFace* face = &mesh->mFaces[t];
        vertex vert;
        fillVert(vert);
        if(face->mNumIndices == 3){
            indexes = &compactMesh.triIndexes;
        } else if (face->mNumIndices >= 4){
            indexes = &compactMesh.quadIndexes;
        }

        for(int i = 0; i < face->mNumIndices; i++){     // go through all vertices in face
            int vertexIndex = face->mIndices[i];    // get group index for current index
            indexes->push_back(vertexIndex);

            vert.x = mesh->mVertices[vertexIndex].x;
            vert.y = mesh->mVertices[vertexIndex].y;
            vert.z = mesh->mVertices[vertexIndex].z;

            vert.nx = mesh->mNormals[vertexIndex].x;
            vert.ny = mesh->mNormals[vertexIndex].x;
            vert.nz = mesh->mNormals[vertexIndex].x;

            if(mesh->HasTextureCoords(0)){
                vert.u = mesh->mTextureCoords[0][vertexIndex].x;
                vert.v = mesh->mTextureCoords[0][vertexIndex].y;
            }

            compactMesh.verts.push_back(vert);
        }
    }
    printer(compactMesh);
}
