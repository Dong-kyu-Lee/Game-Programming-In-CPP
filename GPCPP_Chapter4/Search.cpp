#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>

struct GraphNode
{
	// 각 노드는 인접한 노드의 포인터를 가지고 있다.
	std::vector<GraphNode*> mAdjacent;
};

struct Graph
{
	// 그래프는 노드들을 포함한다.
	std::vector<GraphNode*> mNodes;
};

struct WeightedGraphEdge
{
	// 간선에 어떤 노드가 연결되어 있는가?
	WeightedGraphNode* mFrom;
	WeightedGraphNode* mTo;
	// 간선의 가중치
	float mWeight;
};

struct WeightedGraphNode
{
	// 외부로 향하는 간선들를 저장한다.
	std::vector<WeightedGraphEdge*> mEdges;
};

// Key : 현재 노드, Value : 부모 노드
using NodeToParentMap = std::unordered_map<const GraphNode*, const GraphNode*>;

bool BFS(const Graph& graph, const GraphNode* start,
	const GraphNode* goal, NodeToParentMap& outMap)
{
	// 경로를 찾았는지 확인할 플래그
	bool pathFound = false;
	// 고려해야 할 노드
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
			// 시작 노드를 제외하고, 부모 노드가 nullptr이면 큐에 넣지 않은 노드다.
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