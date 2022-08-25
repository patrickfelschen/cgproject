#version 460

in VS_OUT {
    vec4 color;
    vec2 TexCoord0;
} fs_in;

uniform sampler2D uTexture0;

out vec4 fragColor;

void main() {
    vec4 tex = texture(uTexture0, fs_in.TexCoord0);
    fragColor = fs_in.color * tex;
}