// https://learnopengl.com/Lighting/Basic-Lighting
// https://learnopengl.com/Advanced-Lighting/Advanced-Lighting
#version 460 core

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in VS_OUT {
    vec3 Pos;
    vec3 Normal;
    vec2 TexCoord0;
    vec2 TexCoord1;
} fs_in;

uniform vec3 uCamPos;

uniform Material uMaterial;
uniform Light uLight;

uniform sampler2D uTexture0;
uniform sampler2D uTexture1;
uniform sampler2D uTexture2;

out vec4 FragColor;

float sat(in float a) {
    return clamp(a, 0.0, 1.0);
}

bool blinn = true;

void main() {
    light.ambientColor = vec3(1.0f, 1.0f, 1.0f);
    light.diffuseColor = vec3(1.0f, 1.0f, 1.0f);
    light.specularColor = vec3(1.0f, 1.0f, 1.0f);

    // ambient
    vec3 ambient = light.ambientColor * uMaterial.ambientColor;

    vec3 norm = normalize(fs_in.Normal);
    vec3 lightDir = normalize(uLightPos - fs_in.Pos);

    // diffuse
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = light.diffuseColor * (diff * uMaterial.diffuseColor);

    // specular
    float spec;
    vec3 viewDir = normalize(uCamPos - fs_in.Pos);
    if (blinn) {
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(norm, halfwayDir), 0.0f), uMaterial.shininess);
    } else {
        vec3 reflectDir = reflect(-lightDir, norm);
        spec = pow(max(dot(viewDir, reflectDir), 0.0f), uMaterial.shininess);
    }
    vec3 specular = light.specularColor * (spec * uMaterial.specularColor);

    // Beleuchtung
    vec4 lightResultColor = vec4((ambient + diffuse + specular), 1.0f);

    // Texturen
    //vec4 texelMixTexture = texture(uTexture0, fs_in.TexCoord0).rgba;
    vec4 texelGrassTexture = texture(uTexture1, fs_in.TexCoord1).rgba;
    //vec4 texelRockTexture = texture(uTexture2, fs_in.TexCoord1).rgba;
    //vec4 textureResultColor = mix(texelGrassTexture, texelRockTexture, texelMixTexture);

    FragColor = lightResultColor * texelGrassTexture;
}
