#ifndef __COMMON_H
#define __COMMON_H
#include<glm/glm.hpp>
#include<iostream>
struct DataBuffer
{
        void *data;
        int size;
};
struct UniformBuffer {
        glm::vec3 lightColor;
        glm::vec3 lightPos;
        glm::vec3 viewPos;
    };

typedef enum stateSwitch{
    ON=true,
    OFF=false
};
struct colorPixel
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};
typedef enum textureFormat{
    Red, 
    RG, 
    RGB, 
    RGBA, 
    Stencil, 
    Depth,
};

typedef enum sampler{
    Linear ,
    Nearest,
    Repeat,
    MirroredRepeat,
    ClampToEdge,
    Border
};

struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
};

//顶点着色器的默认输入和默认输出
struct VS_OUT_DEFAULT
{        
        glm::vec4 gl_Position;
};

struct VS_IN_DEFAULT
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
};
#endif