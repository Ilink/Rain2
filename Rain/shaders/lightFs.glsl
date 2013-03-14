uniform mat4 uMVMatrix;
uniform sampler2D uNormalsSampler;
uniform sampler2D uColorSampler;

varying vec3 vPositionE;
varying vec4 vPos;
varying vec4 vProjPos;
// varying vec3 vNormal;
// varying vec3 vLightPositionE;

vec3 Ka =  vec3(0.8, 0.4, 0.1);
vec3 Kd =  vec3(0.2, 0.1, 0.2);
vec3 Ks = vec3(0.5, 0.5, 0.5);
float Shininess = 1.0;
vec3 LightIntensity = vec3(1.0,1.0,1.0);

// vec3 ads(){
//     vec3 s = normalize( vLightPositionE - vPositionE ); // light to object
//     vec3 v = normalize(-vPositionE); // object to camera
//     vec3 r = reflect( -s, vNormal ); // object to light, reflected

//     return
//         LightIntensity * ( Ka + 
//           max( dot(s, vNormal), 0.0 )
//           + Ks * pow( max( dot(r,v), 0.0 ), Shininess ) );
// }

void main(void) {
    vec2 coord = gl_FragCoord.xy;
    // coord.x = coord.x / 800.0f;
    // coord.y = coord.y / 600.0f;
    // gl_FragColor = vec4(ads(), 1.0);
    // gl_FragColor = texture2D(uColorSampler, gl_FragCoord.xy);
    // gl_FragColor = texture2D(uColorSampler, coord);
    // gl_FragColor = texture2D(uColorSampler, vec2(0.5f, 0.5f));
    gl_FragColor = texture2D(uColorSampler, vPos.xy);
    // vec2 temp = texture2D(uColorSampler, vec2(0.0, 1.0));
    // gl_FragColor = texture2D(uColorSampler, vec2(0,1));

    // gl_FragColor = vec4(0.5, 0.5, 0.5, 1.0);
}