#include <iostream>
#include <SDL2/SDL.h>
// Use a loader to initialize OpenGL functions; these are usually auto-generated, this one is generated through glLoadGen and manipulated to allow
// SDL2's implementation of GetProcAddress
#include "glload/gl_glcore_3_3.h"

using namespace std;

// Create an OpenGL context for the current window
SDL_GLContext initGL(SDL_Window *window)
{
    // Set our "wanted" attributes (they might not be what we're going to get!)
    // Request "core" profile (one should never use compat profile ever)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // Request context version 3.3 (core is added in 3.2, sane shader versioning in 3.3)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    // Request RGBA8 drawing surface
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    // Attempt to create context
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context)
    {
        cerr << "Could not create OpenGL context! SDL reports error: " << SDL_GetError();
        return nullptr;
    }
    cout << "Created a new OpenGL context for our application" << endl;
    cout << "Requested configuration: 3.3 core, R8G8B8A8";
    int major, minor, profile;
    int r, g, b, a;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &profile);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
    SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &r);
    SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &g);
    SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &b);
    SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &a);

    cout << "Received configuration: " << major << "." << minor << " "<< (profile == SDL_GL_CONTEXT_PROFILE_CORE ? "core" : "compatibility");
    cout << ", R" << r << "G" << g << "B" << b << "A" << a << endl;

    return context;
}

int main()
{
    // Initialize SDL library for video output (window creation, etc)
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *w = SDL_CreateWindow("Hello OpenGL!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);

    SDL_GLContext context = initGL(w);

    SDL_Event e;

    bool quit = false;

    int brightness = 0;
    int fade = 1;

    while (!quit)
    {
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;

            }
        }
        // Just change brightness on each frame, will not look good, but at least something
        brightness += fade;
        if (brightness == 255 || brightness == 0)
        {
            fade = -fade;
        }
        GLfloat bf = brightness / 255.0;

        glClearColor(bf, bf, bf, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        SDL_GL_SwapWindow(w);
    }
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(w);
    return 0;
}
