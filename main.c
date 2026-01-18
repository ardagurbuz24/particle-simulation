#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    float x, y;
    float vx, vy;
    int size;
    SDL_Color color;
} Particle;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Particle* particles = NULL;      
int current_particle_count = 0;  
float gravity_value = 0.15f;

void set_particle_count(int new_count) {
    if (new_count <= 0) return;
    
    if (particles != NULL) {
        free(particles);
    }
    
    particles = (Particle*)malloc(new_count * sizeof(Particle));
    current_particle_count = new_count;

    for (int i = 0; i < current_particle_count; i++) {
        particles[i].x = rand() % 800;
        particles[i].y = rand() % 600;
        particles[i].vx = (rand() % 401 - 200) / 100.0f;
        particles[i].vy = (rand() % 401 - 200) / 100.0f;
        particles[i].size = 4;
        particles[i].color = (SDL_Color){rand()%256, rand()%256, rand()%256, 255};
    }
}

void init_all() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return;
    window = SDL_CreateWindow("Particle Engine", SDL_WINDOWPOS_CENTERED, 
                              SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    srand(time(NULL));
    set_particle_count(200); 
}

void trigger_explosion() {
    if (particles == NULL || current_particle_count <= 0) return;

    int centerX = 400; 
    int centerY = 300; 

    for (int i = 0; i < current_particle_count; i++) {
        particles[i].x = (float)centerX;
        particles[i].y = (float)centerY;
        
        particles[i].vx = (float)(rand() % 2001 - 1000) / 100.0f;
        particles[i].vy = (float)(rand() % 2001 - 1000) / 100.0f;
    }
}

void set_gravity(float g) {
    gravity_value = g;
}

void run_frame() {
    if (particles == NULL || current_particle_count <= 0) return;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) exit(0);
    }

    int mx, my;
    if (SDL_GetMouseState(&mx, &my) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        for (int i = 0; i < current_particle_count; i++) {
            particles[i].vx += (mx - particles[i].x) * 0.005f;
            particles[i].vy += (my - particles[i].y) * 0.005f;
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < current_particle_count; i++) {
        particles[i].vy += gravity_value;
        particles[i].vx *= 0.99f; 
        particles[i].vy *= 0.99f;
        
        particles[i].x += particles[i].vx;
        particles[i].y += particles[i].vy;

        if (particles[i].y >= 600) {
            particles[i].y = 600;
            particles[i].vy *= -0.8f;
        }
        
        if (particles[i].x <= 0 || particles[i].x >= 800) {
            particles[i].vx *= -1;
        }

        SDL_Rect r = {(int)particles[i].x, (int)particles[i].y, particles[i].size, particles[i].size};
        SDL_SetRenderDrawColor(renderer, particles[i].color.r, particles[i].color.g, particles[i].color.b, 255);
        SDL_RenderFillRect(renderer, &r);
    }
    SDL_RenderPresent(renderer);
}