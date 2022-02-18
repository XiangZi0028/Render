#include"CApp.h"

AppWindow::AppWindow(/* args */)
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::createWindow(int with,int height)
{
    this->windowWidth=with;
    this->windowHeight=height;
     SDL_Init(SDL_INIT_AUDIO);
    window = SDL_CreateWindow("Soft Renderer",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        windowWidth,
        windowHeight,
        0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ABGR8888,
        SDL_TEXTUREACCESS_STREAMING,
        windowWidth,
        windowHeight);
}