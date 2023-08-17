#pragma once

#include <cglm/cglm.h>
#include "../shaders/shader_program.h"
#include <GLFW/glfw3.h>

#define CAM_FOV 70.0f
#define CAM_NEAR 0.01f
#define CAM_FAR 1000.0f

typedef struct {
    vec3 position;
    vec3 rotation;
    vec3 up;
    float sensitivity;
    float pitch;
    float yaw;
} ss_camera_t;

ss_camera_t* ss_camera_new(vec3 pos);
void ss_camera_load_matrices(ss_camera_t* camera, int width, int height, ss_shader_program_t* program);
void ss_camera_parse_input(ss_camera_t* camera, GLFWwindow* gl_win, int width, int height);
void ss_camera_set_rotation(ss_camera_t* camera, vec3 rot);