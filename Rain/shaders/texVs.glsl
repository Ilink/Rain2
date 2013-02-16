attribute vec3 pos;
attribute vec2 texCoord;
varying vec2 vTexCoord;
uniform mat4 uView;

void main() {
    gl_Position = uView * vec4(pos, 1.0);
    vTexCoord = texCoord;
}