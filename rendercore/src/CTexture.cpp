#include"CTexture.h"

glm::vec4 Texture::getPixel(glm::vec2 pos)
{
    uint8_t *pixels=(uint8_t*)data;
    int pixelPos_x=ceil(pos.x*(this->width));
    int pixelPos_y=ceil((pos.y)*(this->height));
    int pixelPos=(width*pixelPos_y+pixelPos_x)*channel;
    glm::vec4 color;
    color.x=pixels[pixelPos+0];
    color.y=pixels[pixelPos+1];
    color.z=pixels[pixelPos+2];
    color.a=pixels[pixelPos+3];
    return color;
}