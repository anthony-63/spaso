#include "camera.h"

#include <stdlib.h>

#include "../logger/logger.h"

extern ss_logger_t* g_logger;

ss_camera_t* ss_camera_new(vec3 pos) {
    ss_camera_t* cam = malloc(sizeof * cam);
    cam->position[0] = pos[0];
    cam->position[1] = pos[1];
    cam->position[2] = pos[2];
    cam->rotation[0] = 0.0;
    cam->rotation[1] = 180.0;
    cam->rotation[2] = 0.0;
    cam->up[0] = 0.0;
    cam->up[1] = 1.0;
    cam->up[2] = 0.0;
    cam->sensitivity = 0.1;
    cam->pitch = 0.0;
    cam->yaw = 0.0;
    ss_log(g_logger, "Created Camera {sens: %f, pos: {x: %f, y: %f, z: %f}}\n", cam->sensitivity, pos[0], pos[1], pos[2]);
    return cam;
}

void ss_camera_load_matrices(ss_camera_t* camera, int width, int height, ss_shader_program_t* program){
    mat4 view = GLM_MAT4_IDENTITY_INIT;
    mat4 proj = GLM_MAT4_IDENTITY_INIT;
    vec3 center;
    glm_vec3_add(camera->position, camera->rotation, center);
    glm_lookat(camera->position, center, camera->up, view);
    glm_perspective(glm_rad(CAM_FOV), (float)(width / height), CAM_NEAR,CAM_FAR, proj);
    ss_shader_program_load_mat4(program, "view", view[0]);
    ss_shader_program_load_mat4(program, "proj", proj[0]);
}

void ss_camera_set_rotation(ss_camera_t* camera, vec3 rot) {
    camera->rotation[0] = rot[0];
    camera->rotation[1] = rot[1];
    camera->rotation[2] = rot[2];
}