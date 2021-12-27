#include "texture.h"
#include <assert.h>

Texture::~Texture() {
    free(data);
}

math::vec4<double> Texture::getPixel(size_t P) {
    assert(width >= P);
    math::vec4<double> result;
    if(type == kUByte || type == kByte) {
        uint8_t* ptr = (uint8_t*)data;
        size_t channels = getChannels(format);
        for(int c = 0; c <channels; ++c)
            result[c] = ptr[P * channels + c];
    } else if (type == kUShort || type == kShort) {
        uint16_t* ptr = (uint16_t*)data;
        size_t channels = getChannels(format);
        for(int c = 0; c <channels; ++c)
            result[c] = ptr[P * channels + c];
    } else if (type == kUInt || type == kInt || type == kFloat) {
        uint32_t* ptr = (uint32_t*)data;
        size_t channels = getChannels(format);
        for(int c = 0; c <channels; ++c)
            result[c] = ptr[P * channels + c];
    }
    return result;
}

math::vec4<double> Texture::getPixel(math::vec2<double> P) {
    int i = (P.x) * width;
    int j = (1 - P.y) * height - 0.001;
    if(sampler.wrapS == kRepeat) {
        i = i % width;
        if(i < 0) i += width;
    } else if(sampler.wrapS == kMirroredRepeat) {
        int m = i / width;
        if(m % 2) {
            i = i % width;
            if(i < 0) i += width;
        } else {
            i = i % width;
            if(i < 0)
                i = abs(i);
            else 
                i = width - i;
        }
    } else if(sampler.wrapS == kClampToEdge) {
        if (i < 0) i = 0;
        if (i > width - 1) i = width - 1;
    } else if(sampler.wrapS == kBorder) {
        if (i < 0 || i > width - 1)
            return math::vec4<double>(0.0);
    }

    if(sampler.wrapT == kRepeat) {
        j = j % height;
        if(j < 0) j += height;
    } else if(sampler.wrapT == kMirroredRepeat) {
        int m = j / height;
        if(m % 2) {
            j = j % height;
            if(j < 0) j += height;
        } else {
            j = j % height;
            if(j < 0)
                j = abs(j);
            else 
                j = height - j;
        }
    } else if(sampler.wrapT == kClampToEdge) {
        if (j < 0) j = 0;
        if (j > height - 1) j = height - 1;
    } else if(sampler.wrapT == kBorder) {
        if (j < 0 || j > height - 1)
            return math::vec4<double>(0.0);
    }

    math::vec4<double> result;
    if(type == kUByte || type == kByte) {
        uint8_t* ptr = (uint8_t*)data;
        size_t channels = getChannels(format);
        for(int c = 0; c < channels; ++c)
            result[c] = ptr[width * channels * j + i * channels + c];
    } else if (type == kUShort || type == kShort) {
        uint16_t* ptr = (uint16_t*)data;
        size_t channels = getChannels(format);
        for(int c = 0; c < channels; ++c)
            result[c] = ptr[width * channels * j + i * channels + c];
    } else if (type == kUInt || type == kInt || type == kFloat) {
        uint32_t* ptr = (uint32_t*)data;
        size_t channels = getChannels(format);
        for(int c = 0; c < channels; ++c)
            result[c] = ptr[width * channels * j + i * channels + c];
    }
    return result;
}

math::vec4<double> Texture::getPixel(math::vec3<double> P) {
    int i = (P.x) * width;
    int j = (1 - P.y) * height - 0.001;
    int k = (P.z) * depth;
    if(sampler.wrapS == kRepeat) {
        i = i % width;
        if(i < 0) i += width;
    } else if(sampler.wrapS == kMirroredRepeat) {
        int m = i / width;
        if(m % 2) {
            i = i % width;
            if(i < 0) i += width;
        } else {
            i = i % width;
            if(i < 0)
                i = abs(i);
            else 
                i = width - i;
        }
    } else if(sampler.wrapS == kClampToEdge) {
        if (i < 0) i = 0;
        if (i > width - 1) i = width - 1;
    } else if(sampler.wrapS == kBorder) {
        if (i < 0 || i > width - 1)
            return math::vec4<double>(0.0);
    }

    if(sampler.wrapT == kRepeat) {
        j = j % height;
        if(j < 0) j += height;
    } else if(sampler.wrapT == kMirroredRepeat) {
        int m = j / height;
        if(m % 2) {
            j = j % height;
            if(j < 0) j += height;
        } else {
            j = j % height;
            if(j < 0)
                j = abs(j);
            else 
                j = height - j;
        }
    } else if(sampler.wrapT == kClampToEdge) {
        if (j < 0) j = 0;
        if (j > height - 1) j = height - 1;
    } else if(sampler.wrapT == kBorder) {
        if (j < 0 || j > height - 1)
            return math::vec4<double>(0.0);
    }

    if(sampler.wrapR == kRepeat) {
        k = k % depth;
        if(k < 0) k += depth;
    } else if(sampler.wrapR == kMirroredRepeat) {
        int m = k / depth;
        if(m % 2) {
            k = k % depth;
            if(k < 0) k += depth;
        } else {
            k = k % depth;
            if(k < 0)
                k = abs(k);
            else 
                k = depth - k;
        }
    } else if(sampler.wrapR == kClampToEdge) {
        if (k < 0) k = 0;
        if (k > depth - 1) k = depth - 1;
    } else if(sampler.wrapR == kBorder) {
        if (k < 0 || k > depth - 1)
            return math::vec4<double>(0.0);
    }

    math::vec4<double> result;
    if(type == kUByte || type == kByte) {
        uint8_t* ptr = (uint8_t*)data;
        size_t channels = getChannels(format);
        for(int c = 0; c < channels; ++c)
            result[c] = ptr[width * channels * height * k + width * channels * j + i * channels];
    } else if (type == kUShort || type == kShort) {
        uint16_t* ptr = (uint16_t*)data;
        size_t channels = getChannels(format);
        for(int c = 0; c < channels; ++c)
            result[c] = ptr[width * channels * height * k + width * channels * j + i * channels];
    } else if (type == kUInt || type == kInt || type == kFloat) {
        uint32_t* ptr = (uint32_t*)data;
        size_t channels = getChannels(format);
        for(int c = 0; c < channels; ++c)
            result[c] = ptr[width * channels * height * k + width * channels * j + i * channels];
    }
    return result;
}

size_t getChannels(uint8_t format) {
    switch (format)
    {
    case kRed:
    case kStencil:
    case kDepth:
        return 1;
    case kRg:
        return 2;
    case kRgb:
        return 3;
    case kRgba:
        return 4;
    }
    return 0;
}
