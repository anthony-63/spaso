#include <stdio.h>
#include "game/spaso.h"
#define GLFW_DLL

ss_logger_t* g_logger;

int main() {
    g_logger = ss_logger_new("[SPASO]", "data/log.txt");
    spaso_t* spaso = ss_new(1280, 720, "Spaso | Sound Space Written From Scratch");
    ss_run(spaso);
    ss_free(spaso);
    ss_logger_free(g_logger);
}