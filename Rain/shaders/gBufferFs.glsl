varying vec4 vPosition;
varying vec3 vNormal;

void main(void) {
    float ndcDepth = vPosition.z =
        (2.0 * gl_FragCoord.z - gl_DepthRange.near - gl_DepthRange.far) /
        (gl_DepthRange.far - gl_DepthRange.near);

    float clipDepth = ndcDepth / gl_FragCoord.w;
    // put me in another color buffer since default depth buffer sucks
    // gl_FragColor = vec4((clipDepth * 0.5) + 0.5);

    vec3 packedNormal = (normalize(vNormal) + 1.0)*0.5; //compress normal
    // vec3 packedNormal = normalize(vNormal); //compress normal

    gl_FragData[0] = vec4(packedNormal,1.0); // normals
    gl_FragData[1] = vec4(0.2, 1.0, 0.4, 1.0); // color
};