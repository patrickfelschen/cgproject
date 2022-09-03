#version 420

const int MAX_LIGHT_COUNT = 30;

out vec4 FragColor;

struct Light {
    int type;           // Typ (0=POINT, 1=DIR, 2=SPOT)

    vec4 position;      // Position der Lichtquelle (für DIR uninteressant)
    vec4 direction;     // Ausrichtung der Lichtquelle (für POINT uninteressant)

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;
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

layout (std140, binding = 0) uniform Matrices {
    mat4 uProjection;
    mat4 uView;
    vec4 uCamPos;
};

layout (std140, binding = 1) uniform Lights {
    int uStaticLightCount;
    Light uDynamicLight;
    Light uStaticLights[MAX_LIGHT_COUNT];
};

uniform Material uMaterial;

uniform sampler2D texture_diffuse0;
uniform sampler2D texture_specular0;

vec4 diffuseTexture;
vec4 specularTexture;

vec4 calcDirLight(Light light, vec3 normal, vec3 viewDir);
vec4 calcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec4 calcSpotLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
    vec3 normal = normalize(fs_in.Normal);
    vec3 camDir = normalize(uCamPos.xyz - fs_in.Pos);
    // texture color
    diffuseTexture = texture(texture_diffuse0, fs_in.TexCoord0);
    specularTexture = texture(texture_specular0, fs_in.TexCoord0);
    // result
    vec4 resultColor = calcSpotLight(uDynamicLight, normal, fs_in.Pos, camDir);
    for (int i = 0; i < uStaticLightCount; i++){
        if (uStaticLights[i].type == 0) {
            resultColor += calcPointLight(uStaticLights[i], normal, fs_in.Pos, camDir);
        }
        if (uStaticLights[i].type == 1) {
            resultColor += calcDirLight(uStaticLights[i], normal, camDir);
        }
        if (uStaticLights[i].type == 2) {
            resultColor += calcSpotLight(uStaticLights[i], normal, fs_in.Pos, camDir);
        }
    }
    // out
    FragColor = resultColor;
}

vec4 calcDirLight(Light light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction.xyz);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    // combine results
    vec4 ambient  = light.ambient * diffuseTexture * uMaterial.ambient;
    vec4 diffuse  = light.diffuse  * diff * diffuseTexture * uMaterial.diffuse;
    vec4 specular = light.specular * spec * specularTexture * uMaterial.specular;
    return (ambient + diffuse + specular);
}

vec4 calcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position.xyz - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    // attenuation
    float distance = length(light.position.xyz - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // combine results
    vec4 ambient = light.ambient * diffuseTexture * uMaterial.ambient;
    vec4 diffuse = light.diffuse * diff * diffuseTexture * uMaterial.diffuse;
    vec4 specular = light.specular * spec * specularTexture * uMaterial.specular;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec4 calcSpotLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position.xyz - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    // attenuation
    float distance = length(light.position.xyz - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction.xyz));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec4 ambient = light.ambient * diffuseTexture * uMaterial.ambient;
    vec4 diffuse = light.diffuse * diff * diffuseTexture * uMaterial.diffuse;
    vec4 specular = light.specular * spec * specularTexture * uMaterial.specular;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}

// https://learnopengl.com/Lighting/Multiple-lights
// https://learnopengl.com/code_viewer_gh.php?code=src/2.lighting/6.multiple_lights/multiple_lights.cpp
