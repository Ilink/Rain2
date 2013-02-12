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

    double left = -width/2.0;
    double right = width/2.0;
    double top = height/2.0;
    double bottom = -height/2.0;
    double close = -depth/2.0;
    double far = depth/2.0;

    // Front
    verts[0].x = left;          verts[0].y = bottom;           verts[0].z = close;
    verts[1].x = right;         verts[1].y = bottom;           verts[1].z = close;
    verts[2].x = right;         verts[2].y = top;              verts[2].z = close;
    verts[3].x = left;          verts[3].y = top;              verts[3].z = close;
    
    // Back
    verts[4].x = left;          verts[4].y = bottom;           verts[4].z = far;
    verts[5].x = left;          verts[5].y = top;              verts[5].z = far;
    verts[6].x = right;         verts[6].y = top;              verts[6].z = far;
    verts[7].x = right;         verts[7].y = bottom;           verts[7].z = far;

    // Top
    verts[8].x = left;           verts[8].y = top;             verts[8].z = close;
    verts[9].x = left;           verts[9].y = top;             verts[9].z = far;
    verts[10].x = right;         verts[10].y = top;            verts[10].z = far;
    verts[11].x = right;         verts[11].y = top;            verts[11].z = close;

    // Bottom
    verts[12].x = left;          verts[12].y = bottom;          verts[12].z = close;
    verts[13].x = right;        verts[13].y = bottom;          verts[13].z = close;
    verts[14].x = right;        verts[14].y = bottom;           verts[14].z = far;
    verts[15].x = left;          verts[15].y = bottom;          verts[15].z = far;

    // Right
    verts[16].x = right;        verts[16].y = bottom;          verts[16].z = far;
    verts[17].x = right;        verts[17].y = top;       verts[17].z = far;
    verts[18].x = right;        verts[18].y = top;       verts[18].z = close;
    verts[19].x = right;        verts[19].y = bottom;          verts[19].z = close;

    // Left
    verts[20].x = left;          verts[20].y = bottom;          verts[20].z = close;
    verts[21].x = left;          verts[21].y = bottom;          verts[21].z = far;
    verts[22].x = left;          verts[22].y = top;       verts[22].z = far;
    verts[23].x = left;          verts[23].y = top;       verts[23].z = close;


    /*
    the vertex index should be flipped, not the verts?
    */
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

// i would like to have a variant of this which lets the user specify an axis of orientation
void makePlane(double height, double width, vector <vertex>& verts, vector<GLuint>& triIndex){
    verts.resize(4);
    triIndex.resize(6);

    double left = -width/2.0;
    double right = width/2.0;
    double top = height/2.0;
    double bottom = -height/2.0;

    verts[0].x = left;          verts[0].y = bottom;           verts[0].z = 0.0;
    verts[1].x = right;         verts[1].y = bottom;           verts[1].z = 0.0;
    verts[2].x = right;         verts[2].y = top;              verts[2].z = 0.0;
    verts[3].x = left;          verts[3].y = top;              verts[3].z = 0.0;

    // set texture coordinates
    verts[0].u = 0.0; verts[0].v = 0.0;
    verts[1].u = 1.0; verts[1].v = 0.0;
    verts[2].u = 1.0; verts[2].v = 1.0;
    verts[3].u = 0.0; verts[3].v = 1.0;

    triIndex[0] = 0;    triIndex[1] = 1;    triIndex[2] = 2;
    triIndex[3] = 0;    triIndex[4] = 2;    triIndex[5] = 3;
}
