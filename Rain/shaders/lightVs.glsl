uniform mat4 uMVMatrix;
uniform mat4 uPMatrix;
uniform vec3 lightPos;
uniform vec3 lightDirection;

//todo: use the uniforms instead of hardcoded values
// uniform vec3 uAmbientColor;
// uniform vec3 uLightingDirection;
// uniform vec3 uDirectionalColor;

attribute vec3 pos;
attribute vec2 texCoord;

varying vec2 vTexCoord;
varying vec3 vPos;
varying vec3 vLightPositionS;
varying vec3 vLightDirection; // does this need to be transformed? probably, but idc right now

mat4 bias = mat4(
    0.5, 0.0, 0.0, 0.0,
    0.0, 0.5, 0.0, 0.0,
    0.0, 0.0, 0.5, 0.0,
    0.5, 0.5, 0.5, 1.0
);

void main(void) {
    vTexCoord = texCoord;
    vec4 lightPos = uPMatrix * uMVMatrix * vec4(lightPos, 1.0);
    
    vLightPositionS = bias*(lightPos / lightPos.w);

    vec4 temp = uPMatrix * uMVMatrix * vec4(lightDirection, 1.0);
    vLightDirection = bias * (temp / temp.w);

    gl_Position = vec4(pos, 1.0);
    vPos = bias*(gl_Position / gl_Position.w);
}