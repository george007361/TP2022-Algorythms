#pragma once 

#include "../IGraph/IGraph.h"
#include <vector>
#include <cassert>

class MatrixGraph : public IGraph
{
public:
	explicit MatrixGraph(const int count);
	MatrixGraph(const IGraph& src);
	virtual ~MatrixGraph() override {};

	// Добавление ребра от from к to.
	virtual void AddEdge(int from, int to) override;

	virtual int VerticesCount() const   override;

	virtual std::vector<int> GetNextVertices(int vertex) const  override;
	virtual std::vector<int> GetPrevVertices(int vertex) const  override;
private:
	std::vector<std::vector<int>> adjMatrix;
};