#include "Render.h"
#include <iostream>
#include "VertexArray.h"
#include "IndexBuffer.h"

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

void Render::Draw(VertexArray& va, IndexBuffer& ib, Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    GL_DEBUG_CALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
