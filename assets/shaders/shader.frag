// https://learnopengl.com/Lighting/Basic-Lighting
// https://learnopengl.com/Advanced-Lighting/Advanced-Lighting
#version 460 core

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
    float shininess;
};

in vec2 texCoord;
in vec3 currentPos;
in vec3 outNormal;

out vec4 fragColor;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform Material material;
uniform vec3 lightPos;
uniform vec3 camPos;
uniform bool useTexture;

float sat(in float a) {
    return clamp(a, 0.0, 1.0);
}

bool blinn = true;

void main() {
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
    Light light;
    light.ambient = vec3(1.0f, 01.0f, 1.0f);
    light.diffuse = vec3(1.0f, 1.0f, 1.0f);
    light.specular = vec3(1.0f, 1.0f, 1.0f);

    vec4 diffTex = useTexture ? texture(tex0, texCoord) : vec4(1.0f, 1.0f, 1.0f, 1.0f);
    // ambient
    vec3 ambient = light.ambient * material.ambientColor;

    // diffuse
    vec3 norm = normalize(outNormal);
    vec3 lightDir = normalize(lightPos - currentPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = light.diffuse * (diff * material.diffuseColor);

    // specular
    float spec;
    vec3 viewDir = normalize(camPos - currentPos);
    if(blinn) {
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(norm, halfwayDir), 0.0f), material.shininess);
    }
    else {
        vec3 reflectDir = reflect(-lightDir, norm);
        spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    }
    vec3 specular = light.specular * (spec * material.specularColor);

    vec4 result = vec4((ambient + diffuse + specular), 1.0f);

    fragColor = result * diffTex;


}