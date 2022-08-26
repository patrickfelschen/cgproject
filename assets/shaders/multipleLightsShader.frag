// https://learnopengl.com/Lighting/Basic-Lighting
// https://learnopengl.com/Advanced-Lighting/Advanced-Lighting
#version 460 core

struct Light {
    int Type;           // Typ der Lichtquelle (0=POINT, 1=DIRECTIONAL, 2=SPOT)
    vec3 Color;         // Farbe der Lichtquelle in RGB
    vec3 Position;      // Position der Lichtquelle (für DIRECTIONAL uninteressant)
    vec3 Direction;     // Ausrichtung der Lichtquelle (für POINT uninteressant)
    vec3 Attenuation;   // Koeffizienten für Intensitätsabfall über die Entfernung
    vec3 SpotRadius;    // SpotRadius.x enthält den inneren und SpotRadius.y den äußeren Radius der Spot-Lichtquelle
    int ShadowIndex;
};

in VS_OUT {
    vec3 Pos;
    vec3 Normal;
    vec2 TexCoord0;
    vec2 TexCoord1;
} fs_in;

uniform uLights {
    int LightCount;
    Light lights[MAX_LIGHTS];
};

uniform vec3 uLightPos;
uniform vec3 uCamPos;

uniform vec3 uDiffuseColor;
uniform vec3 uSpecularColor;
uniform vec3 uAmbientColor;
uniform float uSpecularExp;

uniform sampler2D uTexture0;
uniform sampler2D uTexture1;

out vec4 FragColor;

float sat(in float a) {
    return clamp(a, 0.0f, 1.0f);
}

vec3 DiffuseComponent = vec3(0.0f);
vec3 SpecularComponent = vec3(0.0f);

vec3 NormalDir;
vec3 CamDir;

// Punktlichtquelle (Vorlesung 3 Seite 21)
void addPointLight(in Light pointLight) {
    // Vektor von Fragment zur Lichtquelle
    vec3 LightDir = normalize(pointLight.Position - Position);
    // Distanz zwischen Fragment und Lichtquelle
    float Dist = length(pointLight.Position - Position);
    // Intensitätsabfall über Distanz berechnen (siehe CG_Praktiukum_6.pdf Seite 3)
    float Attenuation = 1.0f / (pointLight.Attenuation.x +
    pointLight.Attenuation.y * Dist +
    pointLight.Attenuation.z * Dist * Dist);
    // Winkelhalbierende von Punkt zum Betrachter und von Punkt zur Lichtquelle
    // Quelle: https://de.wikipedia.org/wiki/Blinn-Beleuchtungsmodell
    vec3 HalfVector = normalize(CamDir + LightDir);
    // Diffuse- und Spekularkomponente berechnen (siehe Vorlesung 3 Seite 17-19)
    float diffuse = sat(dot(NormalDir, LightDir));
    float specular = pow(sat(dot(HalfVector, NormalDir)), uSpecularExp);
    DiffuseComponent += pointLight.Color * Attenuation * uDiffuseColor * diffuse;
    SpecularComponent += pointLight.Color * Attenuation * uSpecularColor * specular;
}

// Direktionale Lichtquelle (Vorlesung 3 Seite 23)
void addDirectionalLight(in Light directionalLight) {
    // Vektor entgegengesetz der Strahlrichtung 
    // (Keine Berechnung über Position nötig, da Distanz unendlich ist)
    vec3 LightDir = normalize(-directionalLight.Direction);
    vec3 HalfVector = normalize(CamDir + LightDir);
    float diffuse = sat(dot(NormalDir, LightDir));
    float specular = pow(sat(dot(HalfVector, NormalDir)), uSpecularExp);
    DiffuseComponent += directionalLight.Color * uDiffuseColor * diffuse;
    SpecularComponent += directionalLight.Color * uSpecularColor * specular;
}

// Spot Lichtquelle (Vorlesung 3 Seite 22)
// Quelle: learnopengl_book.pdf, Kapitel 16.4 - 16.6
void addSpotLight(in Light spotLight) {
    vec3 LightDir = normalize(spotLight.Position - Position);
    vec3 HalfVector = normalize(CamDir + LightDir);
    float Dist = length(spotLight.Position - Position);
    float Attenuation = 1.0f / (spotLight.Attenuation.x +
    spotLight.Attenuation.y * Dist +
    spotLight.Attenuation.z * Dist * Dist);
    // Winkel zwischen Lichtausrichtung und Vektor von Punkt zur Lichtquelle
    // (Sollte kleiner als äußerer Spotlight Radius sein, damit Punkt innerhalb liegt)
    // acos liefert Winkel aus Skalarprodukt
    float theta = acos(dot(LightDir, normalize(-spotLight.Direction)));
    // Bereich zwischen äußeren und inneren Radius
    float epsilon = spotLight.SpotRadius.y - spotLight.SpotRadius.x;
    // Lineare Interpolation in Abhängigkeit von Winkel theta (Heilligkeit im Bereich von 1.0 - 0.0)
    float intensity = (1 - sat((theta - spotLight.SpotRadius.x) / epsilon));
    float diffuse = sat(dot(NormalDir, LightDir));
    float specular = pow(sat(dot(HalfVector, NormalDir)), uSpecularExp);
    DiffuseComponent += spotLight.Color * Attenuation * intensity * uDiffuseColor * diffuse;
    SpecularComponent += spotLight.Color * Attenuation * intensity * uSpecularColor * specular;
}

void main() {
    NormalDir = normalize(fs_in.Normal);
    CamDir = normalize(uCamPos - fs_in.Pos);
    vec4 DiffTex = texture(uTexture0, fs_in.TexCoord0);

    for (int i=0; i < LightCount; i++){

    }

    FragColor = vec4(
    DiffuseComponent * DiffTex.rgb +
    SpecularComponent * DiffTex.rgb +
    uAmbientColor * DiffTex.rgb,
    DiffTex.a
    );
}
