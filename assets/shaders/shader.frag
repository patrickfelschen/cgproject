#version 460 core

in vec4 color;
in vec2 texCoord;
in vec3 currentPos;
in vec3 outNormal;

out vec4 fragColor;

uniform sampler2D tex0;
uniform vec3 lightPos;
uniform vec3 camPos;

void main() {
    float ambient = 0.2f;

    vec3 normal = normalize(outNormal);
    vec3 lightDirection = normalize(lightPos - currentPos);
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    float specularIntensity = 1.5f;
    vec3  viewDirection = normalize(camPos - currentPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 12);
    float specular = specAmount * specularIntensity;

    fragColor = texture(tex0, texCoord) * color * (diffuse + ambient + specular);
}