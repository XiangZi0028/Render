#ifndef RENDERER_ENUMS_H
#define RENDERER_ENUMS_H

enum {
    kLinear = 0,
    kNearest,
    kRepeat,
    kMirroredRepeat,
    kClampToEdge,
    kBorder
};

enum {
    kTexture1d,
    kTexture2d,
    kTexture3d,

    kRed, 
    kRg, 
    kRgb, 
    kRgba, 
    kStencil, 
    kDepth, 

    kUByte, 
    kByte, 
    kUShort, 
    kShort, 
    kUInt, 
    kInt, 
    kFloat
};

#endif