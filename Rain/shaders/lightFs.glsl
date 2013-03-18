uniform sampler2D uNormalsSampler;
uniform sampler2D uColorSampler;
uniform sampler2D uDepthSampler;
uniform mat4 uMVMatrix;


varying vec2 vTexCoord;
varying vec3 vLightPositionS;
varying vec4 vLightPosV;
varying vec3 vLightDirection;
varying vec3 vPos;
varying vec4 vPosV;

vec3 Ka =  vec3(0.8, 0.4, 0.1);
vec3 Kd =  vec3(0.2, 0.1, 0.2);
vec3 Ks = vec3(0.5, 0.5, 0.5);
float Shininess = 1.0;
vec3 LightIntensity = vec3(1.0,1.0,1.0);

float zFar = 1.0;
float zNear = 0.25;

//Makes depth values linear (i.e. inverse of the perpective projection)
float depthToLinearZ(float depth){
    return (zFar*zNear) / (zFar-(depth*(zFar-zNear)));
}

vec3 ads(vec3 normal, vec3 p){
    vec3 s = normalize( vLightPosV - p ); // light to object
    vec3 v = normalize(-p); // object to camera
    vec3 r = reflect( -s, normal ); // object to light, reflected

    return
        LightIntensity * ( Ka + 
          max( dot(vLightPosV, normal), 0.0 )
          // max( dot(s, normal), 0.0 )
          + Ks * pow( max( dot(r,v), 0.0 ), Shininess ) );
}

void main(void) {
    // color and normals are reversed for some reason
    vec3 normal = texture2D(uColorSampler, vTexCoord).xyz * 2.0 - 1.0;
    float depth = texture2D(uDepthSampler, vTexCoord).r;
    float linearDepth = depthToLinearZ(depth);

    // vec3 p = normalize(vPosV.xyz) * linearDepth; //position in view space of geometry

    vec4 p = vec4(vPos, 1.0);
    p = vPosV;
    p.z = linearDepth;
    mat4 invMV = inverse(uMVMatrix);
    vec4 pv = invMV * p;
    // pv = pv / pv.w;

    vec3 lightToPos = vLightPosV.xyz - pv.xyz;

    // gl_FragColor = vec4(lightColor.xyz * texture2D(uNormalsSampler, vTexLookup.xy).xyz, 1.0);
    // gl_FragColor = vec4(max( dot(normalize(vLightDirection), normal), 0.0 ));
    gl_FragColor = vec4(max( dot(normalize(lightToPos), normal), 0.0 ));

}