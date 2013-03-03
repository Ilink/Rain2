attribute vec3 pos;
varying vec4 vPosition;
uniform mat4 uPMatrix;
uniform mat4 uMVMatrix;
void main(void) {
    vPosition = uPMatrix * uMVMatrix * vec4(pos, 1.0);
    gl_Position = vPosition;
};