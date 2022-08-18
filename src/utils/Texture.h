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

    Texture(const std::string &filePath, const std::string &type);

    virtual ~Texture();

    void activate(unsigned int unit) const;

    void deactivate() const;

    GLuint id;
private:
    std::string type;
    std::string filePath;
};


#endif //CG_TEXTURE_H
