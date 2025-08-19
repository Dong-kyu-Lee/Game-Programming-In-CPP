#include "VertexArray.h"
#include "GL/glew.h"

VertexArray::VertexArray(const float* verts, unsigned int numVerts, 
	const unsigned int* indices, unsigned int numIndices)
	:mNumVerts(numVerts)
	, mNumIndices(numIndices)
{
	// ���ؽ� �迭 ��ü ���� �� Ȱ��ȭ
	glGenVertexArrays(1, &mVertexArray); // 1���� VAO�� �����ϰ� mVertexArray�� ID�� ����
	glBindVertexArray(mVertexArray); // VAO�� Ȱ��ȭ�Ͽ� ������ ���� ������ �� VAO�� ����ǵ��� ��

	// ���ؽ� ���� ����
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer); // GL_ARRAY_BUFFER�� ���ؽ� ���۸� ���۷� ����ϰڴٴ� ��
	glBufferData(GL_ARRAY_BUFFER, numVerts * 5 * sizeof(float), verts, GL_STATIC_DRAW);

	// �ε��� ���� ����
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	// ���ؽ� �Ӽ� ����
	// (For now, assume one vertex format)
	// Position is 3 floats starting at offset 0
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
}

// ���ؽ� ����, �ε��� ����, VAO ����
VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteVertexArrays(1, &mVertexArray);
}

// ���� Ȱ��ȭ�� VAO�� �����ϴ� �Լ�
void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArray); // ���� ����� ���ؽ� �迭�� �����ϴ� �Լ�
}
