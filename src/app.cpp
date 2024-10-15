#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Render.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

enum EnumShaderType
{
    NONE = -1, VERTEX = 0, FRAGMENT = 1
};

struct ShaderData
{
    std::string VertexShader;
    std::string FragmentShader;
};

ShaderData static ParseShaderFile(std::string FilePath)
{
    std::ifstream File(FilePath);
    std::string line;
    std::stringstream ss[2];
    EnumShaderType currentType = EnumShaderType::NONE;

    while (getline(File, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                currentType = EnumShaderType::VERTEX;
            }
            if (line.find("fragment") != std::string::npos)
            {
                currentType = EnumShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)currentType] << line << std::endl; 
        }
        
    }

    return {ss[0].str(),ss[1].str()};
}

static unsigned int CompileShader(unsigned int shaderType, std::string& shader)
{
    unsigned int shaderID = glCreateShader(shaderType);
    const char* src = shader.c_str();
    GL_DEBUG_CALL(glShaderSource(shaderID, 1, &src, nullptr));
    GL_DEBUG_CALL(glCompileShader(shaderID));

    int result = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);

    if (result != GL_TRUE)
    {
        auto logLength = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
        char* message = (char*)alloca(logLength * sizeof(char));
        glGetShaderInfoLog(shaderID, logLength , &logLength, message);

        std::cout << "Error in " << ((shaderType == GL_VERTEX_SHADER) ? "vertex" : "fragment") << "shader" << std::endl;
        std::cout << message << std::endl;
    }

    return shaderID;
}

static unsigned int CreateShader(std::string& vertexShader, std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GL_DEBUG_CALL(glAttachShader(program, vs));
    GL_DEBUG_CALL(glAttachShader(program, fs));
    GL_DEBUG_CALL(glLinkProgram(program));

    GL_DEBUG_CALL(glDeleteShader(vs));
    GL_DEBUG_CALL(glDeleteShader(fs));


    return program;

}

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


    GL_DEBUG_CALL(glEnableVertexAttribArray(0));
    GL_DEBUG_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

    IndexBuffer ib(indicies, 6);

    ShaderData ShaderParsedData(ParseShaderFile("Content\\Shaders\\Main.shader"));
    

    unsigned int Shader = CreateShader(ShaderParsedData.VertexShader, ShaderParsedData.FragmentShader);
    GL_DEBUG_CALL(glUseProgram(Shader));

    int uniformAddress = glGetUniformLocation(Shader,"u_Color");
    
    GL_DEBUG_CALL(glBindVertexArray(0));
    GL_DEBUG_CALL(glBindBuffer(GL_ARRAY_BUFFER,0));
    GL_DEBUG_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0));

    float delta = 0.0002f;
    float value = 0.0f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GL_DEBUG_CALL(glClear(GL_COLOR_BUFFER_BIT));
        glUniform4f(uniformAddress, value, 0.0, 1.0, 1.0);

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