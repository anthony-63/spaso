#pragma once

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include "../logger/logger.h"

typedef struct {
    int width, height;
    GLFWwindow* gl_window;
    char* title;
    ss_logger_t* logger;
} ss_window_t;

ss_window_t* ss_window_new(int width, int height, const char* title);
void ss_window_run(ss_window_t* window);
void ss_window_free(ss_window_t* window);