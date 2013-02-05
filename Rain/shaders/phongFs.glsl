varying vec3 vLightWeighting;
varying vec4 vPosition;
varying vec3 vNormal;

void main(void) {
    vec3 color = vec3(0.8, 0.4, 0.1);
    vec3 specColor = vec3(0.1,0.5, 0.2);
    vec3 diffuseColor = vec3(0.2, 0.1, 0.2);

    vec3 eyeDirection = normalize(-vPosition.xyz);
    vec3 directionalVector = vec3(-1.0, -1.0, 0.0);

    vec3 reflectionDirection = reflect(-directionalVector, vNormal);
    float specularLightWeighting = pow(max(dot(reflectionDirection, eyeDirection), 0.0), 1.0);
    float diffuseLightWeighting = max(dot(vNormal, directionalVector), 0.0);

    vec3 lightWeighting = color
            + specColor * specularLightWeighting
            + diffuseColor * diffuseLightWeighting;

    gl_FragColor = vec4(color*vLightWeighting*lightWeighting, 1.0);
    // if(gl_FrontFacing){
    //     gl_FragColor = vec4(color*vLightWeighting*lightWeighting, 1.0);
    // } else {
    //     // discard;
    //     // gl_FragColor = vec4(0,0,0,1.0);
    // }
    
}