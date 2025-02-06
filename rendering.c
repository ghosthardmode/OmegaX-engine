#include "rendering.h"
#include "win.h"
#include <GL/gl.h>

static SDL_Renderer *renderer;
static SDL_GLContext *ctx;
static bool use_opengl_l;
void OM_create_renderer(bool use_opengl, bool vsync, bool accelerated) {
  	use_opengl_l = use_opengl;
    if (!use_opengl) {
        renderer = SDL_CreateRenderer(OM_get_win(), -1, accelerated ? SDL_RENDERER_ACCELERATED : 0);
        if (!renderer) {
            SDL_Log("err: failed to create renderer");
            OM_destroy_win();
            SDL_Quit();
            exit(1);
        }
        SDL_RenderSetVSync(renderer, vsync);
    }else {
    	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        ctx = SDL_GL_CreateContext(OM_get_win());
        if (!ctx) {
            SDL_Log("err: failed to create an opengl context");
            OM_destroy_win();
            SDL_Quit();
            exit(1);
        }
        glViewport(0, 0, OM_get_win_width(), OM_get_win_height());
        glEnable(GL_DEPTH_TEST);
    }
}

SDL_Renderer *OM_get_renderer() {
    return renderer;
}

SDL_GLContext *OM_get_ctx() {
    return ctx;
}

void OM_clear_color(float r, float g, float b, float a){
    if (use_opengl_l) {
        if (r <= 1.f && g <= 1.f && b <= 1.f && a <= 1.f){
            glClearColor(r, g, b, a);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }else {
            glClearColor(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
    } else {
        if (r <= 1 && g <= 1 && b <= 1 && a <= 1) {
            SDL_SetRenderDrawColor(renderer, (uint8_t)(r * 255), (uint8_t)(g * 255), (uint8_t)(b * 255), (uint8_t)(a * 255));
            SDL_RenderClear(renderer);
        }else {
            SDL_SetRenderDrawColor(renderer, (uint8_t)r, (uint8_t)g, (uint8_t)b, (uint8_t)a);
            SDL_RenderClear(renderer);
        }
    }
}

void OM_change_draw_color(float r, float g, float b, float a) {
    if (use_opengl_l) {
        if (r <= 1.f && g <= 1.f && b <= 1.f && a <= 1.f){
            glClearColor(r, g, b, a);
        }else {
            glClearColor(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
        }
    } else {
        if (r <= 1 && g <= 1 && b <= 1 && a <= 1) {
            SDL_SetRenderDrawColor(renderer, (uint8_t)(r * 255), (uint8_t)(g * 255), (uint8_t)(b * 255), (uint8_t)(a * 255));
        }else {
            SDL_SetRenderDrawColor(renderer, (uint8_t)r, (uint8_t)g, (uint8_t)b, (uint8_t)a);
        }
    }
}

void OM_draw_rect(OM_rect_t rect) {
    if (!use_opengl_l) {
        SDL_FRect temp_rect = {rect.x, rect.y, rect.w, rect.h};
        SDL_RenderFillRectF(renderer, &temp_rect);
    }else{
      float x_gl, y_gl, w_gl, h_gl;
      
      if (rect.x > 1.f || rect.y > 1.f || rect.x < -1.f || rect.y < -1.f) {
          x_gl = (2.0f * rect.x / (float)OM_get_win_width()) - 1.0f;
          y_gl = 1.0f - (2.0f * rect.y / (float)OM_get_win_height());
          w_gl = (2.0f * rect.w / (float)OM_get_win_width());
          h_gl = (2.0f * rect.h / (float)OM_get_win_height());
      } else {
          x_gl = rect.x;
          y_gl = rect.y;
          w_gl = rect.w;
          h_gl = rect.h;
      }
      glBegin(GL_QUADS);
          glVertex2f(x_gl - w_gl / 2, y_gl + h_gl / 2);
          glVertex2f(x_gl + w_gl / 2, y_gl + h_gl / 2);
          glVertex2f(x_gl + w_gl / 2, y_gl - h_gl / 2);
          glVertex2f(x_gl - w_gl / 2, y_gl - h_gl / 2);
      glEnd();
      glFlush();
    }
}

void OM_destroy_renderer() {
    SDL_DestroyRenderer(renderer);
    SDL_GL_DeleteContext(ctx);
}
