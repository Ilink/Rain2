attribute vec3 pos;
attribute vec3 normal;

varying vec3 vNormal;
varying vec4 vPosition;
uniform mat4 uPMatrix;
uniform mat4 uMVMatrix;
uniform mat3 uNormalMatrix;

void main(void) {
    vPosition = uPMatrix * uMVMatrix * vec4(pos, 1.0);
    gl_Position = vPosition;
    vNormal = uNormalMatrix * normal;
};