#version 460

out vec4 fragColor;

in VS_OUT {
    vec4 color;
    vec2 TexCoord0;
} fs_in;

uniform sampler2D texture_diffuse0;

vec4 diffuseTexture;

void main() {
    diffuseTexture = texture(texture_diffuse0, fs_in.TexCoord0);
    fragColor = fs_in.color * diffuseTexture;
}