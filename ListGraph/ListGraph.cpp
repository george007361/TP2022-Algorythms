#include "ListGraph.h"

ListGraph::ListGraph(const int count)
{
	adjList.resize(count);
}

ListGraph::ListGraph(const IGraph& src) {
	adjList.resize(src.VerticesCount());
	for (int i = 0; i < src.VerticesCount(); i++)
	{
		adjList[i] = src.GetNextVertices(i);
	}
}

void ListGraph::AddEdge(int from, int to)
{
	assert(from >= 0 && from < adjList.size());
	assert(to >= 0 && to < adjList.size());
	adjList[from].push_back(to);
}

int ListGraph::VerticesCount() const
{
	return adjList.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < adjList.size());
	return adjList[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const
{
	std::vector<int> prevVerticies;
	for (int from = 0; from < adjList.size(); ++from)
	{
		for (int i = 0; i < adjList[from].size(); ++i)
		{
			if (adjList[from][i] == vertex)
			{
				prevVerticies.push_back(from);
			}
		}

	}

	return prevVerticies;
}
