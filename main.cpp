#include <SDL2/SDL.h>

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
