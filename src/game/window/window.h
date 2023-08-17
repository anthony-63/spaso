#pragma once

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include "../logger/logger.h"
#include "../shaders/shader_program.h"
#include "../camera/camera.h"

typedef struct {
    int width, height;
    GLFWwindow* gl_window;
    ss_shader_program_t* shader_program;
    ss_camera_t* camera;
    char* title;
} ss_window_t;

ss_window_t* ss_window_new(int width, int height, char* title);
void ss_window_run(ss_window_t* window);
void ss_window_free(ss_window_t* window);