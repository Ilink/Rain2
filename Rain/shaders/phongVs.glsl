uniform mat4 uMVMatrix;
uniform mat4 uPMatrix;
uniform mat3 uNormalMatrix;
uniform vec3 uLightPosition;

//todo: use the uniforms instead of hardcoded values
// uniform vec3 uAmbientColor;
// uniform vec3 uLightingDirection;
// uniform vec3 uDirectionalColor;

attribute vec3 normal;
attribute vec3 pos;
attribute vec3 texCoord;

varying vec3 vNormal;
varying vec2 vTexCoord;
varying vec3 vPositionE;
varying vec3 vLightPositionE;

void main(void) {
    // vTexCoord = texCoord;
    vPositionE = vec3(uMVMatrix * vec4(pos, 1.0));
    // vLightPositionE = mat3(uMVMatrix) * uLightPosition;
    vLightPositionE = uMVMatrix * vec4(uLightPosition, 1.0);
    gl_Position = uPMatrix * uMVMatrix * vec4(pos, 1.0);
    
    vNormal = mat3(uMVMatrix) * normal;
}