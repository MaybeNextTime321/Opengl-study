#pragma once

#include <string>
#include <unordered_map>

enum EnumShaderType
{
	NONE = -1, VERTEX = 0, FRAGMENT = 1
};

struct ShaderData
{
	std::string VertexShader;
	std::string FragmentShader;
};

class Shader
{
private:
	unsigned int m_RenderID;
	std::unordered_map <std::string, int> m_UniformCash;

public:
	Shader(std::string path);
	~Shader();
	void Bind();
	void Unbind();
	void SetUniformValue4f(std::string Varible, float v1, float v2, float v3, float v4);

private:
	ShaderData ParseShaderFile(std::string& FilePath);
	unsigned int CompileShader(unsigned int shaderType, std::string& shader);
	unsigned int CreateShader(std::string vertexShader, std::string fragmentShader);
	int GetUniformAddress(std::string& VaribleName);

};