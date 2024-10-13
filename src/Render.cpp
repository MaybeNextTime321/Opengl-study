#include "Render.h"
#include <iostream>


void ClearError()
{
    while (glGetError() != GL_NO_ERROR)
    {
    }
}

bool CheckError(const char* function, const char* file, int line)
{
    while (GLenum Error = glGetError() != GL_NO_ERROR)
    {
        std::cout << "OpenGL Runtime Error (" << Error << ")." << std::endl;
        std::cout << "We call this function " << function << std::endl;
        std::cout << "From this file " << file << " (" << line << ")" << std::endl;

        return false;
    }
    return true;
}


