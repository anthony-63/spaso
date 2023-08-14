#include "window.h"

#include <stdlib.h>
#include <stdio.h>

extern ss_logger_t* g_logger;

void err_cb(int err, const char* desc) {
    ss_err(g_logger, "GLFW Threw an error: %s\n", desc);
}

ss_window_t* ss_window_new(int width, int height, const char* title) {
    ss_window_t* window = malloc(sizeof * window);
    
    window->width = width;
    window->height = height;
    window->title = title;
    if(!glfwInit()) {
        ss_err(g_logger, "Failed to initialize GLFW!\n");
        exit(-1);
    }
    ss_log(g_logger, "Initialized GLFW\n");

    glfwSetErrorCallback(err_cb);
    ss_log(g_logger, "Set GLFW Error Callback\n");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    
    window->gl_window = glfwCreateWindow(width, height, title, NULL, NULL);
    if(!window->gl_window) {
        ss_err(g_logger, "Failed to create OpenGL Context or Window\n");
    }
    glfwMakeContextCurrent(window->gl_window);
    ss_log(g_logger, "Created OpenGL Context\n");

    if(gl3wInit()){
        ss_err(g_logger, "Failed to initialize OpenGL\n");
    }

    if(!gl3wIsSupported(4, 0)) {
        ss_err(g_logger, "Invalid OpenGL Version. OpenGL version must be >3.3\n");
    }

    ss_log(g_logger, "OpenGL Intialized:\n\tGL: %s\n\tGLSL:  %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
    glfwSwapInterval(1);

    return window;
}

void ss_window_run(ss_window_t* window) {
    while(!glfwWindowShouldClose(window->gl_window)) {
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window->gl_window);
        glfwPollEvents();
    }
}

void ss_window_free(ss_window_t* window) {
    glfwDestroyWindow(window->gl_window);
    free(window);
}