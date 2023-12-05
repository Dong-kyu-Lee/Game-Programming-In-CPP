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

struct WeightedEdge
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
	std::vector<WeightedEdge*> mEdges;
};

struct WeightedGraph
{
	std::vector<WeightedGraphNode*> mNodes;
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

// 노드의 추가 정보
struct GBFSScratch
{
	const WeightedEdge* mParentEdge = nullptr;
	float mHeuristic = 0.0f;
	bool mInOpenSet = false;
	bool mInClosedSet = false;
};

// 노드에 매핑된 추가 정보
using GBFSMap = std::unordered_map<const WeightedGraphNode*, GBFSScratch>;

float ComputeHeuristic(const WeightedGraphNode* start, const WeightedGraphNode* goal)
{
	return 0.0f;
}

bool GBFS(const WeightedGraph& g, const WeightedGraphNode* start,
	const WeightedGraphNode* goal, GBFSMap& outMap)
{
	std::vector<const WeightedGraphNode*> openSet;
	// 시작 노드를 현재 노드로 설정하고 닫힌 집합에 있다고 마킹한다.
	const WeightedGraphNode* current = start;
	outMap[current].mInClosedSet = true;
	do
	{
		// 열린 집합에 인접 노드를 추가한다.
		for (const WeightedEdge* edge : current->mEdges)
		{
			GBFSScratch& data = outMap[edge->mTo];
			// 닫힌 집합에 있는 노드가 아니라면 테스트 필요
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

		// 열린 집합에서 가장 낮은 비용을 가진 노드를 찾는다.
		auto iter = std::min_element(openSet.begin(), openSet.end(),
			[&outMap](const WeightedGraphNode* a, const WeightedGraphNode* b)
			{
				return outMap[a].mHeuristic < outMap[b].mHeuristic;
			});
		// 현재 노드로 설정하고 열린 집합에서 닫힌 집합으로 이동시킨다.
		current = *iter;
		openSet.erase(iter);
		outMap[current].mInClosedSet = true;
		outMap[current].mInOpenSet = false;
	} while (current != goal);
	// 경로를 찾았는가?
	return (current == goal) ? true : false;
}

struct AStarScratch
{
	const WeightedEdge* mParentEdge = nullptr;
	float mHeuristic = 0.0f;
	float mActualFromStart = 0.0f;
	bool mInOpenSet = false;
	bool mInClosedSet = false;
};

using AStarMap = std::unordered_map<const WeightedGraphNode*, AStarScratch>;

bool AStar(const WeightedGraph& g, const WeightedGraphNode* start,
	const WeightedGraphNode* goal, AStarMap& outMap)
{
	std::vector<const WeightedGraphNode*> openSet;

	const WeightedGraphNode* current = start;
	outMap[current].mInClosedSet = true;

	do
	{
		for (const WeightedEdge* edge : current->mEdges)
		{
			const WeightedGraphNode* neighbor = edge->mTo;
			// 이 노드의 추가 데이터를 얻는다.
			AStarScratch& data = outMap[neighbor];
			// 닫힌 집합이 없는지를 확인
			if (!data.mInClosedSet)
			{
				if (!data.mInOpenSet)
				{
					data.mParentEdge = edge;
					data.mHeuristic = ComputeHeuristic(neighbor, goal);
					// 실제 비용은 부모의 실제 비용 + 부모에서 자신으로 이동하는 간선의 가중치다.
					data.mActualFromStart = outMap[current].mActualFromStart +
						edge->mWeight;
					data.mInOpenSet = true;
					openSet.emplace_back(neighbor);
				}
				else
				{
					// 현재 노드가 부모 노드가 될지를 판단하고자 새로운 실제 비용 계산.
					float newG = outMap[current].mActualFromStart + edge->mWeight;
					if (newG < data.mActualFromStart)
					{
						// 현재 노드가 이 노드의 부모 노드로 채택됨.
						data.mParentEdge = edge;
						data.mActualFromStart = newG;
					}
				}
			}
		}

		if (openSet.empty()) break;

		auto iter = std::min_element(openSet.begin(), openSet.end(),
			[&outMap](const WeightedGraphNode* a, const WeightedGraphNode* b)
			{
				// f(x) 계산
				float fOfA = outMap[a].mActualFromStart + outMap[a].mHeuristic;
				float fOfB = outMap[b].mActualFromStart + outMap[b].mHeuristic;
				return fOfA < fOfB;
			});
		current = *iter;
		openSet.erase(iter);
		outMap[*iter].mInClosedSet = true;
		outMap[*iter].mInOpenSet = true;
	} while (current != goal);

	return (current == goal) ? true : false;
}