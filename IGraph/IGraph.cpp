#include "IGraph.h"

bool IGraph::equal(const IGraph &gr)
{
    if(this->VerticesCount() != gr.VerticesCount())
    {
        return false;
    }

    for(int i = 0; i < gr.VerticesCount(); ++i)
    {
        auto thisNextVerts = this->GetNextVertices(i);
        auto grNextVerts = gr.GetNextVertices(i);
        if(thisNextVerts.size() != grNextVerts.size())
        {
            return false;
        }

        std::sort(thisNextVerts.begin(), thisNextVerts.end());
        std::sort(grNextVerts.begin(), grNextVerts.end());

        if (thisNextVerts != grNextVerts)
        {
            return false;
        }   
    }

    return true;
}