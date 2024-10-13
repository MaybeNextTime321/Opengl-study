#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define ASSERT(x) if(!(x)) __debugbreak()

#ifdef DEDUG
#define GL_DEBUG_CALL(x) ClearError();\
    x;\
    ASSERT(CheckError(#x, __FILE__, __LINE__));
#else 
#define GL_DEBUG_CALL(x) x;
#endif


void ClearError();
bool CheckError(const char* function, const char* file, int line);