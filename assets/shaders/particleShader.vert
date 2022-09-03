#version 420

// Attribut Inputs
layout (location = 0) in vec3 aPos;         // Position
layout (location = 1) in vec3 aNormal;      // Normale
layout (location = 2) in vec2 aTexCoord0;   // Texturkoordinaten 0
layout (location = 3) in vec2 aTexCoord1;   // Texturkoordinaten 1

// Uniform Buffer Inputs (min. Version 4.2)
// https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL (Uniform buffer objects)
layout (std140, binding = 0) uniform Matrices {
    mat4 uProjection;   // Projektions Matrix
    mat4 uView;         // View Matrix
    vec4 uCamPos;       // Kamera Position
};

uniform mat4 uTransform;    // Model Transform Matrix
uniform vec4 uColor;        // Farbe für Transparenz

// Output für Fragment Shader (FS) definieren
out VS_OUT {
    vec4 Color;
    vec2 TexCoord0;
} vs_out;

void main() {
    // Farbe für FS setzen
    vs_out.Color = uColor;
    // Texturkoordinaten für FS setzen
    vs_out.TexCoord0 = aTexCoord0;
    /*
        https://learnopengl.com/Getting-started/Coordinate-Systems
        Vertex Position mit der Projektions-, View-, und Modeltransformations-Matrix in CLIP SPACE transformieren.
        LOCAL SPACE -> [MODEL MATRIX] -> WORLD SPACE -> [VIEW MATRIX] -> VIEW SPACE -> [PROJECTION MATRIX] ->
        CLIP SPACE -> [VIEWPORT] -> SCREEN SPACE
    */
    gl_Position = uProjection * uView * uTransform  * vec4(aPos, 1.0);
}