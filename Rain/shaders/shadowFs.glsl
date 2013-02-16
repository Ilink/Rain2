varying vec4 vPosition;
uniform sampler2D uShadowmapSampler;
// uniform sampler2DShadow uShadowmapSampler;
varying vec4 vShadowCoord;

void main() {
    vec4 shadow = texture2D(uShadowmapSampler, vShadowCoord.st);
    gl_FragColor = vec4(shadow.z, shadow.z, shadow.z, 1.0);
}