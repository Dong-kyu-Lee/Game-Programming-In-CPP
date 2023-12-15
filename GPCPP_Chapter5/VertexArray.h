#pragma once
class VertexArray
{
public:
	VertexArray(const float* verts, unsigned int numVerts,
		const unsigned int* indices, unsigned int numIndices);
	~VertexArray();

	// �� VertexArray�� Ȱ��ȭ ��.(�̰��� �׸�)
	void SetActive();

	unsigned int GetNumIndices() const { return mNumIndices; }
	unsigned int GetNumVerts() const { return mNumVerts; }
private:
	// ���ؽ� ���ۿ� �����ϴ� ���ؽ� ��
	unsigned int mNumVerts;
	// �ε��� ���ۿ� �����ϴ� �ε��� ��
	unsigned int mNumIndices;
	// ���ؽ� ������ OpenGL ID
	unsigned int mVertexBuffer;
	// �ε��� ������ OpenGL ID
	unsigned int mIndexBuffer;
	// ���ؽ� �迭 ��ü�� OpenGL ID
	unsigned int mVertexArray;
};

