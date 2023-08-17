#pragma once

#include <GL/gl3w.h>

#include "shader.h"

typedef struct {
    unsigned int id;
} ss_shader_program_t;

ss_shader_program_t* ss_shader_program_new(ss_shader_t* vert, ss_shader_t* frag);
void ss_shader_program_use(ss_shader_program_t* shader_program);
void ss_shader_program_free(ss_shader_program_t* shader_program);

void ss_shader_program_load_mat4(ss_shader_program_t* shader_program, char* uniform_name, GLfloat* value);