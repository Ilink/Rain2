uniform mat4 uMVMatrix;
uniform mat4 uPMatrix;
uniform mat3 uNormalMatrix;

//todo: use the uniforms instead of hardcoded values
// uniform vec3 uAmbientColor;
// uniform vec3 uLightingDirection;
// uniform vec3 uDirectionalColor;

attribute vec3 normal;
attribute vec3 pos;

varying vec4 vPosition;
varying vec3 vNormal;
varying vec3 vLightWeighting;
varying vec3 vLightDirection;

void main(void) {
    vPosition = uMVMatrix * vec4(pos, 1.0);
    gl_Position = uPMatrix * vPosition;
    
    //todo: use the uniforms instead of these hardcoded values
    vec3 ambientLight = vec3(0.85, 0.5, 0.5);
    vec3 directionalLightColor = vec3(0.5, 0.5, 0.75);
    vec3 directionalVector = vec3(0.85, 0.8, 0.75);
    vLightDirection = directionalVector;
    
    vec3 transformedNormal = uNormalMatrix * normal;
    vNormal = transformedNormal;
    
    // we clamp to 0 because it doesn't make sense to have a negative value for the amount of light
    float directional = max(dot(transformedNormal.xyz, directionalVector), 0.0);
    vLightWeighting = ambientLight + directional;
    // vLightWeighting = ambientLight + (directionalLightColor * directional);
}