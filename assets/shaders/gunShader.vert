#version 460 core

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

out VS_OUT {
    vec3 Pos;
    vec3 Normal;
    vec2 TexCoord0;
    vec2 TexCoord1;
} vs_out;

void main() {
    vs_out.Pos = vec3(uTransform * vec4(aPos, 1.0f));
    // https://learnopengl.com/Lighting/Basic-Lighting -> One last thing
    vs_out.Normal = mat3(transpose(inverse(uTransform))) * aNormal;
    vs_out.TexCoord0 = aTexCoord0;
    vs_out.TexCoord1 = aTexCoord1;

    gl_Position = uProjection * uTransform  * vec4(aPos, 1.0);
}

// https://learnopengl.com/code_viewer_gh.php?code=src/2.lighting/3.1.materials/3.1.materials.vs