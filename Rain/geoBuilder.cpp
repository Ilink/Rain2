#include "geoBuilder.h"

// 0,1,2
// 0,2,3
/*
     Front
    3----2
    |  / |
    | /  |
    0----1
*/

void makeBox(double height, double width, double depth, vector <vertex>& verts, vector<GLuint>& triIndex){
    verts.resize(24);
    triIndex.resize(36);

    // Front
    verts[0].x = 0.0;           verts[0].y = 0.0;           verts[0].z = 0.0;
    verts[1].x = width;         verts[1].y = 0.0;           verts[1].z = 0.0;
    verts[2].x = width;         verts[2].y = height;        verts[2].z = 0.0;
    verts[3].x = 0.0;           verts[3].y = height;        verts[3].z = 0.0;
    
    // Back
    verts[4].x = 0.0;         verts[4].y = 0.0;           verts[4].z = depth;
    verts[5].x = 0.0;           verts[5].y = height;           verts[5].z = depth;
    verts[6].x = width;           verts[6].y = height;        verts[6].z = depth;
    verts[7].x = width;         verts[7].y = 0.0;           verts[7].z = depth;

    // Top
    verts[8].x = 0.0;           verts[8].y = height;        verts[8].z = depth;
    verts[9].x = 0.0;           verts[9].y = height;        verts[9].z = 0.0;
    verts[10].x = width;        verts[10].y = height;       verts[10].z = 0.0;
    verts[11].x = width;        verts[11].y = height;       verts[11].z = depth;

    // Bottom
    verts[12].x = 0.0;          verts[12].y = 0.0;          verts[12].z = depth;
    verts[13].x = width;        verts[13].y = 0.0;          verts[13].z = depth;
    verts[14].x = width;        verts[14].y = 0.0;       verts[14].z = 0.0;
    verts[15].x = 0.0;          verts[15].y = 0.0;          verts[15].z = 0.0;

    // Right
    verts[16].x = width;        verts[16].y = 0.0;          verts[16].z = depth;
    verts[17].x = width;        verts[17].y = height;       verts[17].z = depth;
    verts[18].x = width;        verts[18].y = height;       verts[18].z = 0.0;
    verts[19].x = width;        verts[19].y = 0.0;          verts[19].z = 0.0;

    // Left
    verts[20].x = 0.0;          verts[20].y = 0.0;          verts[20].z = 0.0;
    verts[21].x = 0.0;          verts[21].y = 0.0;          verts[21].z = depth;
    verts[22].x = 0.0;          verts[22].y = height;       verts[22].z = depth;
    verts[23].x = 0.0;          verts[23].y = height;       verts[23].z = 0.0;

    // // Front face
    // 0.0, 0.0,  depth,
    // width, 0.0,  depth,
    // width,  height,  depth,
    // 0.0,  height,  depth,
    
    // // Back face
    // 0.0, 0.0, 0.0,
    // 0.0,  height, 0.0,
    // width,  height, 0.0,
    // width, 0.0, 0.0,

    // // Top face
    // 0.0, height, 0.0,
    // 0.0, height,  depth,
    // width, height,  depth,
    // width, height, 0.0,

    // // Bottom face
    // 0.0, 0.0, 0.0,
    // width, 0.0, 0.0,
    // width, 0.0,  depth,
    // 0.0, 0.0,  depth,

    // // Right face
    // width, 0.0, 0.0,
    // width, height, 0.0,
    // width, height,  depth,
    // width, 0.0,  depth,

    // // Left face
    // 0.0, 0.0, 0.0,
    // 0.0, 0.0,  depth,
    // 0.0,  height,  depth,
    // 0.0,  height, 0.0


    //     0,1,2,      0,2,3,      // front
    //     4,5,6,      4,6,7,      // back
    //     8,9,10,     8,10,11,    // top
    //     12,13,14,   12,14,15,   // bottom
    //     16,17,18,   16,18,19,   // right
    //     20,21,22,   20,22,23    // left

    // 0, 1, 2,
    // 2, 1, 3

    triIndex[0] = 0;    triIndex[1] = 1;    triIndex[2] = 2;
    triIndex[3] = 0;    triIndex[4] = 2;    triIndex[5] = 3;

    triIndex[6] = 4;    triIndex[7] = 5;    triIndex[8] = 6;
    triIndex[9] = 4;    triIndex[10] = 6;   triIndex[11] = 7;

    triIndex[12] = 8;   triIndex[13] = 9;   triIndex[14] = 10;
    triIndex[15] = 8;   triIndex[16] = 10;  triIndex[17] = 11;

    triIndex[18] = 12;  triIndex[19] = 13;  triIndex[20] = 14;
    triIndex[21] = 12;  triIndex[22] = 14;  triIndex[23] = 15;

    triIndex[24] = 16;  triIndex[25] = 17;  triIndex[26] = 18;
    triIndex[27] = 16;  triIndex[28] = 18;  triIndex[29] = 19;

    triIndex[30] = 20;  triIndex[31] = 21;  triIndex[32] = 22;
    triIndex[33] = 20;  triIndex[34] = 22;  triIndex[35] = 23;



    // triIndex[0] = 0;    triIndex[1] = 1;    triIndex[2] = 2;
    // triIndex[3] = 2;    triIndex[4] = 1;    triIndex[5] = 3;

    // triIndex[6] = 4;    triIndex[7] = 5;    triIndex[8] = 6;
    // triIndex[9] = 6;    triIndex[10] = 5;   triIndex[11] = 7;

    // triIndex[12] = 8;   triIndex[13] = 9;   triIndex[14] = 10;
    // triIndex[15] = 10;   triIndex[16] = 9;  triIndex[17] = 11;

    // triIndex[18] = 12;  triIndex[19] = 13;  triIndex[20] = 14;
    // triIndex[21] = 14;  triIndex[22] = 13;  triIndex[23] = 15;

    // triIndex[24] = 16;  triIndex[25] = 17;  triIndex[26] = 18;
    // triIndex[27] = 18;  triIndex[28] = 17;  triIndex[29] = 19;

    // triIndex[30] = 20;  triIndex[31] = 21;  triIndex[32] = 22;
    // triIndex[33] = 22;  triIndex[34] = 21;  triIndex[35] = 23;
}
