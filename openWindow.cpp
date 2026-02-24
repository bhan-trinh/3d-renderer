#include <SDL2/SDL.h>
#include <iostream>
#include <iomanip>
#include "framebuffer.h"

#define WIDTH 680
#define HEIGHT 480

#define RED 0xFFFF0000
#define GREEN 0xFF00FF00
#define BLUE 0xFF0000FF

int main(){
    
    // Init my silly video
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        return -1;
    }

    // Creates and set up my silly window
    SDL_Window *window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

    if(!window)
    {
        std::cout << "Failed to create window\n";
        return -1;
    }

    // Creates my silly renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Creates my silly texture
    SDL_Texture *framebuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

    // Creates my silly pixels
    Framebuffer fb(WIDTH, HEIGHT);

    bool keepWindowOpen = true;
    while(keepWindowOpen)
    {
        // Keep track of silly events
        SDL_Event e;
        while(SDL_PollEvent(&e) > 0)
        {
            switch(e.type)
            {
                // If quit
                case SDL_QUIT:
                    keepWindowOpen = false;
                    break;
                
                case SDL_KEYDOWN:
                    // Optional: handle keyboard shortcuts within the application window
                    if (e.key.keysym.sym == SDLK_ESCAPE) {
                        keepWindowOpen = false;
                    }
                    break;
            }
            

            // Draws sily changes on framebuffer
            fb.clear(0xFF000000);

            fb.drawLine(50, 50, 1, 1, RED);
            //  std::cout << "Hexadecimal (formatted): 0x" 
            //   << std::uppercase << std::setfill('0') << std::setw(8) 
            //   << fb.getPixels()[(HEIGHT - 1) * WIDTH + (WIDTH - 1)] << std::endl;

            
            // Difference between updateSurface? Whats the WIDTH for?

            // Updates silly framebuffer
            SDL_UpdateTexture(framebuffer, NULL, fb.getPixels(), WIDTH * sizeof(uint32_t));

            // Renders from silly buffer to screen
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, framebuffer, NULL, NULL);
            SDL_RenderPresent(renderer);
        }
    }

    // ANNIHILATION
    SDL_DestroyTexture(framebuffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

