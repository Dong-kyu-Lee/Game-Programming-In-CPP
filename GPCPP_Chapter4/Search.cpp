#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>

struct GraphNode
{
	// �� ���� ������ ����� �����͸� ������ �ִ�.
	std::vector<GraphNode*> mAdjacent;
};

struct Graph
{
	// �׷����� ������ �����Ѵ�.
	std::vector<GraphNode*> mNodes;
};

struct WeightedGraphEdge
{
	// ������ � ��尡 ����Ǿ� �ִ°�?
	WeightedGraphNode* mFrom;
	WeightedGraphNode* mTo;
	// ������ ����ġ
	float mWeight;
};

struct WeightedGraphNode
{
	// �ܺη� ���ϴ� �����鸦 �����Ѵ�.
	std::vector<WeightedGraphEdge*> mEdges;
};

// Key : ���� ���, Value : �θ� ���
using NodeToParentMap = std::unordered_map<const GraphNode*, const GraphNode*>;

bool BFS(const Graph& graph, const GraphNode* start,
	const GraphNode* goal, NodeToParentMap& outMap)
{
	// ��θ� ã�Ҵ��� Ȯ���� �÷���
	bool pathFound = false;
	// ����ؾ� �� ���
	std::queue<GraphNode*> q;
	q.emplace(start);

	while (!q.empty())
	{
		const GraphNode* current = q.front();
		q.pop();

		if (current == goal)
		{
			pathFound = true;
			break;
		}

		for (const GraphNode* node : current->mAdjacent)
		{
			// ���� ��带 �����ϰ�, �θ� ��尡 nullptr�̸� ť�� ���� ���� ����.
			const GraphNode* parent = outMap[node];
			if (parent == nullptr && node != start)
			{
				outMap[node] = parent;
				q.emplace(node);
			}
		}
	}

	return pathFound;
}