#include "shader.h"

#include <stdlib.h>
#include <GL/gl3w.h>
#include <stdio.h>
#include "../logger/logger.h"

extern ss_logger_t* g_logger;

ss_shader_t* ss_shader_load(const char* path, unsigned int type) {
    ss_shader_t* shader = malloc(sizeof * shader);
    shader->id = glCreateShader(type);
    
    FILE* file = fopen(path, "r");
    int fsize;
    fseek(file, 0, SEEK_END);
    fsize = ftell(file);
    fseek(file, 0, 0);

    char* file_contents = malloc((fsize + 1) * sizeof(char));
    memset(file_contents, 0, (fsize * sizeof(char)));
    fread(file_contents, fsize, 1, file);
    file_contents[fsize] = '\0';

    fclose(file);

    ss_log(g_logger, "Loading shader source: %s\n", path);

    glShaderSource(shader->id, 1, (const char* const*)&file_contents, NULL);

    ss_log(g_logger, "Compiling shader: %s\n", path);
    glCompileShader(shader->id);

    int compiled;
    char compile_log[1024];
    glGetShaderiv(shader->id, GL_COMPILE_STATUS, &compiled);
    if(!compiled) {
        glGetShaderInfoLog(shader->id, 1024, NULL, compile_log);
        ss_err(g_logger, "Failed to compile shader '%s' with error message: %s", path, compile_log);
    }

    ss_log(g_logger, "Compiled shader: %s\n", path);

    free(file_contents);

    ss_log(g_logger, "Freed shader tmp\n");

    return shader;
}