#pragma once

#include <graph/graphe.h>
#include "search.h"

class DFS : public Search {
    public:
        DFS(const Graphe<EdgeData, VertexData>& graph);

        void search() override;
};