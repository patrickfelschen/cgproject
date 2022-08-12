#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;

out vec2 texCoord;
out vec3 currentPos;
out vec3 outNormal;

void main() {
    currentPos = (transform * vec4(pos, 1.0f)).xyz;
    gl_Position = projection * view * transform  * vec4(pos, 1.0);
    texCoord = texCoords;
    outNormal = normal;
}