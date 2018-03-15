#pragma once

#include <string>
#include <modeling/vertexdata.h>
#include <graph/sommet.h>
#include "view.h"

class VertexSelector : public View {
    public:
        VertexSelector(std::ostream& out, std::istream& in, CLI* cli, const std::string& vertexName, bool canBeEmpty);

        void show() override;

        /**
         * @return Sommet selectionné par l'utilisateur
         */
        inline const Sommet<VertexData>* selected() const;

    private:
        std::string _vertexName;
        const Sommet<VertexData>* _selected;
        bool _canBeEmpty;
};

const Sommet<VertexData>* VertexSelector::selected() const {
    return _selected;
}