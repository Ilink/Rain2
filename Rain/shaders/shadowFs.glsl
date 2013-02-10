varying vec4 vPosition;
uniform sampler2DShadow uShadowmapSampler;
varying vec4 ShadowCoord;

void main() {     
    float shadow = textureProj(uShadowmapSampler, ShadowCoord);
    gl_FragColor = vec4(shadow, 1.0);
}