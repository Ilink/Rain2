#ifndef TYPES_H
#define TYPES_H

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

struct vertex {
    GLfloat x, y, z;        //Vertex
    GLfloat nx, ny, nz;     //Normal
    GLfloat s0, t0;         //Texcoord
};

#define POSATTR 0
#define MVPUNI 1

#endif