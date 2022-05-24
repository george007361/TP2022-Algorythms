#pragma once

#include "../IGraph/IGraph.h"
#include <vector>
#include <cassert>

class ListGraph : public IGraph
{
public:
	explicit ListGraph(const int count);
	ListGraph(const IGraph& src);
	virtual ~ListGraph() override {};

	virtual void AddEdge(int from, int to) override;
	virtual int VerticesCount() const override;
	virtual std::vector<int> GetNextVertices(int vertex) const override;
	virtual std::vector<int> GetPrevVertices(int vertex) const override;
private:
	std::vector<std::vector<int>> adjList;
};
