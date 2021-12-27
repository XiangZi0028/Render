#pragma warning (disable : 4996)

#define STB_IMAGE_IMPLEMENTATION
#include "../3part/core_third_party/stb/stb_image.h"

#include "renderer.h"
#include "math.h"
#include "shader_tools.h"
#include "renderer_enums.h"

math::vec4<double> gl_Position;

struct FUniformBuffer {
    math::vec3<double> lightColor;
    math::vec3<double> lightPos;
    math::vec3<double> viewPos;
};

struct VUniformBuffer {
    math::mat4<double> projection;
    math::mat4<double> view;
    math::mat4<double> model;
};

int main(int argc, char* argv[]) {
    uint32_t width = 800;
    uint32_t height = 800;
    math::vec3<double> viewPos = math::vec3<double>(0.0, 0.0, 3.0);
    math::vec3<double> lightPos = math::vec3<double>(3.0, 3.0, 3.0);
    math::vec3<double> lightColor = math::vec3<double>(255.0f);

    math::mat4<double> projection = math::perspective<double>(45.0 / 57.29577951, double(width) / height, 0.1, 256.0);
    math::mat4<double> view = math::lookAt(viewPos, math::vec3<double>(0.0), math::vec3<double>(0.0, 1.0, 0.0));
    math::mat4<double> model = math::rotate(math::mat4<double>(1.0), 0.0, math::vec3<double>(0.0, 1.0, 0.0));
    model = math::scale(model, math::vec3<double>(0.5));
    
    double vertices[] = {
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
    uint32_t indices[] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        8, 9, 10, 10, 11, 8,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        20, 21, 22, 22, 23, 20
    };

    Renderer *renderer = new Renderer(width, height);
    uint32_t vbo = renderer->createBuffer(sizeof(vertices));
    renderer->setBufferData(vbo, vertices, sizeof(vertices));
    uint32_t ibo = renderer->createBuffer(sizeof(indices));
    renderer->setBufferData(ibo, indices, sizeof(indices));
    FUniformBuffer buf = { lightColor, lightPos, viewPos };
    uint32_t fubo = renderer->createBuffer(sizeof(FUniformBuffer));
    renderer->setBufferData(fubo, &buf, sizeof(FUniformBuffer));
    uint32_t vubo = renderer->createBuffer(sizeof(VUniformBuffer));
    
    int w, h, channel;
    uint8_t* data = stbi_load("E:/GLExample/pic/container2.png", &w, &h, &channel, 0);
    uint32_t albedo = renderer->createTexture(kTexture2d, kRgba, kUByte, w, h, 1);
    renderer->setTextureData(albedo, data, w * h * channel);
    stbi_image_free(data);

    auto vertexShader = [](void* _vs_in, Renderer* renderer, uint32_t index)->void*{
        struct VS_IN {
            math::vec3<double> position;
            math::vec3<double> normal;
            math::vec2<double> uv;
        };

        struct Uniform {
            struct UniformBuffer {
                math::mat4<double> projeciton;
                math::mat4<double> view;
                math::mat4<double> model;
            };
            uint8_t binding = 0;
        } uniform;
        
        struct VS_OUT {
            math::vec3<double> fragPos;
            math::vec3<double> normal;
            math::vec2<double> uv;
        };
        VS_IN* vs_in = &((VS_IN*)_vs_in)[index];
        Uniform::UniformBuffer* ubo = (Uniform::UniformBuffer*)renderer->getCurrUboByBinding(uniform.binding);

        gl_Position = ubo->projeciton * ubo->view * ubo->model * math::vec4<double>(vs_in->position, 1.0);
        VS_OUT* vs_out = (VS_OUT*)malloc(sizeof(VS_OUT));
        math::mat3<double> normalMatrix = math::inverseTranspose(math::mat3<double>(ubo->model));
        vs_out->normal = normalMatrix * vs_in->normal;
        vs_out->fragPos = math::vec3(ubo->model * math::vec4(vs_in->position, 1.0));
        vs_out->uv = vs_in->uv;
        return (void*)vs_out;
    };

    auto fragmentShader = [](const std::vector<void*>& _fs_ins, uint32_t index, Renderer* renderer, math::vec3<double> w)->math::vec4<double> {
        struct FS_IN {
            math::vec3<double> fragPos;
            math::vec3<double> normal;
            math::vec2<double> uv;
        };
        sampler2D albedo_texture = 0;
        struct Uniform {
            struct UniformBuffer {
                math::vec3<double> lightColor;
                math::vec3<double> lightPos;
                math::vec3<double> viewPos;
            };
            uint8_t binding = 1;
        } uniform;

        FS_IN fs_in;
        fs_in.fragPos = ((FS_IN*)_fs_ins[index + 0])->fragPos * w[0] + ((FS_IN*)_fs_ins[index + 1])->fragPos * w[1] + ((FS_IN*)_fs_ins[index + 2])->fragPos * w[2];
        fs_in.normal = ((FS_IN*)_fs_ins[index + 0])->normal * w[0] + ((FS_IN*)_fs_ins[index + 1])->normal * w[1] + ((FS_IN*)_fs_ins[index + 2])->normal * w[2];
        fs_in.uv = ((FS_IN*)_fs_ins[index + 0])->uv * w[0] + ((FS_IN*)_fs_ins[index + 1])->uv * w[1] + ((FS_IN*)_fs_ins[index + 2])->uv * w[2];
        Uniform::UniformBuffer* ubo = (Uniform::UniformBuffer*)renderer->getCurrUboByBinding(uniform.binding);

        math::vec3<double> albedo = math::vec3<double>(texture(albedo_texture, fs_in.uv, renderer));
        math::vec3<double> ambient = math::vec3<double>(albedo * math::vec3<double>(0.1));
        math::vec3<double> lightDir = math::normalize(ubo->lightPos - fs_in.fragPos);
        double diff = math::max(math::dot(lightDir, fs_in.normal), 0.0);

        math::vec3<double> viewDir = math::normalize(ubo->viewPos - fs_in.fragPos);
        math::vec3<double> halfDir = math::normalize(viewDir + lightDir);
        double spec = pow(math::max(math::dot(fs_in.normal, halfDir), 0.0), 32.0);

        math::vec4<double> fragColor = math::vec4<double>(ambient + albedo * diff + ubo->lightColor * spec, 1.0);
        return math::vec4<double>(math::vec3<double>(albedo), 255.0);
    };

    double framecount = 0;
    while (true)
    {
        renderer->clearDepth(1.0f);
        renderer->clearColor(0, 0, 0, 0);
        if (renderer->quit())
            break;
        model = math::rotate(math::mat4<double>(1.0), framecount, math::vec3<double>(0.0, 1.0, 0.0));
        model = math::scale(model, math::vec3<double>(0.5));
        VUniformBuffer buf = {projection, view, model};
        renderer->setBufferData(vubo, &buf, sizeof(VUniformBuffer));

        renderer->bindVertexBuffer(vbo);
        renderer->bindIndexBuffer(ibo);
        renderer->bindUniformBuffer(0, vubo);
        renderer->bindUniformBuffer(1, fubo);
        renderer->bindTexture(0, albedo);
        renderer->bindVertexShader(vertexShader);
        renderer->bindFragmentShader(fragmentShader);
        renderer->drawIndex(36, 0);
        ++framecount;
    }
    delete renderer;
    return 0;
}
