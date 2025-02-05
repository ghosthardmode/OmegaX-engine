#ifndef CORE_H
    #define CORE_H
#endif

#include <SDL2/SDL.h>

void OM_start(uint16_t win_width, uint16_t win_height, const char *win_tittle, bool use_opengl, bool vsync, bool accel);
float OM_get_deltaTime();
uint16_t OM_get_framerate();
bool OM_get_key_state(uint8_t scancode);
void OM_update();
