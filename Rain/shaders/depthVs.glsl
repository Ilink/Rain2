attribute vec3 pos;
uniform mat4 uPMatrix;
uniform mat4 uMVMatrix;
void main(void) {
    gl_Position = uPMatrix * uMVMatrix * vec4(pos, 1.0);
};