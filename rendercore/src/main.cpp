#include"CGraphicPipeline.h"
#include"CTexture.h"
#include"common.h"
#include"CApp.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
struct MVPBuffer
{
    glm::mat4 proj;
    glm::mat4 view;
    glm::mat4 model;
}mvp;
int with=800;
int height=600;
int main()
{
   // App app;
    GraphicPipeline tranglePipeline;

    int indices[] = {
       0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        8, 9, 10, 10, 11, 8,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        20, 21, 22, 22, 23, 20
    };

    float vertices[] = {
         1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,

         1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,

        -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         1.0f, 1.0f, -1.0f,   0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,   0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        -1.0f, 1.0f,  1.0f,   0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
         1.0f, 1.0f,  1.0f,   0.0f, -1.0f,  0.0f,  1.0f, 0.0f,

         1.0f, -1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
    };
    mvp.model=glm::mat4(1.0);
    mvp.view=glm::mat4(1.0);
    mvp.proj=glm::mat4(1.0);

      struct FragUniform
    {
        int albedo;

    }fragmentUniformBuffer;
    
    int vbo=tranglePipeline.createDataBuffer();
    tranglePipeline.setVertexBufferData(vbo,vertices,sizeof(vertices));
    
    int ebo=tranglePipeline.createDataBuffer();
    tranglePipeline.setIndexBufferData(ebo,indices,sizeof(indices));

    int ubo_vertex=tranglePipeline.createDataBuffer();
    tranglePipeline.setBuffer(ubo_vertex,&mvp,sizeof(MVPBuffer));

    int w, h, channel;
    uint8_t* data = stbi_load("../../pic/a.png", &w, &h, &channel, 0);
    if(data==nullptr)
    {
        std::cout<<"stbi_load failed!"<<std::endl;
        return 1;
    }
    int albedo = tranglePipeline.createTexture();
    tranglePipeline.setTextureData(albedo,w,h,channel,data,w*h*channel);
    //stbi_image_free(data);

    fragmentUniformBuffer.albedo=albedo;
    int ubo_fragment=tranglePipeline.createDataBuffer();

    tranglePipeline.setBuffer(ubo_fragment,&fragmentUniformBuffer,sizeof(FragUniform));

    tranglePipeline.setRendertargetSize(with,height);
    auto vertexShader =[](GraphicPipeline *pipeline,void* vsindefault,int uniformbufferIndex)->std::pair<void*,void*>{
   
        struct VS_IN_UNIFORMBUFFER
        {
            glm::mat4 projeciton;
            glm::mat4 view;
            glm::mat4 model;
        };
        struct VS_OUT
        {
            glm::vec3 fragPos;
            glm::vec3 normal;
            glm::vec2 uv;
        };
                
        //传进来的数据转换成VS_IN数据结构
        VS_IN_DEFAULT *vs_in_default = ((VS_IN_DEFAULT*)vsindefault);
        //从buffer中取出数据转换成自定义的uniformbuffer
        VS_IN_UNIFORMBUFFER *ubo=(VS_IN_UNIFORMBUFFER*)pipeline->bufferMap[uniformbufferIndex]->data;

        VS_OUT_DEFAULT *vs_out_default=(VS_OUT_DEFAULT*)malloc(sizeof(VS_OUT_DEFAULT));
        //计算gl_Position
        vs_out_default->gl_Position=ubo->projeciton*ubo->view*ubo->model*glm::vec4(vs_in_default->position,1.0);

        VS_OUT *vs_out=(VS_OUT*)malloc(sizeof(VS_OUT));
        vs_out->fragPos=glm::vec3(ubo->model*glm::vec4(vs_in_default->position,1.0));
        vs_out->normal=vs_in_default->normal;
        vs_out->uv=vs_in_default->uv;

        std::pair<void*,void*> out;
        out.first=(void*)vs_out_default;
        out.second=(void*)vs_out;
        return out;
    };

  


    auto fragmentShader=[](GraphicPipeline* pipeline,std::vector<std::pair<void*,void*>> fsin, std::vector<float> weights,int uniformbufferindex)->colorPixel{
        
        struct FragUniform
        {
            int albedo;
        };
        FragUniform* frag_unifom=(FragUniform*)(pipeline->bufferMap[uniformbufferindex]);
        Texture *albedoTex=(Texture*)(pipeline->textureMap[0]);
        struct VS_OUT
        {
            glm::vec3 fragPos;
            glm::vec3 normal;
            glm::vec2 uv;
        };
        std::vector<VS_OUT_DEFAULT*> fs_in_default(3);
        std::vector<VS_OUT*> fs_in(3);
        glm::vec3 normal(0.0);
        glm::vec2 uv(0.0);
        for(int i=0;i<3;i++)
        {
            fs_in_default[i]=(VS_OUT_DEFAULT*)fsin[i].first;
            fs_in[i]=(VS_OUT*)fsin[i].second;
            normal+=fs_in[i]->normal*weights[i];
            uv+=fs_in[i]->uv*weights[i];
        }
         //colorPixel fragColor={normal.x*255,normal.y*255,normal.z*255,255.0};
        glm::vec4 albedoColor=albedoTex->getPixel(uv);
        colorPixel fragColor={albedoColor.x,albedoColor.y,albedoColor.z,albedoColor.w};
        return fragColor;

    };
    
    
    // mvp.model = glm::translate(mvp.model,glm::vec3(0.0f, 0.0f, -10.0f));
    float aspect=(float)with/(float)height;
    mvp.proj = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
    mvp.view= glm::lookAt(glm::vec3(0,0,1.0),glm::vec3(0,0,0),glm::vec3(0,1.0,0));

    double count = 0;
    tranglePipeline.setCullFace(stateSwitch::ON);   
    tranglePipeline.setDepthTest(stateSwitch::ON);
    glm::mat4 rotateMat(1.0);

    while (true)
    {
        mvp.model = glm::mat4(1.0f);
        mvp.model = glm::translate(mvp.model,glm::vec3(0.0f, 0.0f, -8.0f));
        rotateMat = glm::rotate(rotateMat,float(3.14/60), glm::vec3(0.0f, 1.0f, 0.0f));
        mvp.model = mvp.model*rotateMat;
        if (tranglePipeline.quit())
            break;
        tranglePipeline.clearColor({0,0,0,0});
        tranglePipeline.clearDepth(1.0);
        tranglePipeline.bindVertexBuffer(vbo);
        tranglePipeline.bindIndexBuffer(ebo);
        tranglePipeline.bindVertexShader(vertexShader);
        tranglePipeline.bindFragmentShader(fragmentShader);
        tranglePipeline.bindVertexUniformBuffer(ubo_vertex);
        tranglePipeline.bindFragmentUniformBuffer(ubo_fragment);
        tranglePipeline.drawElements(36,0);
        //tranglePipeline.swapBuffer();
        count++;
    }
    return 0;
}   