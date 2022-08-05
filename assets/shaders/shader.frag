#version 460 core

in vec4 ambientColor;
in vec4 diffuseColor;
in vec4 specularColor;
in vec2 texCoord;
in vec3 currentPos;
in vec3 outNormal;

out vec4 fragColor;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform vec3 lightPos;
uniform vec3 camPos;
uniform bool useTexture;

float sat(in float a) {
    return clamp(a, 0.0, 1.0);
}

void main() {
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
    vec4 diffTex = useTexture ? texture(tex0, texCoord) : vec4(1.0f, 1.0f, 1.0f, 1.0f);
    if(diffTex.a < 0.3f) discard;
    vec3 N = normalize(outNormal);
    vec3 L = normalize(lightPos - currentPos);
    vec3 E = normalize(camPos - currentPos);
    vec3 R = reflect(-L, N);
    vec3 diffuseComponent = lightColor * diffuseColor.rgb * sat(dot(N, L));
    vec3 specularComponent = lightColor * specularColor.rgb * pow(sat(dot(R, E)), 24);
    fragColor = vec4((diffuseComponent + ambientColor.rgb) * diffTex.rgb + specularComponent, diffTex.a);
}