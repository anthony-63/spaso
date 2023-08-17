#pragma once

typedef struct {
    unsigned int id;
} ss_shader_t;

ss_shader_t* ss_shader_load(const char* path, unsigned int type);
