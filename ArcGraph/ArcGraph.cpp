#include "ArcGraph.h"

ArcGraph::ArcGraph(const int count) :
	verticesCount(count)
{}

ArcGraph::ArcGraph(const IGraph& src)
{
	verticesCount = src.VerticesCount();

	for (int from = 0; from < src.VerticesCount(); ++from)
	{
		std::vector<int> nextVerts = src.GetNextVertices(from);
		for (int i = 0; i < nextVerts.size(); ++i)
		{
			AddEdge(from, nextVerts[i]);
		}
	}
}

void ArcGraph::AddEdge(int from, int to)
{
	assert(from >= 0 && from < verticesCount);
	assert(to >= 0 && to < verticesCount);
	edges.emplace_back(from, to);
}

int ArcGraph::VerticesCount() const
{
	return verticesCount;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < verticesCount);

	std::vector<int> nextVerticies;

	for (const auto& edge : edges)
	{
		if (edge.first == vertex)
		{
			nextVerticies.push_back(edge.second);
		}
	}

	return nextVerticies;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < verticesCount);

	std::vector<int> prevVerticies;

	for (const auto& edge : edges)
	{
		if (edge.second == vertex)
		{
			prevVerticies.push_back(edge.first);
		}
	}

	return prevVerticies;
}
