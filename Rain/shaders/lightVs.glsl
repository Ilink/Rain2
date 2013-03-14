uniform mat4 uMVMatrix;
uniform mat4 uPMatrix;
uniform sampler2D uNormalsSampler;
uniform sampler2D uColorSampler;

//todo: use the uniforms instead of hardcoded values
// uniform vec3 uAmbientColor;
// uniform vec3 uLightingDirection;
// uniform vec3 uDirectionalColor;

attribute vec3 pos;
// attribute vec3 texCoord;

// varying vec2 vTexCoord;
varying vec3 vPositionE;
varying vec4 vPos;
// varying vec4 vProjPos;
// varying vec3 vLightPositionE;

void main(void) {
    // vTexCoord = texCoord;
    vPositionE = vec3(uMVMatrix * vec4(pos, 1.0));
    
    mat4 bias = mat4(
        0.5, 0.0, 0.0, 0.0,
        0.0, 0.5, 0.0, 0.0,
        0.0, 0.0, 0.5, 0.0,
        0.5, 0.5, 0.5, 1.0
    );
    // vPos = bias * uPMatrix * uMVMatrix * vec4(pos, 1.0);
    // vProjPos = bias * vPos;
    // vLightPositionE = mat3(uMVMatrix) * uLightPosition;
    // vLightPositionE = uMVMatrix * vec4(uLightPosition, 1.0);
    gl_Position = uPMatrix * uMVMatrix * vec4(pos, 1.0);
    vPos = bias*(gl_Position/gl_Position.w);
    // vPos = gl_Position;
    // vNormal = mat3(uMVMatrix) * normal;
}