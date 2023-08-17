#include "window.h"

#include <stdlib.h>
#include <stdio.h>
#include "../shaders/shader.h"
#include <cglm/cglm.h>
#include <cglm/mat4.h>

extern ss_logger_t* g_logger;

int first_mouse = 0;
int last_mouse_x = 0;
int last_mouse_y = 0;

void err_cb(int err, const char* desc) {
    ss_err(g_logger, "GLFW Threw an error: %s\n", desc);
}

void window_resize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_move(GLFWwindow* window, double x, double y) {
    if(first_mouse) {
        last_mouse_x = x;
        last_mouse_y = y;
        first_mouse = 0;
    }

    float xoff = x - last_mouse_x;
    float yoff = last_mouse_y - y;
    last_mouse_x = x;
    last_mouse_y = y;

    ss_window_t* sswindow = (ss_window_t*)glfwGetWindowUserPointer(window);
    ss_camera_t* cam = sswindow->camera;
    xoff *= cam->sensitivity;
    yoff *= cam->sensitivity;

    cam->yaw += xoff;
    cam->pitch += yoff;

    if(cam->pitch > 89.0f) cam->pitch = 89.0f;
    if(cam->pitch < -89.0f) cam->pitch = -89.0f;

    vec3 direction;
    direction[0] = cos(glm_rad(cam->yaw)) * cos(glm_rad(cam->pitch));
    direction[1] = sin(glm_rad(cam->pitch));
    direction[2] = sin(glm_rad(cam->yaw)) * cos(glm_rad(cam->pitch));
    glm_normalize(direction);
    cam->rotation[0] = direction[0];
    cam->rotation[1] = direction[1];
    cam->rotation[2] = direction[2];
    
}

float vert[] = {
    -0.5, -0.5, 0.0,
    0.5, -0.5, 0.0,
    0.0, 0.5, 0.0,
};

unsigned int vbo;
unsigned int vao;

ss_window_t* ss_window_new(int width, int height, char* title) {
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
    glfwSetWindowUserPointer(window->gl_window, (void*)window);

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

    ss_log(g_logger, "OpenGL Initialized:\n\tGL: %s\n\tGLSL:  %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
    glfwSwapInterval(1);

    glfwSetWindowSizeCallback(window->gl_window, window_resize);
    glfwSetCursorPosCallback(window->gl_window, mouse_move);

    glGenBuffers(1, &vbo);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(vao);

    ss_shader_t* vert = ss_shader_load("data/shaders/main.vert", GL_VERTEX_SHADER);
    ss_shader_t* frag = ss_shader_load("data/shaders/main.frag", GL_FRAGMENT_SHADER);

    window->shader_program = ss_shader_program_new(vert, frag);
    window->camera = ss_camera_new((vec3){0.0, 0.0, -3.5});

    ss_camera_set_rotation(window->camera, (vec3){0.0, 180.0, 0.0});
    return window;
}

void draw(ss_window_t* window) {
    glClear(GL_COLOR_BUFFER_BIT);
    ss_shader_program_use(window->shader_program);

    mat4 model = GLM_MAT4_IDENTITY_INIT;

    ss_shader_program_load_mat4(window->shader_program, "model", model[0]);
    ss_camera_load_matrices(window->camera, window->width, window->height, window->shader_program);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void update(ss_window_t* window) {
}

void ss_window_run(ss_window_t* window) {
    glfwSetInputMode(window->gl_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    while(!glfwWindowShouldClose(window->gl_window)) {
        glClearColor(0.0, 0.0, 0.0, 0.0);

        update(window);
        draw(window);

        glfwSwapBuffers(window->gl_window);
        glfwPollEvents();
    }
}

void ss_window_free(ss_window_t* window) {
    ss_shader_program_free(window->shader_program);
    glfwDestroyWindow(window->gl_window);
    free(window);
}