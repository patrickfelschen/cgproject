#version 420

// Maximale Anzahl an Beleuchtungen
const int MAX_LIGHT_COUNT = 30;

// Farb Output
out vec4 FragColor;

// Lichteigenschaften
struct Light {
    int type;           // Typ (0=POINT, 1=DIR, 2=SPOT)
    // Positionierung
    vec4 position;      // Position der Lichtquelle (für DIR uninteressant)
    vec4 direction;     // Ausrichtung der Lichtquelle (für POINT uninteressant)
    // Farbe
    vec4 ambient;       // Ambient Farbkomponente
    vec4 diffuse;       // Diffuse Farbkomponente
    vec4 specular;      // Specular Farbkomponente
    // Lichtabschwächung (POINT und SPOT)
    // Koeffizienten für Intensitätsabfall über die Entfernung
    // https://learnopengl.com/Lighting/Light-casters (Attenuation)
    // https://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
    float constant;     // Konstante, meist 1.0
    float linear;       // für lineare Intensität
    float quadratic;    // für quadratische Intensität
    // Bereich für SPOT
    float cutOff;       // innerer Radius
    float outerCutOff;  // äußerer Radius
};

// Materialeigenschaften
// https://learnopengl.com/Lighting/Materials
struct Material {
    vec4 ambient;       // Ambient Farbkomponente
    vec4 diffuse;       // Diffuse Farbkomponente
    vec4 specular;      // Specular Farbkomponente
    float shininess;    // Reflektionsstärke
};

// Inputs aus Vertex Shader
in VS_OUT {
    vec3 Pos;
    vec3 Normal;
    vec2 TexCoord0;
    vec2 TexCoord1;
} fs_in;

// Uniform Buffer Inputs (min. Version 4.2)
// https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL (Uniform buffer objects)
layout (std140, binding = 0) uniform Matrices {
    mat4 uProjection;   // Projektions Matrix
    mat4 uView;         // View Matrix
    vec4 uCamPos;       // Kamera Position
};
layout (std140, binding = 1) uniform Lights {
    int uStaticLightCount;                  // Anzahl der statischen Lichtquellen <= MAX_LIGHT_COUNT
    Light uDynamicLight;                    // Dynamisches Licht (Taschenlampe)
    Light uStaticLights[MAX_LIGHT_COUNT];   // Alle statischen Lichtquellen
};

uniform Material uMaterial;

uniform sampler2D texture_diffuse0;     // diffuse 2D Textur Sampler (Gras)
uniform sampler2D texture_diffuse1;     // diffuse 2D Textur Sampler (Stein)
uniform sampler2D texture_specular0;    // specular 2D Textur (weiß)
uniform sampler2D texture_mixmap0;      // mixmap 2D Textur Sampler

vec4 diffuseTexture;    // kombinierte diffuse Textur Farbe
vec4 specularTexture;   // specular Textur Farbe

vec4 calcDirLight(Light light, vec3 normal, vec3 viewDir);
vec4 calcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec4 calcSpotLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
    // Normale normalisieren
    vec3 normal = normalize(fs_in.Normal);
    // Kamera Richtung zur Position berechnen
    vec3 camDir = normalize(uCamPos.xyz - fs_in.Pos);
    // Farbwert über Texturkoordinaten aus Textur lesen
    vec4 grassTexture = texture(texture_diffuse0, fs_in.TexCoord1);
    vec4 rockTexture = texture(texture_diffuse1, fs_in.TexCoord1);
    vec4 mixTexture = texture(texture_mixmap0, fs_in.TexCoord0);
    // Lineare Interpolation der diffusen Texturen anhand der MixMap
    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/mix.xhtml
    diffuseTexture = mix(grassTexture, rockTexture, mixTexture);
    specularTexture = texture(texture_specular0, fs_in.TexCoord1);
    // Taschenlampen SPOT berechnen
    vec4 resultColor = calcSpotLight(uDynamicLight, normal, fs_in.Pos, camDir);
    // Über alle statischen Lichquellen iterieren und errechneten Farbwert summieren
    for (int i = 0; i < uStaticLightCount; i++){
        if (uStaticLights[i].type == 0){
            resultColor += calcPointLight(uStaticLights[i], normal, fs_in.Pos, camDir);
        }
        if (uStaticLights[i].type == 1){
            resultColor += calcDirLight(uStaticLights[i], normal, camDir);
        }
        if (uStaticLights[i].type == 2){
            resultColor += calcSpotLight(uStaticLights[i], normal, fs_in.Pos, camDir);
        }
    }
    // Farbresultat setzen
    FragColor = resultColor;
}

// Begrenzt Werte zwischen 0.0 und 1.0
float sat(float a) {
    return clamp(a, 0.0f, 1.0f);
}

// Direktionale Lichtquelle berechnen
// https://learnopengl.com/Lighting/Light-casters (Directional Light)
// https://learnopengl.com/Lighting/Multiple-lights (Directional light)
// https://learnopengl.com/code_viewer_gh.php?code=src/2.lighting/6.multiple_lights/6.multiple_lights.fs
vec4 calcDirLight(Light light, vec3 normal, vec3 viewDir) {
    // Vektor entgegengesetz der Strahlrichtung
    // (Keine Berechnung über Position nötig, da Distanz unendlich ist)
    vec3 lightDir = normalize(-light.direction.xyz);
    // Diffuse Komponente
    float diff = sat(dot(normal, lightDir));
    // Specular Komponente
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(sat(dot(viewDir, reflectDir)), uMaterial.shininess);
    // Kombination
    vec4 ambient  = light.ambient * diffuseTexture * uMaterial.ambient;
    vec4 diffuse  = light.diffuse  * diff * diffuseTexture * uMaterial.diffuse;
    vec4 specular = light.specular * spec * specularTexture * uMaterial.specular;
    return (ambient + diffuse + specular);
}

// Punkt Lichtquelle berechnen
// https://learnopengl.com/Lighting/Light-casters (Point lights)
// https://learnopengl.com/Lighting/Multiple-lights (Point light)
// https://learnopengl.com/code_viewer_gh.php?code=src/2.lighting/6.multiple_lights/6.multiple_lights.fs
vec4 calcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    // Vektor von Fragment zur Lichtquelle
    vec3 lightDir = normalize(light.position.xyz - fragPos);
    // Diffuse Komponente
    float diff = sat(dot(normal, lightDir));
    // Specular Komponente
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(sat(dot(viewDir, reflectDir)), uMaterial.shininess);
    // Lichtabschwächung
    // Distanz zwischen Fragment und Lichtquelle
    float distance = length(light.position.xyz - fragPos);
    // Intensitätsabfall über Distanz berechnen
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // Kombination
    vec4 ambient = light.ambient * diffuseTexture * uMaterial.ambient;
    vec4 diffuse = light.diffuse * diff * diffuseTexture * uMaterial.diffuse;
    vec4 specular = light.specular * spec * specularTexture * uMaterial.specular;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// Spot Lichtquelle berechnen
// https://learnopengl.com/Lighting/Light-casters (Spotlight)
// https://learnopengl.com/code_viewer_gh.php?code=src/2.lighting/6.multiple_lights/6.multiple_lights.fs
vec4 calcSpotLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position.xyz - fragPos);
    // Diffuse Komponente
    float diff = sat(dot(normal, lightDir));
    // Specular Komponente
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(sat(dot(viewDir, reflectDir)), uMaterial.shininess);
    // Lichtabschwächung
    // Distanz zwischen Fragment und Lichtquelle
    float distance = length(light.position.xyz - fragPos);
    // Intensitätsabfall über Distanz berechnen
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // Licht Intensität
    // https://learnopengl.com/Lighting/Light-casters (Smooth/Soft edges)
    float theta = dot(lightDir, normalize(-light.direction.xyz));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = sat((theta - light.outerCutOff) / epsilon);
    // Kombination
    vec4 ambient = light.ambient * diffuseTexture * uMaterial.ambient;
    vec4 diffuse = light.diffuse * diff * diffuseTexture * uMaterial.diffuse;
    vec4 specular = light.specular * spec * specularTexture * uMaterial.specular;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}
