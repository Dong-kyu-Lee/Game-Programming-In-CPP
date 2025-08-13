
## GBFS(Greedy Best-First Search)

- GBFS가 최적의 경로를 보장해주지는 않지만, GBFS는 `A*`가 되기 위해 몇 가지만 수정하면 되므로 이해하는데 도움이 된다.
- `A*`알고리즘은 휴리스틱이 허용 가능하다면 최단 경로를 보장한다.
- GBFS는 경로를 찾는 과정에서 다음 노드를 선정할 때 노드들의 휴리스틱 값을 이용해 노드를 선택한다.
- BFS에서는 방문하지 않은 노드 중, Queue에서 가장 앞에 있는 노드를 선택했다면, GBFS에서는 노드들 중에서 휴리스틱 값을 비교해 가장 작은/큰 노드를 선택하는 식으로 구현한다.

- GBFS에서는 탐색을 진행할 때, 열린 집합(Open set)과 닫힌 집합(Closed set)을 사용한다.
- 열린 집합에는 평가를 위한 노드가 포함된다. (BFS의 큐와 비슷함)
- 닫힌 집합에는 노드를 평가하기 위해 선택된 노드가 들어간다.
- 아래 구조체에는 알고리즘에서 노드가 가져야 하는 데이터들을 가지고 있는 구조체이다.
```cpp
struct GBFSScratch{
	const WegithedEdge* mParentEdge = nullptr;
	float mHeuristic = 0.0f; // 휴리스틱 값
	bool mInOpenSet = false;
	bool mInClosedSet = false;
};
```

- 전체 코드
```cpp
using GBFSMap = std::unordered_map<const WeightedGraphNode*, GBFSScratch>;

bool GBFS(cibst WeightedGraph& g, const WeightedGraphNode* start, const WeightedGraphNode* goal, GBFSMap& outMap)
{
	std::vector<const WeightedGraphNode*> openSet;
	// 시작 노드를 현재 노드로 설정하고 닫힌 집합에 있다고 마킹한다.
	const WeightedGraphNode* current = start;
	outMap[current].mInClosedSet = true;
	do
	{
		// 열린 집합으로 인접 노드를 추가한다.
		for (const WeightedEdge* edge : current->mEdges)
		{
			// 이 노드의 추가 데이터를 얻는다.
			GBFSScratch& data = outMap[edge->mTo];
			// 닫힌 집합에 있는 노드가 아니라면 테스트 필요
			if (!data.mInClosedSet)
			{
				// 인접 노드의 부모 Edge를 설정한다.
				data.mParentEdge = edge;
				if (!data.InOpenSet)
				{
					// 이 노드의 휴리스틱 값을 계산한다. 그리고 열린 집합에 추가한다.
					data.mHeuristic = ComputeHeuristic(edge->mTo, goal);
					data.mInOpenSet = true;
					openSet.emplace_back(edge->mTo);
				}
			}
		}
	if (openSet.empty()) break;
	
	// 열린 집합에서 가장 낮은 비용을 가진 노드를 찾는다.
	auto iter = std::min_element(open.begin(), openSet.end(), [&outMap](const WeightedGraphNode* a, const WeightedGraphNode* b){
	return outMap[a].mHeuristic < outMap[b].mHeuristic; });
	// 현재 노드로 설정하고 열린 집합에서 닫힌 집합으로 이동시킨다.
	current = *iter;
	openSet.erase(iter);
	outMap[current].mInOpenSet = false;
	outMap[current].mInClosedSet = true;
	} while (current != goal);
	// 경로를 찾았는가?
	return (current == goal) ? true : false;
}
```

