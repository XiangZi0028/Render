#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdint.h>
#include "renderer_enums.h"
#include "math.h"

class Texture
{
public:
    void* data;
    uint32_t width;
    uint32_t height;
    uint32_t depth;
    
    uint8_t target;
    uint8_t format;
    uint8_t type;
    
    struct {
        uint8_t minFilter = kNearest;
        uint8_t magFilter = kNearest;
        uint8_t wrapS = kRepeat;
        uint8_t wrapT = kRepeat;
        uint8_t wrapR = kRepeat;
    } sampler;

    Texture() = default;
    ~Texture();
    math::vec4<double> getPixel(size_t P);
    math::vec4<double> getPixel(math::vec2<double> P);
    math::vec4<double> getPixel(math::vec3<double> P);
};

size_t getChannels(uint8_t format);

#endif