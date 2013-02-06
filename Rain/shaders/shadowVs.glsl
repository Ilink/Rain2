uniform mat4 uMVMatrix;
uniform mat4 uPMatrix;

attribute vec3 pos;

varying vec4 vPosition;

void main(void) {
    vPosition = uMVMatrix * vec4(pos, 1.0);
    gl_Position = uPMatrix * vPosition;
}