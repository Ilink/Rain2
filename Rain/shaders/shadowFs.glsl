varying vec4 vPosition;
uniform sampler2D uShadowmapSampler;
varying vec4 vShadowCoord;
uniform vec4 uColor;
varying vec4 vNormal;
varying vec2 vTexCoord;
varying vec4 vPos;
varying vec4 quadUV;

const float pi = 3.14159;
const float total_strength = 1.0;
const float base = 0.2;

const float area = 0.0075;
const float falloff = 0.000001;

const float radius = 0.0002;

// borrowed the sample vectors from: http://www.theorangeduck.com/page/pure-depth-ssao
float3 samplesSphere[16] = {
    float3( 0.5381, 0.1856,-0.4319), float3( 0.1379, 0.2486, 0.4430),
    float3( 0.3371, 0.5679,-0.0057), float3(-0.6999,-0.0451,-0.0019),
    float3( 0.0689,-0.1598,-0.8547), float3( 0.0560, 0.0069,-0.1843),
    float3(-0.0146, 0.1402, 0.0762), float3( 0.0100,-0.1924,-0.0344),
    float3(-0.3577,-0.5301,-0.4358), float3(-0.3169, 0.1063, 0.0158),
    float3( 0.0103,-0.5869, 0.0046), float3(-0.0897,-0.4940, 0.3287),
    float3( 0.7119,-0.0154,-0.0918), float3(-0.0533, 0.0596,-0.5411),
    float3( 0.0352,-0.0631, 0.5460), float3(-0.4776, 0.2847,-0.0271)
};

void main() {
    float shadow = 1.0;
    vec3 shadowCoord = vShadowCoord.xyz / vShadowCoord.w;
    vec2 quadUV_W = quadUV.xy/quadUV.w;

    // Used to lower moire pattern and self-shadowing
    // shadowCoordinateWdivide.z += 0.5;
    shadowCoord.z += 0.00005;

    float distanceFromLight = texture2D(uShadowmapSampler,shadowCoord.st).z;

    // if the point is closer to the light, then it is in shadow. 
    if (vShadowCoord.w > 0.0) {
        if(distanceFromLight < shadowCoord.z){
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
    // gl_FragColor =  shadow * uColor;

    const int samples = 16;
    float occlusion = 0;
    float zFar = 1.0;
    float zNear = 0.25;

    // Linear depth
    float z_b = texture2D(uShadowmapSampler, quadUV_W.xy+0.01).z;
    float z_n = 2.0 * z_b - 1.0;
    float depthFrag = 2.0 * zNear * zFar / (zFar + zNear - z_n * (zFar - zNear));

    // float depthFrag = texture2D(uShadowmapSampler,quadUV_W).x;
    vec3 depthSpacePos = vec3(quadUV_W, depthFrag);
    
    for(int i = 0; i < samples; i++){
        vec3 lookupRay = depthSpacePos + sign(dot(vNormal.xyz, samplesSphere[i])) + samplesSphere[i];

        // float sampledDepth = texture2D(uShadowmapSampler, lookupRay.xy).z;
        float sampledDepth = texture2D(uShadowmapSampler, quadUV_W.xy+.01).z;

        float difference = 0;
        if(sampledDepth <= depthFrag){ // every frag tests true here
            difference = 0.0;
        } else {
            difference = sampledDepth - depthFrag;
        }
        difference = sampledDepth - depthFrag;

        occlusion += step(falloff, difference) * (1.0-smoothstep(falloff, area, difference));
        // occlusion += difference;
    }

    // float ao = 1.0 - total_strength * occlusion * (1.0 / samples);
    float ao = 1.0 - occlusion / samples;
    // gl_FragColor = clamp(occlusion, 0.0, 1.0);
    // gl_FragColor = clamp(ao, 0.0, 1.0);
    gl_FragColor = depthFrag;
}