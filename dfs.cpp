#include <iostream>
#include <vector>
#include <utility>


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

int main()
{
	std::vector<std::vector<size_t>> graph = {{1,2}, {3,4}, {2,5}, {}, {}, {}};

	AdjList adj; 
	adj.reserve(graph.size()); // This is super important, otherwise adj.begin() might get reallocated 
	auto start = adj.begin();
	for(auto& u: graph)
	{
		adj.emplace_back();
		for(size_t v: u) adj.back().push_back(start + v);
	}

	// dfs(adj.begin(), [=](auto it) {std::cout << std::distance(start, it) << std::endl; });


	using Bool = uint8_t;
	std::vector<Bool> visited(adj.size(), false);
	auto isVisited = [&visited, start](auto u){ return not std::exchange(visited[std::distance(start, u)], true); };

	dfs(start, [=](auto it){ std::cout << std::distance(start, it) << std::endl; }, isVisited);
	

}
