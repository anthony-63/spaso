#include "logger.h"

#include <stdlib.h>

ss_logger_t* ss_logger_new(char* prefix, char* log_file) {
    ss_logger_t* logger = malloc(sizeof * logger);
    logger->prefix = prefix;
    FILE* tmp = fopen(log_file, "w");
    fputc('\n', tmp);
    fclose(tmp);
    logger->log_file = fopen(log_file, "a");
    return logger;
}

void ss_logger_free(ss_logger_t* logger) {
    fclose(logger->log_file);
    free(logger);
}
