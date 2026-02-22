#include <iostream>
#include <vector>
#include <utility>

template<class Iterator, class UnaryOp>
void dfs(Iterator it, UnaryOp op)
{
	op(it);
	for(Iterator to: *it) dfs(to, op);
}

template<class Iterator, class UnaryPred, class UnaryOp>
void dfs(Iterator it, UnaryPred p, UnaryOp op)
{
	op(it);
	for(Iterator to: *it) if(p(to)) dfs(to, p, op);
}

using Bool = uint8_t;


template <template <typename...> class Outer = std::vector,
		  template <typename...> class Inner = std::vector>
struct Edge;

template <template <typename...> class Outer = std::vector,
		  template <typename...> class Inner = std::vector>
struct Adj : Outer<Edge<Outer, Inner>> {};

template <template <typename...> class Outer,
		  template <typename...> class Inner>
struct Edge : Inner<typename Adj<Outer, Inner>::iterator> {};

/*
template <template <typename...> class Container = std::vector>
struct Edge;

template <template <typename...> class Container = std::vector>
struct Adj : Container<Edge<Container>> {};

template <template <typename...> class Container>
struct Edge : Container<typename Adj<Container>::iterator> {};
*/

/*
struct Edge;
struct Adj : std::vector<Edge> {};
struct Edge : std::vector<Adj::iterator> {};
*/

int main()
{
	std::vector<std::vector<size_t>> adjI;
	adjI.push_back({1, 2}); adjI.push_back({3, 4}); adjI.push_back({2, 5});
	adjI.push_back({}); adjI.push_back({}); adjI.push_back({});

	Adj adj; 
	adj.reserve(adjI.size()); // This is super important, otherwise adj.begin() might get reallocated 
	auto start = adj.begin();
	for(auto& u: adjI)
	{
		adj.emplace_back();
		for(size_t v: u) adj.back().push_back(start + v);
	}

	// dfs(adj.begin(), [=](auto it) {std::cout << std::distance(start, it) << std::endl; });


	std::vector<Bool> visited(adj.size(), false);
	auto isVisited = [&visited, start](auto u){ return not std::exchange(visited[std::distance(start, u)], true); };

	dfs(start, isVisited, [=](auto it){ std::cout << std::distance(start, it) << std::endl; });
	

}
