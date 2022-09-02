//
// Created by Patrick on 17.08.2022.
//

#ifndef CG_TEXTURE_H
#define CG_TEXTURE_H

#include <string>
#include "RGBImage.h"
#include "Loader.h"

class Texture {
public:
    Texture();

    Texture(const std::string &type);

    Texture(const Color &pixel, const std::string &type);

    Texture(const std::string &filePath, const std::string &type);

    virtual ~Texture();

    void activate(unsigned int unit) const;

    void deactivate(unsigned int unit) const;

    GLuint id;
    std::string type;
private:
    std::string filePath;

    void create(RGBImage &image);
};


#endif //CG_TEXTURE_H
