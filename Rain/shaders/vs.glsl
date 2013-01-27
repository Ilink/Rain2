// // uniform mat4 uMVPmat;

// void main(void){
//    vec4 a = gl_Vertex;
//    a.x = a.x * 0.5;
//    a.y = a.y * 0.5;


//    gl_Position = vec4(0.0, 0.0, 0.0, 0.0);
//    // gl_Position = gl_ModelViewProjectionMatrix * a;
//    // vPosition = uMVMatrix * vec4(position, 1.0);
//    // gl_Position = uPMatrix * vPosition;

//    // gl_Position = uMVPmat * vec4(position, 1.0);
//    // gl_Position = uMVPmat * a;
// }

// #version 120  // OpenGL 2.1
attribute vec3 pos;
uniform mat4 uMVPmat;
void main(void) {
	gl_Position = uMVPmat * vec4(pos, 1.0);
};