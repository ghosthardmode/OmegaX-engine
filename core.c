#include "core.h"
#include "win.h"
#include "rendering.h"

static bool use_opengl_l;
uint64_t last = 0;
float delta = 0.f;

void main_loop();
void OM_start(uint16_t win_width, uint16_t win_height, const char* win_tittle, bool use_opengl, bool vsync, bool accel){
    use_opengl_l = use_opengl;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("err: SDL failed to initialize");
        SDL_Quit();
        exit(1);
    }
    OM_create_win(win_width, win_height, win_tittle, use_opengl);
    OM_create_renderer(use_opengl, vsync, accel);
    main_loop();
}

void main_loop() {
    SDL_Renderer *renderer = OM_get_renderer();
    SDL_Window *win = OM_get_win();
    SDL_Event ev;
    while (true) {
        uint64_t now = SDL_GetPerformanceCounter();
        delta = (float)(now - last) / (float)SDL_GetPerformanceFrequency();
        last = now;
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) {
                OM_destroy_win();
                OM_destroy_renderer();
                SDL_Quit();
                exit(0);
            }
        }
        OM_clear_color(0, 0, 0, 0);
        OM_update();
        OM_render();
        if (!use_opengl_l)
            SDL_RenderPresent(renderer);
        else
            SDL_GL_SwapWindow(win);
    }
}

float OM_get_deltaTime() {
    return delta;
}

uint16_t OM_get_framerate() {
    return (uint16_t)(1.f / delta);
}

bool OM_get_key_state(uint8_t scancode) {
    const uint8_t *keys = (uint8_t*)SDL_GetKeyboardState(nullptr);
    return keys[scancode];
}