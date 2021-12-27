#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <fstream>
#include <map>
#include <functional>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "math.h"
#include "renderer_enums.h"
#include "texture.h"

extern math::vec4<double> gl_Position;

class Renderer {
    struct Vertex {
        Vertex() {}

        math::vec3<double> position;
        math::vec3<double> normal;
        math::vec2<double> uv;
    };
    struct UniformBuffer {
        math::vec3<double> lightColor;
        math::vec3<double> lightPos;
        math::vec3<double> viewPos;
    };
    struct ColorPixel {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        ColorPixel();
        ColorPixel(const math::vec4<double>& color);
        ColorPixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        ColorPixel& operator=(const ColorPixel& pixel);
    };
public:
    Renderer(uint32_t width, uint32_t height);
    ~Renderer();

    uint32_t createBuffer(size_t size);
    void setBufferData(uint32_t index, void* data, uint32_t size);
    void setBufferSubData(uint32_t index, void *data, uint32_t offset, uint32_t size);
    void destoryBuffer(uint32_t index);
    void bindVertexBuffer(uint32_t index);
    void bindIndexBuffer(uint32_t index);
    void bindUniformBuffer(uint8_t binding, uint32_t index);

    uint32_t createTexture(uint8_t target, uint8_t format, uint8_t type, 
        uint32_t width, uint32_t height, uint32_t depth);
    void setTextureData(uint32_t index, void* data, uint32_t size);
    void setTextureSubData(uint32_t index, void* data, uint32_t size, uint32_t xoffset, uint32_t yoffset, uint32_t width, uint32_t height);
    void setTextureSampler(uint32_t index, uint8_t minFilter, uint8_t magFilter, uint8_t wrapS, uint8_t wrapT);
    void destoryTexture(uint32_t index);
    void bindTexture(uint8_t binding, uint32_t index);

    void bindVertexShader(std::function<void*(void*, Renderer*, uint32_t)> func);
    void bindFragmentShader(std::function<math::vec4<double>(const std::vector<void*>&, uint32_t index,
        Renderer*, math::vec3<double>)> func);
    
    void clearDepth(double depth);
    void clearColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void depthTest(bool enable);
    void drawArrays(uint32_t vertexCount, uint32_t firstIndex);
    void drawIndex(uint32_t indexCount, uint32_t firstIndex);
    bool quit();

public:
    void* getCurrUboByBinding(uint8_t binding) {
        return mBufferMap.at(mUniformBufferBindingList[binding]).data;
    }
    Texture* getCurrTexByBinding(uint8_t binding) {
        return mTextureMap.at(mTextureBindingList[binding]);
    }
private:
    void raster(Vertex gl_Vertex0, Vertex gl_Vertex1, Vertex gl_Vertex2);
    size_t calculatePixelSize(uint8_t format, uint8_t type);
    void initSDL();
private:
    uint32_t width;
    uint32_t height;
    std::vector<std::vector<ColorPixel>> colorPixels;
    std::vector<std::vector<double>> depthPixels;
private:
    struct Buffer {
        void *data;
        size_t size;
    };
    std::map<uint32_t, Buffer> mBufferMap;
    uint32_t mBufferIndex;
    std::map<uint32_t, Texture*> mTextureMap;
    uint32_t mTextureIndex;
private: // 状态
    uint32_t mVertexBinding;
    uint32_t mIndexBinding;
    uint32_t mUniformBufferBindingList[6];
    uint32_t mTextureBindingList[16];
    std::function<void*(void*, Renderer*, uint32_t)> mVertexShader;
    std::function<math::vec4<double>(const std::vector<void*>&, uint32_t, 
        Renderer*, math::vec3<double> w)> mFragmentShader;
    bool mDepthEnable;
    bool mBlendEnable;

private:
    struct {
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;
        SDL_Event event;
        SDL_Rect rect;
    } mSDL;
};

#endif // !RENDERER_H
