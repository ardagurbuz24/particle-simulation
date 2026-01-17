#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PARTICLE_COUNT 100

typedef struct {
    float x, y;
    float vx, vy;
    int size;
} Particle;


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Particle particles[PARTICLE_COUNT];

int init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 0;
    
    window = SDL_CreateWindow("Particle Simulation", SDL_WINDOWPOS_CENTERED, 
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) return 0;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return 0;

    return 1;
}

void init_particles() {
    srand(time(NULL));
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        particles[i].x = (float)(rand() % SCREEN_WIDTH);
        particles[i].y = (float)(rand() % SCREEN_HEIGHT);
        
        particles[i].vx = (float)(rand() % 401 - 200) / 100.f;
        particles[i].vy = (float)(rand() % 401 - 200) / 100.f;

        particles[i].size = 5;
    }
}

int main(int argc, char* argv[]) {
    if (!init_sdl()) return 1;
    init_particles();

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        for (int i = 0; i < PARTICLE_COUNT; i++) {
            
            particles[i].vy += 0.15f;
            
            particles[i].x += particles[i].vx;
            particles[i].y += particles[i].vy;

            if(particles[i].y + particles[i].size >= SCREEN_HEIGHT) {
                particles[i].y = SCREEN_HEIGHT - particles[i].size;
                particles[i].vy *= -0.8f;
            }

            if (particles[i].x <= 0 || particles[i].x + particles[i].size >= SCREEN_WIDTH) {
                particles[i].vx *= -1;
            }   

            SDL_Rect r = {
                (int)particles[i].x,
                (int)particles[i].y,
                particles[i].size,
                particles[i].size
            };
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &r);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Aim for ~60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}