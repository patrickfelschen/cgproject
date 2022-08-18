//https://learnopengl.com/code_viewer_gh.php?code=src/2.lighting/3.1.materials/3.1.materials.vs

#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord0;
layout (location = 3) in vec2 aTexCoord1;

uniform mat4 uTransform;
uniform mat4 uView;
uniform mat4 uProjection;

out VS_OUT {
    vec3 Pos;
    vec3 Normal;
    vec2 TexCoord0;
    vec2 TexCoord1;
} vs_out;

void main() {
    vs_out.Pos = vec3(uTransform * vec4(aPos, 1.0f));
    vs_out.Normal = mat3(transpose(inverse(uTransform))) * aNormal;
    vs_out.TexCoord0 = aTexCoord0;
    vs_out.TexCoord1 = aTexCoord1;

    gl_Position = uProjection * uView * uTransform  * vec4(aPos, 1.0);
}
