#version 460 core

in VS_OUT {
    vec3 Pos;
    vec2 TexCoord;
    vec3 Normal;
} fs_in;

uniform Material uMaterial;
uniform sampler2D uTexture;

out vec4 FragColor;

void main() {
    FragColor = texture(uTexture, fs_in.TexCoord);
}
