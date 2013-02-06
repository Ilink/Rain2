varying vec3 vLightWeighting;
varying vec4 vPosition;

void main(void) {
    vec3 color = vec3(0.8, 0.4, 0.1);
    vec3 specColor = vec3(0.1,0.5, 0.2);
    vec3 diffuseColor = vec3(0.2, 0.1, 0.2);

    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}