varying vec4 vPosition;
uniform sampler2DShadow shadowMap;
varying vec4 ShadowCoord;

void main() {     
    float shadow = textureProj(shadowMap, ShadowCoord);
    gl_FragColor = vec4(shadow, 1.0);
}