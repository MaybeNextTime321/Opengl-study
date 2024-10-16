#include "Shader.h"
#include "Render.h"
#include <sstream>
#include <fstream>
#include <iostream>

Shader::Shader(std::string path)
{
    ShaderData data = ParseShaderFile(path);

    m_RenderID = CreateShader(data.VertexShader, data.FragmentShader);
    GL_DEBUG_CALL(glUseProgram(m_RenderID));
}

Shader::~Shader()
{
    glDeleteShader(m_RenderID);
}

void Shader::Bind()
{
	GL_DEBUG_CALL(glUseProgram(m_RenderID));
}

void Shader::Unbind()
{
	GL_DEBUG_CALL(glUseProgram(0));
}

void Shader::SetUniformValue4f(std::string Varible, float v1, float v2, float v3, float v4)
{
    int uniformAddress = 0;
    if (m_UniformCash.find(Varible) == m_UniformCash.end())
    {
        uniformAddress = GetUniformAddress(Varible);
        m_UniformCash[Varible] = uniformAddress;
    }
    else
    {
        uniformAddress = m_UniformCash[Varible];
    }

    GL_DEBUG_CALL(glUniform4f(uniformAddress, v1, v2, v3, v4));
}


ShaderData Shader::ParseShaderFile(std::string& FilePath)
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

    return { ss[0].str(),ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int shaderType, std::string& shader)
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
        glGetShaderInfoLog(shaderID, logLength, &logLength, message);

        std::cout << "Error in " << ((shaderType == GL_VERTEX_SHADER) ? "vertex" : "fragment") << "shader" << std::endl;
        std::cout << message << std::endl;
    }

    return shaderID;
}

unsigned int Shader::CreateShader(std::string vertexShader, std::string fragmentShader)
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

int Shader::GetUniformAddress(std::string& VaribleName)
{
    int value = GL_DEBUG_CALL(glGetUniformLocation(m_RenderID, VaribleName.c_str()));
    if (value == -1)
    {
        std::cout << "Uniform Varible: " + VaribleName + " is not found" << std::endl;
    }
    return value;
}