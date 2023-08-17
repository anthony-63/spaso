#pragma once

#include <stdio.h>

typedef struct {
    char* prefix;
    FILE* log_file;
} ss_logger_t;

#define ss_log(LOGGER, ...) printf("%s(INFO) ", LOGGER->prefix); \
                            printf(__VA_ARGS__); \
                            fprintf(LOGGER->log_file, "%s(INFO) ", LOGGER->prefix); \
                            fprintf(LOGGER->log_file, __VA_ARGS__); \
                            fflush(LOGGER->log_file);
#define ss_err(LOGGER, ...) printf("%s(ERROR) ", LOGGER->prefix); \
                            printf(__VA_ARGS__); \
                            fprintf(LOGGER->log_file, "%s(ERROR) ", LOGGER->prefix); \
                            fprintf(LOGGER->log_file, __VA_ARGS__); \
                            fflush(LOGGER->log_file); \
                            exit(-1);
#define ss_warn(LOGGER, ...) printf("%s(WARNING) ", "%s(WARNING) ", LOGGER->prefix); \
                            printf(__VA_ARGS__); \
                            fprintf(LOGGER->log_file, LOGGER->prefix); \
                            fprintf(LOGGER->log_file, __VA_ARGS__); \
                            fflush(LOGGER->log_file);

ss_logger_t* ss_logger_new(char* prefix, char* log_file);
void ss_logger_free(ss_logger_t* logger);