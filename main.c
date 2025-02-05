#include "OmegaX.h"

int main(void) {
    OM_start(840, 540, "engine test", false, true, true);
    return 0;
}

void OM_update() {
}

void OM_render() {
    OM_clear_color(0.3f, 0.4f, 0.5f, 1.f);
}