#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <stack>


template<class Iterator, class UnaryOp>
void dfs(Iterator it, UnaryOp op)
{
	op(it);
	for(Iterator to: *it) dfs(to, op);
}

template<class Iterator, class UnaryOp, class UnaryPred>
void dfs(Iterator it, UnaryOp op, UnaryPred p)
{
	op(it);
	for(Iterator to: *it) if(p(to)) dfs(to, op, p);
}

/*
template<class Iterator, class UnaryOp, class BinaryOp, class UnaryPred>
Iterator dfs(Iterator it, UnaryOp op, BinaryOp f, UnaryPred p)
{
	op(it);
	for(Iterator to: *it) if(p(to)) f(it, dfs(to, op, p));
	return it;
}
*/

/*
template<class Iterator, class UnaryOp, class UnaryPred>
void dfs(Iterator it, UnaryOp pre, UnaryOp post, UnaryPred p)
{
	pre(it);
	for(Iterator to: *it) if(p(to)) dfs(to, op, p);
	post(it);
}
*/

template <template <typename...> class Outer, template <typename...> class Inner>
struct Edge;

template <template <typename...> class Outer, template <typename...> class Inner>
struct Adj : Outer<Edge<Outer, Inner>> {};

template <template <typename...> class Outer, template <typename...> class Inner>
struct Edge : Inner<typename Adj<Outer, Inner>::iterator> {};

using AdjList = Adj<std::vector, std::vector>;

// TODO: Implement
// using AdjMatrix = Adj<std::vector, ?>


/*
struct Edge;
struct AdjList : std::vector<Edge> {};
struct Edge : std::vector<AdjList::iterator> {};
*/

AdjList to(std::vector<std::vector<size_t>>& graph)
{
	AdjList adjTree; adjTree.resize(graph.size());
	
	for(size_t u = 0; u < graph.size(); u++) for(size_t v: graph[u]) 
		adjTree[u].push_back(adjTree.begin() + v);
	
	return adjTree;
}


int main()
{
	std::vector<std::vector<size_t>> tree = {{1,2}, {3,4}, {5}, {}, {}, {}};
	AdjList adjTree = to(tree);

	dfs(adjTree.begin(), [&](auto it) {std::cout << std::distance(adjTree.begin(), it) << " "; });
	std::cout << std::endl;

	std::vector<std::vector<size_t>> graph = {{1,2,3}, {3,4}, {2,5}, {1}, {}, {}};
	AdjList adjGraph = to(graph);
	
	// Lazy dfs
	{
		std::vector<bool> visited(adjGraph.size(), false);
		auto visit = [&](auto it) { size_t u = std::distance(adjGraph.begin(), it); visited[u] = true; std::cout << u << " ";};
		auto isNotVisited = [&](auto it) { return not visited[std::distance(adjGraph.begin(), it)]; };
		dfs(adjGraph.begin(), visit, isNotVisited);
		std::cout << std::endl;
	}


	{
		using Bool = uint8_t;
		std::vector<Bool> visited(adjGraph.size(), false);
		auto isNotVisited = [&](auto u){ return not std::exchange(visited[std::distance(adjGraph.begin(), u)], true); };
		dfs(adjGraph.begin(), [&](auto it){ std::cout << std::distance(adjGraph.begin(), it) << " "; }, isNotVisited);
		std::cout << std::endl;
	}
	
	{
		size_t count = 0;
		std::vector<bool> visited(adjGraph.size(), false);
		auto visit = [&](auto it) { size_t u = std::distance(adjGraph.begin(), it); visited[u] = true; count++;};
		auto isNotVisited = [&](auto it) { return not visited[std::distance(adjGraph.begin(), it)]; };
		dfs(adjGraph.begin(), visit, isNotVisited);
		std::cout << count << std::endl;
	}
	
	{
		bool loop = 0;
		std::vector<bool> visited(adjGraph.size(), false);
		auto isNotVisited = [&](auto it) { 
			size_t u = std::distance(adjGraph.begin(), it);
			bool isVisited = visited[std::distance(adjGraph.begin(), it)]; 
			if(isVisited) loop = true;
			else visited[u] = true;
			return not isVisited;
		};

		dfs(adjGraph.begin(), [](auto){}, isNotVisited);
		std::cout << loop << std::endl;
	}
}

void dfs(const std::vector<std::vector<size_t>>& graph, size_t start)
{
	std::vector<bool> visited(graph.size());
	std::stack<size_t> s;
	s.push(start);

	while (!s.empty())
	{
		size_t u = s.top(); s.pop();

		if (visited[u]) continue;
		visited[u] = true;
		std::cout << u << " ";

		for (size_t v : graph[u]) s.push(v);
	}
}

void bfs(const std::vector<std::vector<size_t>>& graph, size_t start)
{
	std::vector<bool> visited(graph.size());
	std::queue<size_t> q;
	q.push(start);

	while (!q.empty())
	{
		size_t u = q.front(); q.pop();

		if (visited[u]) continue;
		visited[u] = true;
		std::cout << u << " ";

		for (size_t v : graph[u]) q.push(v);
	}
}


