#ifndef TEXTURE_H
#define TEXTURE_H
#include"common.h"
class Texture
{

public:
    Texture() = default;
    ~Texture();
    glm::vec4 getPixel(size_t P);//1d texture
    glm::vec4 getPixel(glm::vec2 P);//2d texture
    glm::vec4 getPixel(glm::vec3 P);//3d texture
public:
    void* data;
    int width;
    int height;
    int depth;
    
    textureFormat format;
    int channel;

    
};
#endif