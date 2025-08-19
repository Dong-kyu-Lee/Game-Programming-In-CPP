#include "VertexArray.h"
#include "GL/glew.h"

VertexArray::VertexArray(const float* verts, unsigned int numVerts, 
	const unsigned int* indices, unsigned int numIndices)
	:mNumVerts(numVerts)
	, mNumIndices(numIndices)
{
	// 버텍스 배열 객체 생성 및 활성화
	glGenVertexArrays(1, &mVertexArray); // 1개의 VAO를 생성하고 mVertexArray에 ID를 저장
	glBindVertexArray(mVertexArray); // VAO를 활성화하여 이후의 버퍼 설정이 이 VAO에 적용되도록 함

	// 버텍스 버퍼 생성
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer); // GL_ARRAY_BUFFER는 버텍스 버퍼를 버퍼로 사용하겠다는 뜻
	glBufferData(GL_ARRAY_BUFFER, numVerts * 5 * sizeof(float), verts, GL_STATIC_DRAW);

	// 인덱스 버퍼 생성
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	// 버텍스 속성 설정
	// (For now, assume one vertex format)
	// Position is 3 floats starting at offset 0
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
}

// 버텍스 버퍼, 인덱스 버퍼, VAO 해제
VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteVertexArrays(1, &mVertexArray);
}

// 현재 활성화된 VAO를 지정하는 함수
void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArray); // 현재 사용할 버텍스 배열을 지정하는 함수
}
