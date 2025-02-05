#ifndef RENDERING_H
    #define RENDERING_H
#endif

#include <SDL2/SDL.h>
#include <GL/gl.h>

typedef struct OM_Rect {
    float x, y, w, h;
}OM_rect_t;

void OM_create_renderer(bool use_opengl, bool vsync, bool accelerated);
SDL_Renderer *OM_get_renderer();
SDL_GLContext *OM_get_ctx();
void OM_render();
void OM_clear_color(float r, float g, float b, float a);
void OM_change_draw_color(float r, float g, float b, float a);
void OM_draw_rect(OM_rect_t rect);
void OM_destroy_renderer();