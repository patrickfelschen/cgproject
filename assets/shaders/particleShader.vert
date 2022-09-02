#version 420

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord0;
layout (location = 3) in vec2 aTexCoord1;

layout (std140, binding = 0) uniform Matrices {
    mat4 uProjection;
    mat4 uView;
    vec4 uCamPos;
};

uniform mat4 uTransform;
uniform vec4 uColor;
uniform float uScale;

out VS_OUT {
    vec4 Color;
    vec2 TexCoord0;
} vs_out;

void main() {
    vs_out.Color = uColor;
    vs_out.TexCoord0 = aTexCoord0;
    gl_Position = uProjection * uView * uTransform  * vec4(aPos * uScale, 1.0);
}