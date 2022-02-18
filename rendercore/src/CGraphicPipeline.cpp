#include"CGraphicPipeline.h"
#include<assert.h>
#include<fstream>
GraphicPipeline::GraphicPipeline(/* args */):
                targetWith(0),
                targetHeight(0),
                vertexBufferIndex(-1),
                indexBufferIndex(-1),
                uniformBufferIndex_vertex(-1),
                uniformBufferIndex_fragment(-1),
                bufferMapIndexTop(-1),
                textureMapIndexTop(-1)
{

}

GraphicPipeline::~GraphicPipeline()
{
}

int GraphicPipeline::createDataBuffer()
{
    DataBuffer *buffer=new DataBuffer;
    buffer->size=0;
    buffer->data=nullptr;
    bufferMapIndexTop++;
    bufferMap[bufferMapIndexTop]=buffer;
    return bufferMapIndexTop;
}

int GraphicPipeline::createTexture(/**/)
{
    Texture *texture=new Texture;
    //
    textureMapIndexTop++;
    textureMap[textureMapIndexTop]=texture;
    return textureMapIndexTop;
}

void GraphicPipeline::setVertexBufferData(int identifier,void *data,int length){
    // assert(this->bufferMap.find(identifier));
    this->bufferMap[identifier]->data=data;
    this->bufferMap[identifier]->size=length;
}
void GraphicPipeline::setIndexBufferData(int identifier,void *data,int length)
{
    this->bufferMap[identifier]->data=data;
    this->bufferMap[identifier]->size=length;
}

void GraphicPipeline::setBuffer(int identifier,void *data,int length)
{
    this->bufferMap[identifier]->data=data;
    this->bufferMap[identifier]->size=length;
}

void GraphicPipeline::setTextureData(int identifier,int with,int height,int channel,void *data,int length)
{
    textureMap[identifier]->data=(void*)malloc(length);
    memcpy(textureMap[identifier]->data,data,length);
    textureMap[identifier]->width=with;
    textureMap[identifier]->height=height;
    textureMap[identifier]->channel=channel;

}

void  GraphicPipeline::bindVertexBuffer(int identifier)
{
    //assert(this->bufferMap.find(identifier));
    this->vertexBufferIndex=identifier;
}
void  GraphicPipeline::bindIndexBuffer(int identifier)
{
    // assert(this->bufferMap.find(identifier));
    this->indexBufferIndex=identifier;
}

void  GraphicPipeline::bindFragmentUniformBuffer(int identifier)
{
    //assert(this->bufferMap.find(identifier));
    this->uniformBufferIndex_fragment=identifier;
}
void  GraphicPipeline::bindVertexUniformBuffer(int identifier)
{
    // assert(this->bufferMap.find(identifier));
    this->uniformBufferIndex_vertex=identifier;
}

void GraphicPipeline::bindVertexShader(std::function <std::pair<void*,void*>(GraphicPipeline *,void*,int )> vertexshader)
{
    this->vertexShader=vertexshader;
}

void GraphicPipeline::bindFragmentShader(std::function<colorPixel(GraphicPipeline*,std::vector<std::pair<void*,void*>>, std::vector<float>,int)> fragmentshader)
{
    this->fragmentShader=fragmentshader;
}

void GraphicPipeline::setCullFace(stateSwitch ON_OFF)
{
    this->cullFace=ON_OFF;
}
void GraphicPipeline::setDepthTest(stateSwitch On_OFF)
{
    this->depethTest=On_OFF;
}
void GraphicPipeline::setRendertargetSize(int width,int height){
    this->targetHeight=height;
    this->targetWith=width;
    colorBuffer.resize(height);
    depthBuffer.resize(height);
    for (uint32_t i = 0; i < height; ++i) {
        colorBuffer[i].resize(width);
        depthBuffer[i].resize(width);
    }
    SDL_Init(SDL_INIT_AUDIO);
    
    window.window = SDL_CreateWindow("Soft Renderer",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        0);
    window.renderer = SDL_CreateRenderer(window.window, -1, 0);
    window.texture = SDL_CreateTexture(window.renderer,
        SDL_PIXELFORMAT_ABGR8888,
        SDL_TEXTUREACCESS_STREAMING,
        width,
        height);
}

void GraphicPipeline::drawElements(int count,int begin)
{
    //all points
    std::vector<glm::vec4> gl_Positions(count);
    std::vector<std::pair<void*,void*>> vs_outs(36);
    VS_IN_DEFAULT *all_vertice=(VS_IN_DEFAULT*)bufferMap[this->vertexBufferIndex]->data;
    int *all_indice=(int*)bufferMap[this->indexBufferIndex]->data;

    for(int i=begin;i<begin+count;i++)
    {
        int index=all_indice[i];
        VS_IN_DEFAULT *vertex=&all_vertice[index];
        
        std::pair<void*,void*> vs_out=vertexShader(this,vertex,uniformBufferIndex_vertex);
        vs_outs[i-begin]=vs_out;
        glm::vec4 gl_Position = ((VS_OUT_DEFAULT*)vs_out.first)->gl_Position;
        gl_Positions[i-begin]=gl_Position;
        // gl_Positions[i-begin]=gl_Positions[i-begin]/gl_Positions[i-begin].w;
        // gl_Positions[i-begin] = (gl_Positions[i-begin] + 1.0f) / 2.0f;
    }
    // Three groups of three to raster
    for(int i=0;i<count;i+=3)
    {
        //take three points at a time and each point goes from gl coordinates to NDC coordinates
        glm::vec4 gl_Position_0=gl_Positions[i+0];
        gl_Position_0=gl_Position_0/gl_Position_0.w;
        gl_Position_0 = (gl_Position_0 + 1.0f) / 2.0f;

        glm::vec4 gl_Position_1=gl_Positions[i+1];
        gl_Position_1=gl_Position_1/gl_Position_1.w;
        gl_Position_1 = (gl_Position_1 + 1.0f) / 2.0f;

        glm::vec4 gl_Position_2=gl_Positions[i+2];
        gl_Position_2=gl_Position_2/gl_Position_2.w;
        gl_Position_2=(gl_Position_2 + 1.0f) / 2.0f;
        
        //Whether to open the cutting surface
        if(this->cullFace==stateSwitch::ON)
        {
            glm::vec2 v01 = glm::normalize(glm::vec2(gl_Position_1 - gl_Position_0));
            glm::vec2 v02 = glm::normalize(glm::vec2(gl_Position_2 - gl_Position_0));
            if ((v01.x * v02.y - v01.y * v02.x) < 0.0f)
            {
                    continue;
            }
        }
        //X is associated with the window with and y is associated with the window height
        double xmin=std::min(std::min(gl_Position_0.x,gl_Position_1.x),gl_Position_2.x);
        double ymin=std::min(std::min(gl_Position_0.y,gl_Position_1.y),gl_Position_2.y);
        double xmax=std::max(std::max(gl_Position_0.x,gl_Position_1.x),gl_Position_2.x);
        double ymax=std::max(std::max(gl_Position_0.y,gl_Position_1.y),gl_Position_2.y);

        //Find the position range of the rectangle that corresponds to the coordinates on the screen
        int xmin_pix=std::max(ceil(xmin*targetWith),0.0);
        int ymin_pix=std::max(ceil(ymin*targetHeight),0.0);
        int xmax_pix=std::min(floor(xmax*targetWith),(double)targetWith);
        int ymax_pix=std::min(floor(ymax*targetHeight),(double)targetHeight);

        // Start by finding a rectangular box with 3 points and then check whether the points in the rectangle are inside the triangle
        // The fragment shader calculates the inner points and ignores the non-inner points
        // Pixels are stored in rows 1 by 1
        for(int y=ymin_pix;y<ymax_pix;y++)
        {
            // #pragma omp parallel
            // #pragma omp for
            for(int x=xmin_pix;x<xmax_pix;x++)
            {
                // Get the position of each pixel on the screen
                std::vector<float> wights(3);
                glm::vec2 pos_in_screen=glm::vec2(float(x)/targetWith,float(y)/targetHeight);
                //Determine if each point is inside the triangle
                glm::vec2 v0=glm::vec2(gl_Position_1-gl_Position_0);//w1->gl_Postion_1 weight
                glm::vec2 v1=glm::vec2(gl_Position_2-gl_Position_0);//w2->gl_Postion_2 weight
                glm::vec2 v2=pos_in_screen-glm::vec2(gl_Position_0);
                float dot00=glm::dot(v0,v0);
                float dot01=glm::dot(v0,v1);
                float dot02=glm::dot(v0,v2);
                float dot11=glm::dot(v1,v1);
                float dot12=glm::dot(v1,v2);
                float inverDeno=1/(dot00*dot11-dot01*dot01);
                wights[1]=(dot11*dot02-dot01*dot12)*inverDeno;
                wights[2]=(dot00*dot12-dot01*dot02)*inverDeno;
                wights[0]=1.0-wights[1]-wights[2];
                // if(wights[1]<0||wights[1]>1)
                //     continue;
                // if(wights[2]<0||wights[2]>1)
                //     continue;
                if (wights[0] < 0.0 || wights[1] < 0.0 || wights[2] < 0) 
                    continue;
                //On the inside we have to figure out how deep it is
                glm::vec4 gl_Position=glm::vec4(wights[0])*gl_Position_0+
                                      glm::vec4(wights[1])*gl_Position_1+
                                      glm::vec4(wights[2])*gl_Position_2;
                if(this->depethTest==stateSwitch::ON)
                {
                    if(gl_Position.z > depthBuffer[y][x])
                        continue;
                    depthBuffer[y][x]=gl_Position.z;
                }

                //Fragment shader
                std::vector<std::pair<void*,void*>> fs_in(3);
                fs_in[0]=vs_outs[i+0];
                fs_in[1]=vs_outs[i+1];
                fs_in[2]=vs_outs[i+2];
                colorBuffer[y][x]=fragmentShader(this,fs_in,wights,uniformBufferIndex_fragment);
            }
        }
        
    }
    swapBuffer();
}

void GraphicPipeline::swapBuffer()
{
    uint32_t size = targetWith * targetHeight * 4;
    uint8_t* buff = (uint8_t*)malloc(size);
    for (int i = 0; i < targetHeight; ++i){
        memcpy(buff + i * targetWith * 4, colorBuffer[i].data(), targetWith * 4);
    }
    SDL_UpdateTexture(window.texture, nullptr, buff, targetWith * 4);
    SDL_SetRenderDrawColor(window.renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(window.renderer);
    SDL_Rect rect = { 0, 0, (int)targetWith, (int)targetHeight };
    SDL_RenderCopy(window.renderer, window.texture, nullptr, &rect);
    SDL_RenderPresent(window.renderer);
    free(buff);
}

bool GraphicPipeline::quit()
{
    SDL_PollEvent(&window.event);
    if (window.event.type == SDL_QUIT) {
        return true;
    }
    else
        return false;
}

void GraphicPipeline::clearColor(colorPixel color)
{
    for(int i=0;i<colorBuffer.size();i++)
    {
        for(int j=0;j<colorBuffer[i].size();j++)
            colorBuffer[i][j]=color;
    }
}

void GraphicPipeline::clearDepth(float depth)
{
    for(int i=0;i<depthBuffer.size();i++)
    {
        for(int j=0;j<depthBuffer[i].size();j++)
            depthBuffer[i][j]=depth;
    }
}