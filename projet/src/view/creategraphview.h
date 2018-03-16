#pragma once

#include <modeling/modelinggraph.h>
#include "menuview.h"

class CreateGraphView : public MenuView {
    public:
        CreateGraphView(std::ostream& out, std::istream& in, CLI* cli);

        /**
         * @return Graphe
         */
        inline const ModelingGraph& graph() const;

        /**
         * @return Faux s'il faut sauvegarder le graphe
         */
        inline bool discard() const;

    private:
        void onCreateVertexSelected();
        void onCreateEdgeSelected();
        void onDiscardSelected();

        ModelingGraph _graph;
        bool _discard;
};

const ModelingGraph& CreateGraphView::graph() const {
    return _graph;
}

bool CreateGraphView::discard() const {
    return _discard;
}