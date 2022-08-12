#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uTransform;

out VS_OUT {
    vec3 Pos;
    vec2 TexCoord;
    vec3 Normal;
} vs_out;

void main() {
    gl_Position = uProjection * uView * uTransform  * vec4(aPos, 1.0);

    vs_out.Pos = vec3(uTransform * vec4(aPos, 1.0f));
    vs_out.TexCoord = aTexCoord;
    vs_out.Normal = aNormal;
}
