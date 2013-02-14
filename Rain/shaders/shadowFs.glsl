varying vec4 vPosition;
// uniform sampler2D uShadowmapSampler;
uniform sampler2DShadow uShadowmapSampler;
varying vec4 vShadowCoord;

void main() {
    // gl_FragColor = texture2D(uShadowmapSampler, vShadowCoord.st);
    float shadow = textureProj(uShadowmapSampler, vShadowCoord);
    // float shadow = textureProj(uShadowmapSampler, vShadowCoord);
    gl_FragColor = vec4(shadow, shadow, shadow, 1.0);
}