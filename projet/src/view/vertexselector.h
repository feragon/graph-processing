#pragma once

#include <string>
#include <modeling/vertexdata.h>
#include <graph/sommet.h>
#include <modeling/modelinggraph.h>
#include "view.h"

class VertexSelector : public View {
    public:
        VertexSelector(std::ostream& out, std::istream& in, CLI* cli,
                       const std::string& vertexName,
                       bool canBeEmpty,
                       ModelingGraph* graph = nullptr);

        void show() override;

        /**
         * @return Sommet selectionné par l'utilisateur
         */
        inline const Sommet<VertexData>* selected() const;

    private:
        ModelingGraph* graph() const;

        std::string _vertexName;
        const Sommet<VertexData>* _selected;
        bool _canBeEmpty;
        ModelingGraph* _graph;
};

const Sommet<VertexData>* VertexSelector::selected() const {
    return _selected;
}