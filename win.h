#ifndef WIN_H
    #define WIN_H
#endif

#include <SDL2/SDL.h>

void OM_create_win(uint16_t, uint16_t, const char*, bool);
SDL_Window *OM_get_win();
uint16_t OM_get_win_width();
uint16_t OM_get_win_height();
void OM_destroy_win();