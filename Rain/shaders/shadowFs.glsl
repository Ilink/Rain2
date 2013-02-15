varying vec4 vPosition;
// uniform sampler2D uShadowmapSampler;
uniform sampler2DShadow uShadowmapSampler;
varying vec4 vShadowCoord;

void main() {
    // gl_FragColor = texture2D(uShadowmapSampler, vShadowCoord.st);
    vec3 ambient = vec3(0.5, 0.5, 0.5);
    float shadow = textureProj(uShadowmapSampler, vShadowCoord);
    // float shadow = textureProj(uShadowmapSampler, vShadowCoord);
    // gl_FragColor = vec4(shadow, shadow, shadow, 1.0);
    gl_FragColor = vec4(ambient+shadow, 1.0);
}