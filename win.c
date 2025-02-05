#include "win.h"

SDL_Window *window;
uint16_t width_l;
uint16_t height_l;
void OM_create_win(uint16_t width, uint16_t height, const char *tittle, bool use_opengl) {
    width_l = width;
    height_l = height;
    window = SDL_CreateWindow(tittle, SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      width, height,
                                      use_opengl ? SDL_WINDOW_OPENGL: 0);

    if (!window) {
        SDL_Log("err: failed to create a window");
        SDL_Quit();
        exit(1);
    }
    SDL_ShowWindow(window);
}

SDL_Window *OM_get_win() {
    return window;
}

uint16_t OM_get_win_width() {
    return width_l;
}

uint16_t OM_get_win_height() {
    return height_l;
}

void OM_destroy_win() {
    SDL_DestroyWindow(window);
}