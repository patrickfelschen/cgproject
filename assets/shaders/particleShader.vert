#version 460

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord0;
layout (location = 3) in vec2 aTexCoord1;

//uniform mat4 uTransform;
//uniform mat4 uView;
uniform mat4 uProjection;
uniform vec3 uOffset;
uniform vec4 uColor;

out VS_OUT {
    vec4 color;
    vec2 TexCoord0;
} vs_out;

void main() {
    float scale = 0.001f;
    vs_out.color = uColor;
    vs_out.TexCoord0 = aTexCoord0;
    gl_Position = uProjection * vec4((aPos * scale) + uOffset, 1.0f);
}