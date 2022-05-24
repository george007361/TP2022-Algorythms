#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(const int count)
{
	adjMatrix.resize(count);
	for (std::vector<int> line : adjMatrix)
	{
		line.assign(adjMatrix.size(), 0);
	}
}

MatrixGraph::MatrixGraph(const IGraph& src)
{
	adjMatrix.resize(src.VerticesCount());
	for (std::vector<int> line : adjMatrix)
	{
		line.assign(adjMatrix.size(), 0);
	}

	for (int i = 0; i < adjMatrix.size(); i++)
	{
		std::vector<int> adjForVert = src.GetNextVertices(i);
		for (int j = 0; j < adjForVert.size(); j++)
		{
			AddEdge(i, adjForVert[j]);
		}
	}
}

void MatrixGraph::AddEdge(int from, int to)
{
	assert(from >= 0 && from < adjMatrix.size());
	assert(to >= 0 && to < adjMatrix.size());
	adjMatrix[from][to] = 1;
}

int MatrixGraph::VerticesCount() const
{
	return adjMatrix.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < adjMatrix.size());

	std::vector<int> nextVerticies;
	for (int i = 0; i < adjMatrix.size(); i++)
	{
		if (adjMatrix[vertex][i] > 0)
		{
			nextVerticies.push_back(i);
		}
	}

	return nextVerticies;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < adjMatrix.size());
	std::vector<int> prevVerticies;

	for (int i = 0; i < adjMatrix.size(); i++)
	{
		if (i != vertex && adjMatrix[i][vertex] > 0)
		{
			prevVerticies.push_back(i);
		}
	}

	return prevVerticies;
}
