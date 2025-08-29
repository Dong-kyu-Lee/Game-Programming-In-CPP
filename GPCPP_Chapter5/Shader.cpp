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

// 컴파일할 셰이더 파일의 이름, 셰이더 타입, 셰이더의 ID를 저장할 참조 파라미터
bool Shader::CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader)
{
	// ifstream을 사용하여 셰이더 파일을 읽음
	std::ifstream shaderFile(fileName);
	if (shaderFile.is_open())
	{
		// 모든 텍스트를 읽어서 string에 저장
		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();

		// 지정된 타입의 셰이더를 생성
		outShader = glCreateShader(shaderType);
		// 셰이더 문자열을 설정하고 컴파일 시도
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
	// 컴파일 상태를 질의한다.
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if(status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, sizeof(buffer));
		// 컴파일 에러 메시지를 가져온다.
		glGetShaderInfoLog(shader, 511, nullptr, buffer);
		SDL_Log("GLSL compile failed: \n%s", buffer);
		return false;
	}
	return true;
}

bool Shader::IsValidProgram()
{
	GLint status;
	// 프로그램 상태를 질의한다.
	glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);
	if(status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, sizeof(buffer));
		// 프로그램 연결 에러 메시지를 가져온다.
		glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
		SDL_Log("GLSL program link failed: \n%s", buffer);
		return false;
	}
	return true;
}

// 버텍스와 프래그먼트 셰이더의 파일 이름을 인자로 받고 이를 컴파일 한 후 연결시키는 함수
bool Shader::Load(const std::string& vertName, const std::string& fragName)
{
	// 버텍스와 프래그먼트 셰이더 컴파일
	if(!CompileShader(vertName, GL_VERTEX_SHADER, mVertexShader) ||
	   !CompileShader(fragName, GL_FRAGMENT_SHADER, mFragmentShader))
	{
		return false;
	}
	// 버텍스/프래그먼트 셰이더를 서로 연결하는 셰이더 프로그램 생성
	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, mVertexShader);
	glAttachShader(mShaderProgram, mFragmentShader);
	glLinkProgram(mShaderProgram);

	// 프로그램이 성공적으로 연결됐는지 검증
	if(!IsValidProgram())
	{
		return false;
	}
	return true;
}

// 셰이더 프로그램과 버텍스/프래그먼트 셰이더를 삭제하는 함수
void Shader::Unload()
{
	glDeleteProgram(mShaderProgram);
	glDeleteShader(mVertexShader);
	glDeleteShader(mFragmentShader);
}

void Shader::SetActive()
{
	// 현재 활성화된 셰이더 프로그램을 지정
	glUseProgram(mShaderProgram);
}
