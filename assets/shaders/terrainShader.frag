#version 460 core

out vec4 FragColor;

struct DirLight {
    vec3 direction;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

struct Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
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

uniform DirLight uDirLight;
uniform PointLight uPointLight;
uniform SpotLight uSpotLight;

uniform sampler2D texture_diffuse0;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular0;
uniform sampler2D texture_mixmap0;

vec4 diffuseTexture;
vec4 specularTexture;

vec4 calcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    // combine results
    vec4 ambient  = light.ambient * diffuseTexture;
    vec4 diffuse  = light.diffuse  * diff * diffuseTexture;
    vec4 specular = light.specular * spec * specularTexture;
    return (ambient + diffuse + specular);
}

vec4 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // combine results
    vec4 ambient = light.ambient * diffuseTexture;
    vec4 diffuse = light.diffuse * diff * diffuseTexture;
    vec4 specular = light.specular * spec * specularTexture;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec4 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec4 ambient = light.ambient * diffuseTexture;
    vec4 diffuse = light.diffuse * diff * diffuseTexture;
    vec4 specular = light.specular * spec * specularTexture;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}

void main() {
    vec3 normal = normalize(fs_in.Normal);
    vec3 camDir = normalize(uCamPos - fs_in.Pos);
    // texture color
    vec4 grassTexture = texture(texture_diffuse0, fs_in.TexCoord1);
    vec4 rockTexture = texture(texture_diffuse1, fs_in.TexCoord1);
    vec4 mixTexture = texture(texture_mixmap0, fs_in.TexCoord0);

    diffuseTexture = mix(grassTexture, rockTexture, mixTexture);
    specularTexture = texture(texture_specular0, fs_in.TexCoord1);
    // result
    vec4 resultColor = calcDirLight(uDirLight, normal, camDir);
    resultColor += calcPointLight(uPointLight, normal, fs_in.Pos, camDir);
    resultColor += calcSpotLight(uSpotLight, normal, fs_in.Pos, camDir);
    // out
    FragColor = resultColor;
}

// https://learnopengl.com/Lighting/Multiple-lights
// https://learnopengl.com/code_viewer_gh.php?code=src/2.lighting/6.multiple_lights/multiple_lights.cpp
