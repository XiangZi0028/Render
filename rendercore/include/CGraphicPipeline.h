#include"common.h"
#include"CTexture.h"
#include<map>
#include<vector>
#include<functional>
#define SDL_MAIN_HANDLED
#include<SDL.h>
class GraphicPipeline
{
private:
    stateSwitch cullFace;
    stateSwitch depethTest;
    std::vector<std::vector<float>> depthBuffer;
    std::vector<std::vector<colorPixel>> colorBuffer;
    int bufferMapIndexTop;
    int textureMapIndexTop;
    std::function <std::pair<void*,void*>(GraphicPipeline *pipeline,
                                         void* vsindefaul,
                                         int uniformbufferIndex)> vertexShader;
    // 参数 pipeline 3个顶点的vs_outs 三个顶点的权重 进去之后要要进行插值运算 uniformbufferindex
    std::function<colorPixel(GraphicPipeline* pipeline,
                            std::vector<std::pair<void*,void*>>, 
                            std::vector<float> weights,
                            int uniformbufferindex)>  fragmentShader;
    struct SDLWINDOW
    {
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;
        SDL_Event event;
        SDL_Rect rect;
    }window;
    int vertexBufferIndex;
    int indexBufferIndex;
    int targetWith;
    int targetHeight;
    int uniformBufferIndex_vertex;
    int uniformBufferIndex_fragment;
    
public:
    //all data buffer  uniformbuffer vertexbuffer indexbuffer
    std::map<int, DataBuffer*> bufferMap;
    //all texture buffer colorbuffer depth sencial 
    std::map<int, Texture*> textureMap;
public:
    GraphicPipeline(/* args */);
    ~GraphicPipeline();

    void init(); 
    int createDataBuffer();
    
    int createTexture();

    void setCullFace(stateSwitch ON_OFF);

    void setDepthTest(stateSwitch ON_OFF);

    void setTextureData(int identifier,int with,int height,int channel,void *data,int length);

    void setVertexBufferData(int identifier,void *data,int length);
    
    void setIndexBufferData(int identifier,void *data,int length);

    void setRendertargetSize(int with,int height);
    
    void setBuffer(int identifier,void *data,int length);

    void bindVertexBuffer(int identifier);

    void bindIndexBuffer(int identifier);

    void bindTexture(int identifier);
    
    void bindVertexShader(std::function <std::pair<void*,void*>(GraphicPipeline *,
                                         void*,
                                         int )>);

    void bindFragmentShader(std::function<colorPixel(GraphicPipeline*,
                            std::vector<std::pair<void*,void*>>, 
                            std::vector<float>,
                            int)>);

    void bindVertexUniformBuffer(int identifier);
    
    void bindFragmentUniformBuffer(int identifier);

    void drawElements(int count,int begin);

    void drawArray();
    void swapBuffer();
    bool quit();

    void clearColor(colorPixel color);
    void clearDepth(float depth);
};

