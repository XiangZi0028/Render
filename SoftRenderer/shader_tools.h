#ifndef SHADER_TOOLS_H
#define SHADER_TOOLS_H

#include <stdint.h>
#include "math.h"

struct sampler1D {
    uint8_t binding;

    sampler1D()
        : binding(0)
    {}

    sampler1D(uint8_t binding)
        : binding(binding)
    {}

    sampler1D& operator=(const sampler1D& s) {
        this->binding = s.binding;
    }
};

struct sampler2D {
    uint8_t binding;

    sampler2D()
        : binding(0)
    {}

    sampler2D(uint8_t binding)
        : binding(binding)
    {}

    sampler2D& operator=(const sampler2D& s) {
        this->binding = s.binding;
    }
};

struct sampler3D {
    uint8_t binding;

    sampler3D()
        : binding(0)
    {}

    sampler3D(uint8_t binding)
        : binding(binding)
    {}

    sampler3D& operator=(const sampler3D& s) {
        this->binding = s.binding;
    }
};

math::vec4<double> texture(sampler1D binding, size_t P, Renderer* renderer) {
    Texture* tex = renderer->getCurrTexByBinding(binding.binding);
    return tex->getPixel(P);
}

math::vec4<double> texture(sampler2D binding, math::vec2<double> P, Renderer* renderer) {
    Texture* tex = renderer->getCurrTexByBinding(binding.binding);
    return tex->getPixel(P);
}

math::vec4<double> texture(sampler3D binding, math::vec3<double> P, Renderer* renderer) {
    Texture* tex = renderer->getCurrTexByBinding(binding.binding);
    return tex->getPixel(P);
}

#endif