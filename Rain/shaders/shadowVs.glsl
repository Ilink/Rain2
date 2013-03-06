uniform mat4 uMVMatrix;
uniform mat4 uMMatrix;
uniform mat4 uPMatrix;
uniform mat4 uShadowMatrix;
attribute vec3 pos;
attribute vec3 normal;
varying vec4 vShadowCoord;
varying vec3 vNormal;
varying vec2 uv;

void main(void) {
    // vec4 worldCoord = uMMatrix * vec4(pos, 1.0);
    vShadowCoord = uShadowMatrix * vec4(pos, 1.0);
    gl_Position = uPMatrix * uMVMatrix * vec4(pos, 1.0);
    // uv = (vec2( gl_Position.x, gl_Position.y ) + vec2( 1.0 ) ) * 0.5;
    uv = vec2(gl_Position.xy * 0.5 + 0.5);
    vNormal = normal;
}