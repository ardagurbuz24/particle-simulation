#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PARTICLE_COUNT 200

typedef struct {
    float x, y;
    float vx, vy;
    int size;
    SDL_Color color;
} Particle;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Particle particles[PARTICLE_COUNT];
float gravity_value = 0.15f; 

void init_all() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return;
    
    window = SDL_CreateWindow("Particle Engine", SDL_WINDOWPOS_CENTERED, 
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    srand(time(NULL));
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        particles[i].x = rand() % SCREEN_WIDTH;
        particles[i].y = rand() % SCREEN_HEIGHT;
        particles[i].vx = (rand() % 401 - 200) / 100.0f;
        particles[i].vy = (rand() % 401 - 200) / 100.0f;
        particles[i].size = 4;
        particles[i].color.r = rand() % 256;
        particles[i].color.g = rand() % 256;
        particles[i].color.b = rand() % 256;
        particles[i].color.a = 255;
    }
}

void set_gravity(float g) {
    gravity_value = g;
}

void trigger_explosion() {
    int centerX = SCREEN_WIDTH / 2;
    int centerY = SCREEN_HEIGHT / 2;
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        particles[i].x = centerX;
        particles[i].y = centerY;
        particles[i].vx = (rand() % 2001 - 1000) / 100.0f;
        particles[i].vy = (rand() % 2001 - 1000) / 100.0f;
    }
}

void run_frame() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) exit(0);
        
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            int mx, my;
            SDL_GetMouseState(&mx, &my);
            for (int i = 0; i < PARTICLE_COUNT; i++) {
                particles[i].vx += (mx - particles[i].x) * 0.005f;
                particles[i].vy += (my - particles[i].y) * 0.005f;
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < PARTICLE_COUNT; i++) {
        particles[i].vy += gravity_value; 
        particles[i].vx *= 0.99f; 
        particles[i].vy *= 0.99f;
        
        particles[i].x += particles[i].vx;
        particles[i].y += particles[i].vy;

        if (particles[i].y + particles[i].size >= SCREEN_HEIGHT) {
            particles[i].y = SCREEN_HEIGHT - particles[i].size;
            particles[i].vy *= -0.8f;
        }
        if (particles[i].x <= 0 || particles[i].x + particles[i].size >= SCREEN_WIDTH) {
            particles[i].vx *= -1;
        }

        SDL_Rect r = {(int)particles[i].x, (int)particles[i].y, particles[i].size, particles[i].size};
        SDL_SetRenderDrawColor(renderer, particles[i].color.r, particles[i].color.g, particles[i].color.b, 255);
        SDL_RenderFillRect(renderer, &r);
    }

    SDL_RenderPresent(renderer);
}