// Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами. Найдите количество различных кратчайших путей между заданными вершинами. 
// Требования: сложность O(V+E). 
// Формат ввода.
// v: кол-во вершин (макс. 50000),
// n: кол-во ребер (макс. 200000),
// n пар реберных вершин,
// пара вершин u, w для запроса.
// Формат вывода.
// Количество кратчайших путей от u к w.

#include <cassert>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph
{
public:
	explicit Graph(const int vertsCount_, const int edgesCount_);
	~Graph() {}

	Graph(const Graph&) = default;
	Graph& operator=(const Graph&) = default;

	Graph(Graph&&) = default;
	Graph& operator=(Graph&&) = default;

	void addEdge(const int from, const int to);
	int countMinWays(const int from, const int to) const;
	void DFS(int& countMinWays, int& minWayLenght, const int currentWayLenght, const int from, const int to, vector<bool> visited) const;
	int BFS(int from, int to);

private:
	int vertsCount;
	int edgesCount;
	vector<vector<int>> edgesList;

	struct Vert
	{
		Vert(int minWayLen_) : visited(false), minWaysCount(0), minWayLen(minWayLen_) {}

		bool visited;
		int minWaysCount;
		int minWayLen;
	};
};

Graph::Graph(const int vertsCount_, const int edgesCount_) : vertsCount(vertsCount_), edgesCount(edgesCount_)
{
	assert(vertsCount_ >= 0 && edgesCount_ >= 0);
	edgesList.resize(vertsCount);
}

void Graph::addEdge(const int from, const int to)
{
	assert(from >= 0 && to >= 0 && from < vertsCount&& to < vertsCount);
	edgesList[from].push_back(to);
}

int Graph::countMinWays(const int from, const int to) const
{
	assert(from >= 0 && to >= 0 && from < vertsCount&& to < vertsCount);

	vector<bool> visited(vertsCount, false);
	int minWayLenght = vertsCount + 1;
	int countMinWays = 0;
	int currentWayLenght = 0;

	DFS(countMinWays, minWayLenght, currentWayLenght, from, to, visited);

	return countMinWays;
}

// Не проходит контест, поиск в глубину с рекурсией.
void Graph::DFS(int& countMinWays, int& minWayLenght, const int currentWayLenght, const int vertFrom, const int vertTo, vector<bool> visited) const
{
	visited[vertFrom] = true;

	if (currentWayLenght > minWayLenght)
	{
		return;
	}

	if (vertFrom == vertTo)
	{
		if (currentWayLenght < minWayLenght)
		{
			minWayLenght = currentWayLenght;
			countMinWays = 1;
		}
		else if (currentWayLenght == minWayLenght)
		{
			++countMinWays;
		}
		else
		{
			assert(false);
		}

		return;
	}
	else
	{
		for (int i = 0; i < edgesList[vertFrom].size(); ++i)
		{
			if (!visited[edgesList[vertFrom][i]])
			{
				DFS(countMinWays, minWayLenght, currentWayLenght + 1, edgesList[vertFrom][i], vertTo, visited);
			}
		}
	}
}

// Рабочая версия с BFS 
int Graph::BFS(int from, int to)
{
	vector<Vert> verts(vertsCount, Vert(vertsCount + 1));
	queue<int>  que;

	que.push(from);
	verts[from].visited = true;
	verts[from].minWayLen = 0;
	verts[from].minWaysCount = 1;

	while (que.size())
	{
		int curr = que.front();
		que.pop();

		if (curr == to)
		{
			break;
		}

		for (auto child : edgesList[curr])
		{
			if (verts[child].visited == false)
			{
				que.push(child);
				verts[child].visited = true;
			}

			if (verts[child].minWayLen > verts[curr].minWayLen + 1)
			{
				verts[child].minWayLen = verts[curr].minWayLen + 1;
				verts[child].minWaysCount = verts[curr].minWaysCount;
			}
			else if (verts[child].minWayLen == verts[curr].minWayLen + 1)
			{
				verts[child].minWaysCount += verts[curr].minWaysCount;
			}
		}
	}

	return verts[to].minWaysCount;
}

int main() {
	int v, n, u, w;
	cin >> v >> n;
	Graph graph(v, n);

	for (int i = 0; i < n; ++i)
	{
		cin >> u >> w;

		// неориентированный граф
		graph.addEdge(u, w);
		graph.addEdge(w, u);
	}

	cin >> u >> w;

	cout << graph.BFS(u, w);
	// cout << graph.DFS(u, w);

	return EXIT_SUCCESS;
}