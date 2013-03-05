#include "normals.h"

using namespace std;

int getFace(int index, vector <glm::vec3>& faceNormals){
    return index/3;
}

/*
go through each face and calculate a normal
go through each vertex and find all the normals it shares
average all those adjacent normals
*/

void calcFaceNormals(vector <vertex>& verts, vector<GLuint>& triIndex){
    glm::vec3 vecA;
    glm::vec3 vecB;
    glm::vec3 vecC;
    glm::vec3 edgeA;
    glm::vec3 edgeB;
    glm::vec3 normal;
    vector<glm::vec3> faceNormals;

    // printf("tri index size: %i\n", triIndex.size());

    for(int i=0; i < triIndex.size(); i+=3){
        // printf("%i\n", i);
        vecA.x = verts[triIndex[i]].x;
        vecA.y = verts[triIndex[i]].y;
        vecA.z = verts[triIndex[i]].z;

        vecB.x = verts[triIndex[i+1]].x;
        vecB.y = verts[triIndex[i+1]].y;
        vecB.z = verts[triIndex[i+1]].z;

        vecC.x = verts[triIndex[i+2]].x;
        vecC.y = verts[triIndex[i+2]].y;
        vecC.z = verts[triIndex[i+2]].z;

        edgeA = vecB - vecA;
        edgeB = vecC - vecA;

        // printf("vecB: %f, %f, %f\n", vecA.x, vecA.y, vecA.z);
        // printf("edgeB: %f, %f, %f\n", edgeB.x, edgeB.y, edgeB.z);
        // printf("vecB: %i, %i, %i\n", verts[triIndex[i+1]].x, verts[triIndex[i+1]].z, verts[triIndex[i+1]].z);

        // This is the normal of the current face
        normal = glm::normalize(glm::cross(edgeA, edgeB));
        faceNormals.push_back(normal);
    }

    // for(int i = 0; i < faceNormals.size(); i++){
    //     printf("face normal: %f, %f, %f\n", faceNormals[i].x, faceNormals[i].y, faceNormals[i].z);
    // }

    // find the normals for each vertex
    for(int i=0; i < triIndex.size(); i++){
        GLuint current = triIndex[i];
        vertex& currentVert = verts[triIndex[i]];
        vector<int> adjacentNormalIndexes;
        glm::vec3 vertNormal;

        // find all the other triangles that share this vertex
        for(int j = 0; j < triIndex.size(); j++){
            if(triIndex[j] == current) adjacentNormalIndexes.push_back(getFace(j, faceNormals));
        }

        // average the normals from each face
        // this step could have weighting by angle
        for(int j = 0; j < adjacentNormalIndexes.size(); j++){
            glm::vec3 currentNormal = faceNormals[adjacentNormalIndexes[j]];
            if(j == 0){ // nothing to average with, so we just take the first normal
               currentVert.nx = currentNormal.x;
               currentVert.ny = currentNormal.y;
               currentVert.nz = currentNormal.z;
            } else {
               // printf("current normal: %f, %f, %f\n", currentNormal.x, currentNormal.y, currentNormal.z);
               currentVert.nx = currentNormal.x + currentVert.nx;
               currentVert.ny = currentNormal.y + currentVert.ny;
               currentVert.nz = currentNormal.z + currentVert.nz;
            }
        }
        currentVert.nx /= adjacentNormalIndexes.size();
        currentVert.ny /= adjacentNormalIndexes.size();
        currentVert.nz /= adjacentNormalIndexes.size();
        // printf("avg normal: %f, %f, %f\n", currentVert.nx, currentVert.ny, currentVert.nz);
    }

    // for(int i = 0; i < verts.size(); i++){
    //     printf("avg normal %i: %f, %f, %f\n", i, verts[i].nx, verts[i].ny, verts[i].nz);
    // }
}