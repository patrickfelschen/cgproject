//
//  TextureLoader.hpp
//
//  Created by Patrick Felschen on 02.06.22.
//

#ifndef TextureLoader_hpp
#define TextureLoader_hpp

#include <stdio.h>
#include "../GLincludes.hpp"
#include "FreeImage.h"
#include <string>

class TextureLoader{
public:
    static TextureLoader* Inst();
    virtual ~TextureLoader();
    
    bool getTexture(std::string filepath,
                    GLuint *texID,
                    GLenum image_format = GL_RGB,
                    GLint internal_format = GL_RGB,
                    GLint level = 0,
                    GLint border = 0);
protected:
    TextureLoader();
    TextureLoader(const TextureLoader& tm);
    TextureLoader& operator=(const TextureLoader& tm);

    static TextureLoader* m_inst;
};

#endif /* TextureLoader_hpp */
