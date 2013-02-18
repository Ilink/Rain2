varying vec4 vPosition;
uniform sampler2D uShadowmapSampler;
varying vec4 vShadowCoord;

void main() {
    vec4 shadowCoordinateWdivide = vShadowCoord / vShadowCoord.w ;

    // Used to lower moire pattern and self-shadowing
    shadowCoordinateWdivide.z += 0.0005;

    float distanceFromLight = texture2D(uShadowmapSampler,shadowCoordinateWdivide.st).z;

    float shadow = 1.0;
    if (vShadowCoord.w > 0.0)
        shadow = distanceFromLight < shadowCoordinateWdivide.z ? 0.5 : 1.0 ;

    gl_FragColor =  shadow * vec4(0.5, 0.4, 0.4, 1.0);
}