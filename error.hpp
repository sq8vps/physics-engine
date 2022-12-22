#pragma once

typedef enum
{
    OK,
    ERR_BAD_COR,

} Error_t;

#define EXIT_OK 0x000
#define EXIT_GLFW_INIT_FAIL 0x100
#define EXIT_GLFW_CREATE_WINDOW_FAIL 0x101
#define EXIT_GLAD_INIT_FAIL 0x200