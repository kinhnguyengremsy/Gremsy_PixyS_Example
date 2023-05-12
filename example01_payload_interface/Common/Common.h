
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "string.h"
#include <cstdio>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

#define USE_DEBUG_STRING 1
/*
         foreground background
black        30         40
red          31         41
green        32         42
yellow       33         43
blue         34         44
magenta      35         45
cyan         36         46
white        37         47
*/

#define LOG_MSG     std::cout << "\033[1;37m" << "[MSG] "
#define LOG_INFO    std::cout << "\033[1;32m" << "[INFO] "
#define LOG_WARN    std::cout << "\033[1;33m" << "[WARN] "
#define LOG_ERROR   std::cout << "\033[1;31m" << "[ERROR] "
#define END_LINE    "\033[1;37m\n\r"

#if (USE_DEBUG_STRING == 1)

#endif

typedef enum __E_Mapping_state
{
    MAPPING_STATE_IDLE = 0x00,
    MAPPING_STATE_CHECK_CAMERA_INIT,
    MAPPING_STATE_CHECK_GIMBAL_INIT,
    MAPPING_STATE_CHECK_CUBE_INIT,
    MAPPING_STATE_READY,
    MAPPING_STATE_START_MISSON,
    MAPPING_STATE_RUNNING_MISSON,
    MAPPING_STATE_END_MISSON,
    MAPPING_STATE_DONE,
    MAPPING_STATE_ERROR,
    MAPPING_TOTAL_STATE

}E_Mapping_state;

typedef struct __ProjectCommon_t
{
    bool allThreadExit;
    E_Mapping_state mappingState;
}ProjectCommon_t;

extern ProjectCommon_t *Common;
