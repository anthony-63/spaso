#pragma once

#include "window/window.h"
#include "logger/logger.h"

typedef struct {
    ss_window_t* window;
} spaso_t;

spaso_t* ss_new(int width, int height, const char* title);
void ss_run(spaso_t* ss);
void ss_free(spaso_t* ss);