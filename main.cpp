#include <SDL2/SDL.h>
// Use a loader to initialize OpenGL functions; these are usually auto-generated, this one is generated through glLoadGen and manipulated to allow
// SDL2's implementation of GetProcAddress
#include "glload/gl_glcore_3_3.h"


int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *w = SDL_CreateWindow("Hello OpenGL!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WindowFlags::SDL_WINDOW_OPENGL);


    SDL_Event e;

    bool quit = false;
    while (!quit)
    {
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_EventType::SDL_QUIT:
                    quit = true;
                    break;

            }
        }
    }
    SDL_DestroyWindow(w);
    return 0;
}
