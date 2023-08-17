#include "shader_program.h"

#include <stdlib.h>
#include "../logger/logger.h"

extern ss_logger_t* g_logger;

ss_shader_program_t* ss_shader_program_new(ss_shader_t* vert, ss_shader_t* frag) {
    ss_shader_program_t* prog = malloc(sizeof * prog);
    prog->id = glCreateProgram();
    
    glAttachShader(prog->id, vert->id);
    glAttachShader(prog->id, frag->id);

    ss_log(g_logger, "Linking program id: %d\n", prog->id);

    glLinkProgram(prog->id);

    unsigned int linked;
    char link_log[1024];
    glGetProgramiv(prog->id, GL_LINK_STATUS, &linked);
    if(!linked) {
        glGetProgramInfoLog(prog->id, 1024, NULL, link_log);
        ss_err(g_logger, "Failed to compile program id '%d' with error message: %s", prog->id, link_log);
    }

    ss_log(g_logger, "Linked program id: %d, status: %d\n", prog->id, linked);

    glDeleteShader(vert->id);
    glDeleteShader(frag->id);

    return prog;
}

void ss_shader_program_use(ss_shader_program_t* shader_program) {
    glUseProgram(shader_program->id);
}

void ss_shader_program_free(ss_shader_program_t* shader_program) {
    glDeleteProgram(shader_program->id);
}

void ss_shader_program_load_mat4(ss_shader_program_t* shader_program, char* uniform_name, GLfloat* value) {
    int uni_loc = glGetUniformLocation(shader_program->id, uniform_name);
    glUniformMatrix4fv(uni_loc, 1, GL_FALSE, value);
}