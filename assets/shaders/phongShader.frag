// https://learnopengl.com/Lighting/Basic-Lighting
// https://learnopengl.com/Advanced-Lighting/Advanced-Lighting
// https://learnopengl.com/code_viewer_gh.php?code=src/2.lighting/3.1.materials/3.1.materials.fs

#version 460 core

struct Light {
    vec3 position;
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
uniform Light uLight;

uniform sampler2D uTexture0;
uniform sampler2D uTexture1;

out vec4 FragColor;

void main() {
    // Ambient Color
    vec4 ambient = uLight.ambient * uMaterial.ambient;
    // Diffuse Color
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightDir = normalize(uLight.position - fs_in.Pos);
    float diff = max(dot(normal, lightDir), 0.0f);
    vec4 diffuse = uLight.diffuse * (diff * uMaterial.diffuse);
    // Specular Color
    vec3 camDir = normalize(uCamPos - fs_in.Pos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(camDir, reflectDir), 0.0f), uMaterial.shininess);
    vec4 specular = uLight.specular * (spec * uMaterial.specular);
    vec4 resultColor = ambient + diffuse + specular;
    // Texture Color
    ivec2 size = textureSize(uTexture0, 0);
    if (size.x > 1){
        vec4 diffTex = texture(uTexture0, fs_in.TexCoord0);
        FragColor = diffTex * resultColor;
    } else {
        FragColor = resultColor;
    }
}