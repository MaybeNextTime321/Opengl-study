#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "Render.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Maybe Triangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error!! " << std::endl;
    }
    else
    {
        fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    }
    float position[] =
    {
        -0.5f, 0.5f,
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f,0.5f
    };

    unsigned int indicies[] =
    {
        0,1,2,
        0,2,3
    };

    VertexArray va;
    VertexBuffer vb(position, 8*sizeof(float));
    VertexBufferLayout layout;

    layout.PushBack<float>(2);
    va.AddBuffer(vb,layout);

    IndexBuffer ib(indicies, 6);

    Shader shader("Content\\Shaders\\Main.shader");
    
    va.Unbind();
    GL_DEBUG_CALL(glBindBuffer(GL_ARRAY_BUFFER,0));
    GL_DEBUG_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0));

    float delta = 0.0002f;
    float value = 0.0f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GL_DEBUG_CALL(glClear(GL_COLOR_BUFFER_BIT));
        shader.SetUniformValue4f("u_Color", value, 0.0, 1.0, 1.0);
        va.Bind();

        GL_DEBUG_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        /* Swap front and back buffers */
        GL_DEBUG_CALL(glfwSwapBuffers(window));

        if (value >= 1)
            delta = -0.0002f;
        if (value <= 0)
            delta = 0.0002;

        value += delta;

        /* Poll for and process events */
        GL_DEBUG_CALL(glfwPollEvents());
    }

    glfwTerminate();
    return 0;
}