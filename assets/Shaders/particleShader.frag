#version 420

// Output Fragment Farbe
out vec4 fragColor;

// Inputs aus Vertex Shader
in VS_OUT {
    vec4 Color;
    vec2 TexCoord0;
} fs_in;

uniform sampler2D texture_diffuse0;    // diffuser 2D Textur Sampler

vec4 diffuseTexture;    // diffuse Textur Farbe

void main() {
    // Farbwert über Texturkoordinaten aus Textur lesen
    diffuseTexture = texture(texture_diffuse0, fs_in.TexCoord0);
    // Textur Farbe mit Input-Farbe (Transparenz) multiplizieren
    fragColor = fs_in.Color * diffuseTexture;
}