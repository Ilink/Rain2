uniform sampler2D uNormalsSampler;
uniform sampler2D uColorSampler;

varying vec2 vTexCoord;
varying vec3 vLightPositionS;
varying vec3 vLightDirection;
varying vec3 vPos;

vec3 Ka =  vec3(0.8, 0.4, 0.1);
vec3 Kd =  vec3(0.2, 0.1, 0.2);
vec3 Ks = vec3(0.5, 0.5, 0.5);
float Shininess = 1.0;
vec3 LightIntensity = vec3(1.0,1.0,1.0);

vec3 ads(vec3 normal){
    vec3 s = normalize( vLightDirection - vPos ); // light to object
    vec3 v = normalize(-vPos); // object to camera
    vec3 r = reflect( -s, normal ); // object to light, reflected

    return
        LightIntensity * ( Ka + 
          max( dot(vLightDirection, normal), 0.0 )
          // max( dot(s, normal), 0.0 )
          + Ks * pow( max( dot(r,v), 0.0 ), Shininess ) );
}

void main(void) {
    vec3 normal = texture2D(uColorSampler, vTexCoord).xyz; // color and normals are reversed for some reason
    vec4 lightColor = vec4(ads(normal), 1.0);
    // gl_FragColor = vec4(lightColor.xyz * texture2D(uNormalsSampler, vTexLookup.xy).xyz, 1.0);\
    gl_FragColor = vec4(max( dot(normalize(vLightDirection), normal), 0.0 ));
    // gl_FragColor = lightColor;
    // gl_FragColor = vec4(normal, 1.0);
}