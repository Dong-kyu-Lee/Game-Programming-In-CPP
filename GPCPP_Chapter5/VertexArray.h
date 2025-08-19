#pragma once
// 버텍스 배열 객체(Vertex Array Object, VAO)는 OpenGL에서 버텍스 데이터를 관리하는데 사용되는 객체입니다.
// OpenGL의 VAO를 직접 생성하고 ID를 관리함
// VAO에 필요한 버퍼와 속성 설정을 캡슐화함
class VertexArray
{
public:
	VertexArray(const float* verts, unsigned int numVerts,
		const unsigned int* indices, unsigned int numIndices);
	~VertexArray();

	// Activate this vertex array (so we can draw it)
	void SetActive();

	unsigned int GetNumIndices() const { return mNumIndices; }
	unsigned int GetNumVerts() const { return mNumVerts; }
private:
	// 버텍스 버퍼에 존재하는 버텍스의 수
	unsigned int mNumVerts;
	// 인덱스 버퍼에 존재하는 인덱스의 수
	unsigned int mNumIndices;
	// 버텍스 버퍼의 OpenGL ID
	unsigned int mVertexBuffer;
	// 인덱스 버퍼의 OpenGL ID
	unsigned int mIndexBuffer;
	// 버텍스 배열 객체의 OpenGL ID
	unsigned int mVertexArray;
};
