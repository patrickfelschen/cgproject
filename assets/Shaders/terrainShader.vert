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

// Output für Fragment Shader (FS) definieren
out VS_OUT {
    vec3 Pos;
    vec3 Normal;
    vec2 TexCoord0;
    vec2 TexCoord1;
} vs_out;

void main() {
    // Transformierte Vertex Position für FS setzen
    vs_out.Pos = vec3(uTransform * vec4(aPos, 1.0f));
    /*
        https://learnopengl.com/Lighting/Basic-Lighting (One last thing)
        Normale mit Normalen Matrix berechnen, damit diese bei Skalierungen
        die richtige Richtung behalten.
    */
    vs_out.Normal = mat3(transpose(inverse(uTransform))) * aNormal;
    // Texturkoordinaten für FS setzen
    vs_out.TexCoord0 = aTexCoord0;
    vs_out.TexCoord1 = aTexCoord1;
    /*
        https://learnopengl.com/Getting-started/Coordinate-Systems
        Vertex Position mit der Projektions-, View-, und Modeltransformations-Matrix in CLIP SPACE transformieren.
        LOCAL SPACE -> [MODEL MATRIX] -> WORLD SPACE -> [VIEW MATRIX] -> VIEW SPACE -> [PROJECTION MATRIX] ->
        CLIP SPACE -> [VIEWPORT] -> SCREEN SPACE
    */
    gl_Position = uProjection * uView * uTransform  * vec4(aPos, 1.0);
}
