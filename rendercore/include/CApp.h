#ifndef CAPP_H
#define CAPP_H
#define SDL_MAIN_HANDLED
#include<SDL.h>
class AppWindow
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Event event;
    SDL_Rect rect;
    int windowHeight;
    int windowWidth;
    /* data */
public:
    AppWindow(/* args */);
    ~AppWindow();
    void createWindow(int with , int height);
    
};
#endif