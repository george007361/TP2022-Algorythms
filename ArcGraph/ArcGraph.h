#pragma once 

#include "../IGraph/IGraph.h"
#include <vector>
#include <cassert>

class ArcGraph : public IGraph
{
public:
	ArcGraph(const int count);
	ArcGraph(const IGraph& src);
	virtual ~ArcGraph() override {};

	// Добавление ребра от from к to.
	virtual void AddEdge(int from, int to) override;

	virtual int VerticesCount() const   override;

	virtual std::vector<int> GetNextVertices(int vertex) const  override;
	virtual std::vector<int> GetPrevVertices(int vertex) const  override;
private:
	std::vector<std::pair<int, int>> edges;
	int verticesCount;
};