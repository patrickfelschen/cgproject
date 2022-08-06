#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;
uniform vec3 acolor;
uniform vec3 dcolor;
uniform vec3 scolor;
uniform float shine;

out vec4 ambientColor;
out vec4 diffuseColor;
out vec4 specularColor;
out vec2 texCoord;
out vec3 currentPos;
out vec3 outNormal;
out float shininess;

void main() {
    currentPos = vec3(transform * vec4(pos, 1.0f));
    gl_Position = projection * view * transform  * vec4(pos, 1.0);
    texCoord = texCoords;
    outNormal = normal;
    ambientColor = vec4(acolor, 1);
    diffuseColor = vec4(dcolor, 1);
    specularColor = vec4(scolor, 1);
    shininess = shine;
}