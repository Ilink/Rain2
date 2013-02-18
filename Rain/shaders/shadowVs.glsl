uniform mat4 uMVMatrix;
uniform mat4 uMMatrix;
uniform mat4 uPMatrix;
uniform mat4 uShadowMatrix;
attribute vec3 pos;
varying vec4 vShadowCoord;

void main(void) {
    vec4 worldCoord = uMMatrix * vec4(pos, 1.0);
    vShadowCoord = uShadowMatrix * vec4(pos,1.0);
    // vShadowCoord = uShadowMatrix * vec4(pos,1.0); 
    gl_Position = uPMatrix * uMVMatrix * vec4(pos, 1.0);
}