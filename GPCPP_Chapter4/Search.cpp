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

struct WeightedEdge
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
	std::vector<WeightedEdge*> mEdges;
};

struct WeightedGraph
{
	std::vector<WeightedGraphNode*> mNodes;
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

// ����� �߰� ����
struct GBFSScratch
{
	const WeightedEdge* mParentEdge = nullptr;
	float mHeuristic = 0.0f;
	bool mInOpenSet = false;
	bool mInClosedSet = false;
};

// ��忡 ���ε� �߰� ����
using GBFSMap = std::unordered_map<const WeightedGraphNode*, GBFSScratch>;

float ComputeHeuristic(const WeightedGraphNode* start, const WeightedGraphNode* goal)
{
	return 0.0f;
}

bool GBFS(const WeightedGraph& g, const WeightedGraphNode* start,
	const WeightedGraphNode* goal, GBFSMap& outMap)
{
	std::vector<const WeightedGraphNode*> openSet;
	// ���� ��带 ���� ���� �����ϰ� ���� ���տ� �ִٰ� ��ŷ�Ѵ�.
	const WeightedGraphNode* current = start;
	outMap[current].mInClosedSet = true;
	do
	{
		// ���� ���տ� ���� ��带 �߰��Ѵ�.
		for (const WeightedEdge* edge : current->mEdges)
		{
			GBFSScratch& data = outMap[edge->mTo];
			// ���� ���տ� �ִ� ��尡 �ƴ϶�� �׽�Ʈ �ʿ�
			if (!data.mInClosedSet)
			{
				data.mParentEdge = edge;
				if (!data.mInOpenSet)
				{
					data.mHeuristic = ComputeHeuristic(edge->mTo, goal);
					data.mInOpenSet = true;
					openSet.emplace_back(edge->mTo);
				}
			}
		}

		if (openSet.empty()) break;

		// ���� ���տ��� ���� ���� ����� ���� ��带 ã�´�.
		auto iter = std::min_element(openSet.begin(), openSet.end(),
			[&outMap](const WeightedGraphNode* a, const WeightedGraphNode* b)
			{
				return outMap[a].mHeuristic < outMap[b].mHeuristic;
			});
		// ���� ���� �����ϰ� ���� ���տ��� ���� �������� �̵���Ų��.
		current = *iter;
		openSet.erase(iter);
		outMap[current].mInClosedSet = true;
		outMap[current].mInOpenSet = false;
	} while (current != goal);
	// ��θ� ã�Ҵ°�?
	return (current == goal) ? true : false;
}