#pragma once 

#include "../IGraph/IGraph.h"
#include <vector>
#include <cassert>
#include <unordered_set>

class SetGraph : public IGraph
{
public:
	explicit SetGraph(const int count);
	SetGraph(const IGraph& src);
	virtual ~SetGraph() override {};

	// Добавление ребра от from к to.
	virtual void AddEdge(int from, int to) override;

	virtual int VerticesCount() const   override;

	virtual std::vector<int> GetNextVertices(int vertex) const  override;
	virtual std::vector<int> GetPrevVertices(int vertex) const  override;
private:
	std::vector<std::unordered_set<int>> vertices;
	std::vector<std::unordered_set<int>> reversedVertices;
};