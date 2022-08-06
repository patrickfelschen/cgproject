// https://learnopengl.com/Lighting/Basic-Lighting
#version 460 core

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec4 ambientColor;
in vec4 diffuseColor;
in vec4 specularColor;
in vec2 texCoord;
in vec3 currentPos;
in vec3 outNormal;
in float shininess;

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
    Light light;
    light.ambient = vec3(1.0f, 01.0f, 1.0f);
    light.diffuse = vec3(1.0f, 1.0f, 1.0f);
    light.specular = vec3(1.0f, 1.0f, 1.0f);

    vec4 diffTex = useTexture ? texture(tex0, texCoord) : vec4(1.0f, 1.0f, 1.0f, 1.0f);
    // ambient
    vec4 ambient = vec4(light.ambient, 1.0f) * ambientColor;

    // diffuse
    vec3 norm = normalize(outNormal);
    vec3 lightDir = normalize(lightPos - currentPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec4 diffuse = vec4(light.diffuse, 1.0f) * (diff * diffuseColor);

    // specular
    vec3 viewDir = normalize(camPos - currentPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), shininess);
    vec4 specular = vec4(light.specular, 1.0f) * (spec * specularColor);

    fragColor = (ambient + diffuse + specular) * diffTex;

}