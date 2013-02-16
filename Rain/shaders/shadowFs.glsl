varying vec4 vPosition;
uniform sampler2D uShadowmapSampler;
// uniform sampler2DShadow uShadowmapSampler;
varying vec4 vShadowCoord;

void main() {
    vec4 shadow = texture2D(uShadowmapSampler, vShadowCoord.st);
    gl_FragColor = vec4(shadow.z, shadow.z, shadow.z, 1.0);

    if(shadow.z > vPosition.z){
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    } else {
        gl_FragColor = vec4(0.5, 0.4, 0.4, 1.0);
    }
}