#pragma once
#include <string>
#include <GL/glew.h>

class Shader
{
public:
	Shader();
	~Shader();
	// 주어진 이름으로 버텍스/프래그먼트 셰이더 로드
	bool Load(const std::string& vertName, const std::string& fragName);
	void Unload();
	// 이 셰이더를 활성화된 셰이더 프로그램으로 설정
	void SetActive();
private:
	// 지정된 셰이더를 컴파일
	bool CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader);
	// 셰이더가 성공적으로 컴파일 되었는지 확인
	bool IsCompiled(GLuint shader);
	// 버텍스/프래그먼트 프로그램이 연결됐는지 확인
	bool IsValidProgram();
	// 셰이더 오브젝트 ID 저장
	GLuint mVertexShader;
	GLuint mFragmentShader;
	GLuint mShaderProgram; // 셰이더 프로그램 ID
};

