uniform mat4 uMVMatrix;
uniform mat4 uPMatrix;
attribute vec3 pos;

void main(void) {
    gl_Position = uPMatrix * uMVMatrix * vec4(pos, 1.0);
}