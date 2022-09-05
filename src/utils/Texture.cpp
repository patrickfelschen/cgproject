//
// Created by Patrick on 17.08.2022.
//

#include "Texture.h"

Texture::Texture() : id(0), type("none") {}

/**
 * Erstellt eine weiße Textur
 * @param type Texturtype (texture_diffuse, texture_specular, ...)
 */
Texture::Texture(const std::string &type) : id(0), type(type) {
    RGBImage image(1, 1, GL_RGBA);
    image.setPixelColor(0, 0, Color(1.0f));
    create(image);
}

/**
 * Erstellt eine einfarbige Textur
 * @param type Texturtype (texture_diffuse, texture_specular, ...)
 */
Texture::Texture(const Color &pixel, const std::string &type) : id(0), type(type) {
    RGBImage image(1, 1, GL_RGBA);
    image.setPixelColor(0, 0, pixel);
    create(image);
}

/**
 * Erstellt eine Textur aus einer Bilddatei
 * @param filePath Pfad zur Bilddatei
 * @param type Texturtype (texture_diffuse, texture_specular, ...)
 */
Texture::Texture(const std::string &filePath, const std::string &type) : id(0), filePath(filePath), type(type) {
    RGBImage image;
    Loader::getInstance().readImageFile(filePath.c_str(), image);
    create(image);
}

Texture::~Texture() = default;

/**
 * Erstellt eine Textur und lädt diese in OpenGL
 * Quelle: https://learnopengl.com/Getting-started/Textures
 * Quelle: https://youtu.be/qEfohFgQ1-I?t=2181
 * @param image Textur Bild
 */
void Texture::create(RGBImage &image) {
    // Erstellen und binden einer neuen Textur
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    // Speicher für Texturen (und Mipmaps) erstellen
    // https://stackoverflow.com/a/15406829
    glTexStorage2D(
            GL_TEXTURE_2D,
            1, // Anzahl Mipmaps
            GL_RGBA32F, // Image Klasse besteht aus floats
            (GLsizei) image.getWidth(),
            (GLsizei) image.getHeight()
    );

    // Texturparameter setzen
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    // Daten in Textur Speicher laden
    glTexSubImage2D(
            GL_TEXTURE_2D,
            0,
            0,
            0,
            (GLsizei) image.getWidth(),
            (GLsizei) image.getHeight(),
            GL_RGBA,
            GL_FLOAT, // Image Klasse besteht aus floats
            image.getData().data() // Farbwerte
    );
    // Mipmaps generieren
    glGenerateMipmap(GL_TEXTURE_2D);
}

/**
 * Textur aktivieren
 * @param unit Textur Einheit welche aktiviert werden soll
 */
void Texture::activate(unsigned int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, id);
}

/**
 * Textur deaktivieren
 * @param unit Textur Einheit welche deaktiviert werden soll
 */
void Texture::deactivate(unsigned int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, 0);
}
