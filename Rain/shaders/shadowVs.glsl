uniform mat4 uMVMatrix;
uniform mat4 uMMatrix;
uniform mat4 uPMatrix;
uniform mat4 uShadowMatrix;
attribute vec3 pos;
attribute vec3 normal;
attribute vec2 texCoord;
varying vec4 vShadowCoord;
varying vec3 vNormal;
varying vec2 vTexCoord;
varying vec4 quadUV;
varying vec4 vPos;

void main(void) {
    // vec4 worldCoord = uMMatrix * vec4(pos, 1.0);
    vShadowCoord = uShadowMatrix * vec4(pos, 1.0);
    gl_Position = uPMatrix * uMVMatrix * vec4(pos, 1.0);
    vPos = gl_Position;
    vNormal = normal;
    vTexCoord = gl_MultiTexCoord0.st;
    // vTexCoord = vec2(0.5, 0.5);
    // quadUV = uMMatrix * vec4(pos, 1.0);
    mat4 bias = mat4(
        0.5, 0.0, 0.0, 0.0,
        0.0, 0.5, 0.0, 0.0,
        0.0, 0.0, 0.5, 0.0,
        0.5, 0.5, 0.5, 1.0
    );
    quadUV = vec4(bias*uPMatrix * uMVMatrix * vec4(pos, 1.0));
    // quadUV = vec2(gl_Position * 0.5 + 0.5);
}