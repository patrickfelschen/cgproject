#ifndef GLincludes_hpp
#define GLincludes_hpp

#ifdef _WIN32
#define ASSET_DIRECTORY "../assets/"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#else
#define ASSET_DIRECTORY "../assets/"
#define GLFW_INCLUDE_GLCOREARB
#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>
#endif

#endif /* GLincludes_hpp */
