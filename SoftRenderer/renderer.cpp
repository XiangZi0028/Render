#include "renderer.h"

#include <assert.h>

Renderer::ColorPixel::ColorPixel() 
	: r(0), g(0), b(0), a(0)
{

}

Renderer::ColorPixel::ColorPixel(const math::vec4<double>& color) {
    r = uint8_t(color.x);
    g = uint8_t(color.y);
    b = uint8_t(color.z);
    a = uint8_t(color.w);
}

Renderer::ColorPixel::ColorPixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}
Renderer::ColorPixel& Renderer::ColorPixel::operator=(const ColorPixel& pixel) {
    this->r = pixel.r;
    this->g = pixel.g;
    this->b = pixel.b;
    this->a = pixel.a;
    return *this;
}

Renderer::Renderer(uint32_t width, uint32_t height)
    : width(width)
    , height(height)
    , mBufferIndex(0)
    , mTextureIndex(0)
    , mVertexBinding(0)
    , mIndexBinding(0)
    , mDepthEnable(true)
    , mBlendEnable(false)
{
    colorPixels.resize(height);
    depthPixels.resize(height);
    for (uint32_t i = 0; i < height; ++i) {
        colorPixels[i].resize(width);
        depthPixels[i].resize(width);
    }

    for(int i = 0; i < 6; ++i)
        mUniformBufferBindingList[i] = 0;
    for(int i = 0; i < 16; ++i)
        mTextureBindingList[i] = 0;

    initSDL();
}

Renderer::~Renderer() {
    SDL_DestroyTexture(mSDL.texture);
    SDL_DestroyRenderer(mSDL.renderer);
    SDL_DestroyWindow(mSDL.window);
}

uint32_t Renderer::createBuffer(size_t size) {
    Buffer buffer;
    buffer.data = malloc(size);
    buffer.size = size;
    mBufferMap[mBufferIndex] = buffer;
    return mBufferIndex++;
}

void Renderer::setBufferData(uint32_t index, void* data, uint32_t size) {
    assert(mBufferMap.find(index) != mBufferMap.end());
    Buffer& buffer = mBufferMap[index];
    assert(buffer.size == size);
    memcpy(buffer.data, data, size);
}

void Renderer::setBufferSubData(uint32_t index, void *data, uint32_t offset, uint32_t size) {
    assert(mBufferMap.find(index) != mBufferMap.end());
    Buffer& buffer = mBufferMap[index];
    assert(buffer.size >= offset+size);
    void* src = (void*)((uint8_t*)data + offset);
    memcpy(buffer.data, src, size);
}

void Renderer::destoryBuffer(uint32_t index) {
    auto iter = mBufferMap.find(index);
    if(iter != mBufferMap.end())
    {
        free(iter->second.data);
        mBufferMap.erase(iter);
    }    
}

void Renderer::bindVertexBuffer(uint32_t index) {
    mVertexBinding = index;
}

void Renderer::bindIndexBuffer(uint32_t index) {
    mIndexBinding = index;
}

void Renderer::bindUniformBuffer(uint8_t binding, uint32_t index) {
    mUniformBufferBindingList[binding] = index;
}

uint32_t Renderer::createTexture(uint8_t target, uint8_t format, uint8_t type, 
    uint32_t width, uint32_t height, uint32_t depth) {
    Texture* texture = new Texture;
    texture->target = target;
    texture->format = format;
    texture->type = type;
    texture->width = width;
    texture->height = height;
    texture->depth = depth;
    texture->data = malloc(width*height*calculatePixelSize(format, type));
    mTextureMap[mTextureIndex] = texture;
    return mTextureIndex++;
}

void Renderer::setTextureData(uint32_t index, void* data, uint32_t size) {
    assert(mTextureMap.find(index) != mTextureMap.end());
    Texture*& texture = mTextureMap[index];
    assert(texture->width*texture->height*calculatePixelSize(texture->format, texture->type) == size);
    memcpy(texture->data, data, size);
}

void Renderer::setTextureSubData(uint32_t index, void* data, uint32_t size, uint32_t xoffset, uint32_t yoffset, uint32_t width, uint32_t height) {
    assert(mTextureMap.find(index) != mTextureMap.end());
    Texture*& texture = mTextureMap[index];
    assert(width*height == size);
    assert(texture->width >= xoffset + width);
    assert(texture->height >= yoffset + height);

    size_t pixelSize = calculatePixelSize(texture->format, texture->type);
    for(uint32_t i = 0; i < height; ++i) {
        uint8_t* dst = &((uint8_t*)texture->data)[(yoffset+i)*width*pixelSize + xoffset*pixelSize];
        uint8_t* src = &((uint8_t*)data)[i*width*pixelSize];
        memcpy(dst, src, width*pixelSize);
    }
}

void Renderer::setTextureSampler(uint32_t index, uint8_t minFilter, uint8_t magFilter, uint8_t wrapS, uint8_t wrapT) {
    assert(mTextureMap.find(index) != mTextureMap.end());
    Texture*& texture = mTextureMap[index];
    texture->sampler = {minFilter, magFilter, wrapS, wrapT};
}

void Renderer::destoryTexture(uint32_t index) {
    auto iter = mTextureMap.find(index);
    if(iter != mTextureMap.end())
    {
        delete iter->second;
        mTextureMap.erase(iter);
    }    
}

void Renderer::bindTexture(uint8_t binding, uint32_t index) {
    mTextureBindingList[binding] = index;
}

void Renderer::bindVertexShader(std::function<void*(void*, Renderer*, uint32_t)> func) {
    this->mVertexShader = func;
}
void Renderer::bindFragmentShader(std::function<math::vec4<double>(const std::vector<void*>&, uint32_t, 
    Renderer*, math::vec3<double>)> func) {
    this->mFragmentShader = func;
}

void Renderer::clearDepth(double depth) {
    for (int i = 0; i < depthPixels.size(); ++i)
        for (int j = 0; j < depthPixels[i].size(); ++j)
            depthPixels[i][j] = depth;
}

void Renderer::clearColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    for (int i = 0; i < depthPixels.size(); ++i)
        for (int j = 0; j < depthPixels[i].size(); ++j)
            colorPixels[i][j] = { r, g, b, a };
}

void Renderer::depthTest(bool enable) {
    mDepthEnable = enable;
}

void Renderer::drawArrays(uint32_t vertexCount, uint32_t firstIndex) {
    std::vector<math::vec4<double>> gl_Positions(vertexCount);
    std::vector<void*> vs_outs(vertexCount);
    void* vertices = mBufferMap[mVertexBinding].data;
    uint32_t count = 0;
    for (uint32_t i = firstIndex; i < vertexCount + firstIndex; ++i) {
        void* vs_out = mVertexShader(vertices, this, i);
        gl_Positions[count] = gl_Position;
        vs_outs[count++] = vs_out;
    }

    for(uint32_t i = 0; i < count; i += 3) {
        math::vec4<double> gl_Position0 = gl_Positions[i + 0];
        gl_Position0 = gl_Position0 / gl_Position0.w;
        gl_Position0 = (gl_Position0 + 1.0) / 2.0;

        math::vec4<double> gl_Position1 = gl_Positions[i + 1];
        gl_Position1 = gl_Position1 / gl_Position1.w;
        gl_Position1 = (gl_Position1 + 1.0) / 2.0;

        math::vec4<double> gl_Position2 = gl_Positions[i + 2];
        gl_Position2 = gl_Position2 / gl_Position2.w;
        gl_Position2 = (gl_Position2 + 1.0) / 2.0;

        // cull back
        math::vec2<double> v01 = math::normalize(math::vec2(gl_Position1 - gl_Position0));
        math::vec2<double> v12 = math::normalize(math::vec2(gl_Position2 - gl_Position0));
        if ((v01.x * v12.y - v01.y * v12.x) < 0.0f)
            return;

        double xmin = math::min(gl_Position0.x, gl_Position1.x, gl_Position2.x);
        double xmax = math::max(gl_Position0.x, gl_Position1.x, gl_Position2.x);
        double ymin = math::min(gl_Position0.y, gl_Position1.y, gl_Position2.y);
        double ymax = math::max(gl_Position0.y, gl_Position1.y, gl_Position2.y);

        uint32_t _xmin = math::max<uint32_t>(uint32_t(ceil(xmin * width)), 0);
        uint32_t _xmax = math::min<uint32_t>(uint32_t(floor(xmax * width)), width-1);
        uint32_t _ymin = math::max<uint32_t>(uint32_t(ceil(ymin * height)), 0);
        uint32_t _ymax = math::min<uint32_t>(uint32_t(floor(ymax * height)), height-1);

        // 光栅化
        for (uint32_t y = _ymin; y <= _ymax; ++y) {
            #pragma omp parallel
            #pragma omp for
            for (int x = _xmin; x <= _xmax; ++x) {
                math::vec2<double> pos = math::vec2<double>(double(x) / width, double(y) / height);

                math::vec2<double> R = pos - math::vec2<double>(gl_Position0);
                math::vec2<double> Q1 = math::vec2<double>(gl_Position1 - gl_Position0);
                math::vec2<double> Q2 = math::vec2<double>(gl_Position2 - gl_Position0);
                math::vec2<double> w = math::mat2<double>(math::vec2<double>(math::dot(Q2, Q2), -math::dot(Q1, Q2)), math::vec2<double>(-math::dot(Q1, Q2), math::dot(Q1, Q1)))
                    * math::vec2<double>(math::dot(R, Q1), math::dot(R, Q2))
                    * math::vec2<double>(1.0 / (math::dot(Q1, Q1) * math::dot(Q2, Q2) - math::dot(Q1, Q2) * math::dot(Q1, Q2)));
                double w1 = w.x;
                double w2 = w.y;
                double w0 = 1.0 - w1 - w2;

                if (w1 < 0.0 || w2 < 0.0 || w0 < 0) 
                    continue;
                gl_Position = gl_Position0 * math::vec4<double>(w0) + gl_Position1 * math::vec4<double>(w1) + gl_Position2 * math::vec4<double>(w2);
                // 深度测试
                if (gl_Position.z > depthPixels[y][x])
                    continue;
                depthPixels[y][x] = gl_Position.z;

                math::vec4<double> fragColor = mFragmentShader(vs_outs, i, this, math::vec3<double>(w0, w1, w2));
                colorPixels[height - y][x] = fragColor;
            }
        }
    }

    uint32_t size = width * height * 4;
    uint8_t* buff = (uint8_t*)malloc(size);
    for (uint32_t i = 0; i < height; ++i)
        memcpy(buff + i * width * 4, colorPixels[i].data(), width * 4);

    SDL_UpdateTexture(mSDL.texture, nullptr, buff, width * 4);
    SDL_SetRenderDrawColor(mSDL.renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(mSDL.renderer);
    SDL_Rect rect = { 0, 0, (int)width, (int)height };
    SDL_RenderCopy(mSDL.renderer, mSDL.texture, nullptr, &rect);
    SDL_RenderPresent(mSDL.renderer);
    free(buff);
}

void Renderer::drawIndex(uint32_t indexCount, uint32_t firstIndex) {
    std::vector<math::vec4<double>> gl_Positions(indexCount);
    std::vector<void*> vs_outs(indexCount);
    void* vertices = mBufferMap[mVertexBinding].data;
    uint32_t* indices = (uint32_t*)mBufferMap[mIndexBinding].data;
    uint32_t count = 0;
    for (uint32_t i = firstIndex; i < indexCount + firstIndex; ++i) {
        void* vs_out = mVertexShader(vertices, this, indices[i]);
        gl_Positions[count] = gl_Position;
        vs_outs[count++] = vs_out;
    }

    for(int i = 0; i < count; i += 3) {
        math::vec4<double> gl_Position0 = gl_Positions[i + 0];
        gl_Position0 = gl_Position0 / gl_Position0.w;
        gl_Position0 = (gl_Position0 + 1.0) / 2.0;

        math::vec4<double> gl_Position1 = gl_Positions[i + 1];
        gl_Position1 = gl_Position1 / gl_Position1.w;
        gl_Position1 = (gl_Position1 + 1.0) / 2.0;

        math::vec4<double> gl_Position2 = gl_Positions[i + 2];
        gl_Position2 = gl_Position2 / gl_Position2.w;
        gl_Position2 = (gl_Position2 + 1.0) / 2.0;

        // cull back
        math::vec2<double> v01 = math::normalize(math::vec2(gl_Position1 - gl_Position0));
        math::vec2<double> v12 = math::normalize(math::vec2(gl_Position2 - gl_Position0));
        if ((v01.x * v12.y - v01.y * v12.x) < 0.0f)
            continue;

        double xmin = math::min(gl_Position0.x, gl_Position1.x, gl_Position2.x);
        double xmax = math::max(gl_Position0.x, gl_Position1.x, gl_Position2.x);
        double ymin = math::min(gl_Position0.y, gl_Position1.y, gl_Position2.y);
        double ymax = math::max(gl_Position0.y, gl_Position1.y, gl_Position2.y);

        uint32_t _xmin = math::max<uint32_t>(uint32_t(ceil(xmin * width)), 0);
        uint32_t _xmax = math::min<uint32_t>(uint32_t(floor(xmax * width)), width-1);
        uint32_t _ymin = math::max<uint32_t>(uint32_t(ceil(ymin * height)), 0);
        uint32_t _ymax = math::min<uint32_t>(uint32_t(floor(ymax * height)), height-1);

        // 光栅化
        for (uint32_t y = _ymin; y <= _ymax; ++y) {
            #pragma omp parallel
            #pragma omp for
            for (int x = _xmin; x <= _xmax; ++x) {
                math::vec2<double> pos = math::vec2<double>(double(x) / width, double(y) / height);

                math::vec2<double> R = pos - math::vec2<double>(gl_Position0);
                math::vec2<double> Q1 = math::vec2<double>(gl_Position1 - gl_Position0);
                math::vec2<double> Q2 = math::vec2<double>(gl_Position2 - gl_Position0);
                math::vec2<double> w = math::vec2<double>(math::dot(R, Q1), math::dot(R, Q2))
                    *math::mat2<double>(math::vec2<double>(math::dot(Q2, Q2), -math::dot(Q1, Q2)), math::vec2<double>(-math::dot(Q1, Q2), math::dot(Q1, Q1)))
                    *math::vec2<double>(1.0 / (math::dot(Q1, Q1) * math::dot(Q2, Q2) - math::dot(Q1, Q2) * math::dot(Q1, Q2)));
                double w1 = w.x;
                double w2 = w.y;
                double w0 = 1.0 - w1 - w2;

                if (w1 < 0.0 || w2 < 0.0 || w0 < 0) 
                    continue;
                gl_Position = gl_Position0 * math::vec4<double>(w0) + gl_Position1 * math::vec4<double>(w1) + gl_Position2 * math::vec4<double>(w2);
                // 深度测试
                if(mDepthEnable) {
                    if (gl_Position.z > depthPixels[y][x])
                        continue;
                    depthPixels[y][x] = gl_Position.z;
                }

                math::vec4<double> fragColor = mFragmentShader(vs_outs, i, this, math::vec3<double>(w0, w1, w2));
                colorPixels[height - y][x] = fragColor;
            }
        }
    }

    uint32_t size = width * height * 4;
    uint8_t* buff = (uint8_t*)malloc(size);
    for (uint32_t i = 0; i < height; ++i)
        memcpy(buff + i * width * 4, colorPixels[i].data(), width * 4);

    SDL_UpdateTexture(mSDL.texture, nullptr, buff, width * 4);
    SDL_SetRenderDrawColor(mSDL.renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(mSDL.renderer);
    SDL_Rect rect = { 0, 0, (int)width, (int)height };
    SDL_RenderCopy(mSDL.renderer, mSDL.texture, nullptr, &rect);
    SDL_RenderPresent(mSDL.renderer);
    free(buff);
}

bool Renderer::quit() {
    SDL_PollEvent(&mSDL.event);
    if (mSDL.event.type == SDL_QUIT) {
        return true;
    }
    else
        return false;
}

size_t Renderer::calculatePixelSize(uint8_t format, uint8_t type) {
    size_t m, n;
    switch (format)
    {
    case kRed:
    case kStencil:
    case kDepth:
        m = 1;
        break;
    case kRg:
        m = 2;
        break;
    case kRgb:
        m = 3;
        break;
    case kRgba:
        m = 4;
        break;
    default:
        m = 0;
    }
    switch (type)
    {
    case kUByte:
    case kByte:
        n = 1;
        break;
    case kUShort:
    case kShort:
        n = 2;
        break;
    case kUInt:
    case kInt:
    case kFloat:
        n = 4;
        break;
    default:
        n = 0;
        break;
    }
    return m * n;
}

void Renderer::initSDL() {
    SDL_Init(SDL_INIT_AUDIO);
    mSDL.window = SDL_CreateWindow("Soft Renderer",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        0);
    mSDL.renderer = SDL_CreateRenderer(mSDL.window, -1, 0);
    mSDL.texture = SDL_CreateTexture(mSDL.renderer,
        SDL_PIXELFORMAT_ABGR8888,
        SDL_TEXTUREACCESS_STREAMING,
        width,
        height);
}