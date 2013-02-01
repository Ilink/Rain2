#ifndef TYPES_H
#define TYPES_H

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

struct vertex {
    GLfloat x, y, z;        // Vertex
    GLfloat nx, ny, nz;     // Normal
    GLfloat u, v;           // Texcoord
};

struct Position {
	double x, y, z;
};

struct Color {
	GLfloat x, y, z;
};

// i think we need more of these, but they are unused right now
#define POSATTR 0
#define MVPUNI 1

#endif