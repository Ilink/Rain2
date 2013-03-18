varying vec4 vPosition;
varying vec3 vNormal;

void main(void) {
    float depth = vPosition.z =
        (2.0 * gl_FragCoord.z - gl_DepthRange.near - gl_DepthRange.far) /
        (gl_DepthRange.far - gl_DepthRange.near);

    float clipDepth = depth / gl_FragCoord.w;
    // gl_FragColor = vec4((clipDepth * 0.5) + 0.5);
    // gl_FragColor = vec4(0.2, 1.0, 0.4, 1.0);

    vec3 packedNormal = (normalize(vNormal) + 1.0)*0.5; //compress normal
    gl_FragData[0] = vec4(packedNormal,1.0);
    gl_FragData[1] = vec4(0.2, 1.0, 0.4, 1.0);
};