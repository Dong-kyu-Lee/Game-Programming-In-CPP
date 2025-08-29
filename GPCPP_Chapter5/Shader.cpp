#include "Shader.h"
#include "SDL/SDL_log.h"
#include <fstream>
#include <sstream>

Shader::Shader()
	: mShaderProgram(0)
	, mVertexShader(0)
	, mFragmentShader(0)
{

}

Shader::~Shader()
{

}

// �������� ���̴� ������ �̸�, ���̴� Ÿ��, ���̴��� ID�� ������ ���� �Ķ����
bool Shader::CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader)
{
	// ifstream�� ����Ͽ� ���̴� ������ ����
	std::ifstream shaderFile(fileName);
	if (shaderFile.is_open())
	{
		// ��� �ؽ�Ʈ�� �о string�� ����
		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();

		// ������ Ÿ���� ���̴��� ����
		outShader = glCreateShader(shaderType);
		// ���̴� ���ڿ��� �����ϰ� ������ �õ�
		glShaderSource(outShader, 1, &contentsChar, nullptr);
		glCompileShader(outShader);

		if(!IsCompiled(outShader))
		{
			SDL_Log("Failed to compile shader %s", fileName.c_str());
			return false;
		}
	}
	else
	{
		SDL_Log("Shader file not found: %s", fileName.c_str());
		return false;
	}
	return true;
}

bool Shader::IsCompiled(GLuint shader)
{
	GLint status;
	// ������ ���¸� �����Ѵ�.
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if(status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, sizeof(buffer));
		// ������ ���� �޽����� �����´�.
		glGetShaderInfoLog(shader, 511, nullptr, buffer);
		SDL_Log("GLSL compile failed: \n%s", buffer);
		return false;
	}
	return true;
}

bool Shader::IsValidProgram()
{
	GLint status;
	// ���α׷� ���¸� �����Ѵ�.
	glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);
	if(status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, sizeof(buffer));
		// ���α׷� ���� ���� �޽����� �����´�.
		glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
		SDL_Log("GLSL program link failed: \n%s", buffer);
		return false;
	}
	return true;
}

// ���ؽ��� �����׸�Ʈ ���̴��� ���� �̸��� ���ڷ� �ް� �̸� ������ �� �� �����Ű�� �Լ�
bool Shader::Load(const std::string& vertName, const std::string& fragName)
{
	// ���ؽ��� �����׸�Ʈ ���̴� ������
	if(!CompileShader(vertName, GL_VERTEX_SHADER, mVertexShader) ||
	   !CompileShader(fragName, GL_FRAGMENT_SHADER, mFragmentShader))
	{
		return false;
	}
	// ���ؽ�/�����׸�Ʈ ���̴��� ���� �����ϴ� ���̴� ���α׷� ����
	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, mVertexShader);
	glAttachShader(mShaderProgram, mFragmentShader);
	glLinkProgram(mShaderProgram);

	// ���α׷��� ���������� ����ƴ��� ����
	if(!IsValidProgram())
	{
		return false;
	}
	return true;
}

// ���̴� ���α׷��� ���ؽ�/�����׸�Ʈ ���̴��� �����ϴ� �Լ�
void Shader::Unload()
{
	glDeleteProgram(mShaderProgram);
	glDeleteShader(mVertexShader);
	glDeleteShader(mFragmentShader);
}

void Shader::SetActive()
{
	// ���� Ȱ��ȭ�� ���̴� ���α׷��� ����
	glUseProgram(mShaderProgram);
}
