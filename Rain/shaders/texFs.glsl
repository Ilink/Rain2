varying vec2 vTexCoord;
uniform sampler2D sampler;

void main(){
    gl_FragColor = texture2D(sampler, vTexCoord.st);
    // float zFar = 1.0;
    // float zNear = 0.25;
    // float z_b = texture2D(sampler, vTexCoord.xy).z;
    // float z_n = 2.0 * z_b - 1.0;
    // float z_e = 2.0 * zNear * zFar / (zFar + zNear - z_n * (zFar - zNear));

    // gl_FragColor = vec4(z_e, z_e, z_e, 1.0);
}