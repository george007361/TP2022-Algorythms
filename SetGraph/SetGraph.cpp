#include "SetGraph.h"

SetGraph::SetGraph(const int count)
{
	vertices.resize(count);
	reversedVertices.resize(count);
}

SetGraph::SetGraph(const IGraph& src)
{
	vertices.resize(src.VerticesCount());
	reversedVertices.resize(src.VerticesCount());

	for (int from = 0; from < src.VerticesCount(); ++from)
	{
		std::vector<int> nextVerts = src.GetNextVertices(from);
		for (int to = 0; to < nextVerts.size(); ++to)
		{
			AddEdge(from, nextVerts[to]);
		}
	}
}

void SetGraph::AddEdge(int from, int to)
{
	assert(from >= 0 && from < vertices.size());
	assert(to >= 0 && to < vertices.size());
	vertices[from].insert(to);
	reversedVertices[to].insert(from);
}

int SetGraph::VerticesCount() const
{
	return vertices.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < vertices.size());

	std::vector<int> nextVerticies(vertices[vertex].size());
    std::copy(vertices[vertex].begin(), vertices[vertex].end(), nextVerticies.begin());

	return nextVerticies;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < reversedVertices.size());

	std::vector<int> prevVerticies(reversedVertices[vertex].size());
    std::copy(reversedVertices[vertex].begin(), reversedVertices[vertex].end(), prevVerticies.begin());


	return prevVerticies;
}
