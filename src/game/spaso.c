#include "spaso.h"

#include <stdlib.h>

spaso_t* ss_new(int width, int height, char* title) {
    spaso_t* ss = malloc(sizeof * ss);
    ss->window = ss_window_new(width, height, title);
    return ss;
}

void ss_run(spaso_t* ss) {
    ss_window_run(ss->window);
}

void ss_free(spaso_t* ss) {
    ss_window_free(ss->window);
    free(ss);
}