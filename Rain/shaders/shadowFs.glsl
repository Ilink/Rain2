varying vec4 vPosition;
uniform sampler2D uShadowmapSampler;
varying vec4 vShadowCoord;
uniform vec4 uColor;

void main() {
    vec3 shadowCoord = vShadowCoord.xyz / vShadowCoord.w ;

    // Used to lower moire pattern and self-shadowing
    // shadowCoordinateWdivide.z += 0.5;
    shadowCoord.z += 0.0005;

    float distanceFromLight = texture2D(uShadowmapSampler,shadowCoord.st).z;

    float shadow = 1.0;
    // if the point is closer to the light, then it is in shadow. 
    if (vShadowCoord.w > 0.0) {
        if(distanceFromLight + 0.001 < shadowCoord.z){
            shadow = 0.5;
        } else {
            shadow = 1.0;
            // discard;
        }
    }

    // float lightDepth1 = texture2D(uShadowmapSampler, shadowCoordinateWdivide.st).r;
    // float lightDepth2 = clamp(length(vShadowCoord)/40.0, 0.0, 1.0);
    // float bias = 0.001;
    // float illuminated = step(clamp(length(vShadowCoord)/40.0, 0.0, 1.0), distanceFromLight+bias);
    // gl_FragColor =  illuminated * uColor;

    // gl_FragColor =  shadow * vec4(0.5, 0.4, 0.4, 1.0);
    gl_FragColor =  shadow * uColor;
}