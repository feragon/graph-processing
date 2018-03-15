#include <limits>
#include <climits>
#include "vertexselector.h"
#include "cli.h"

VertexSelector::VertexSelector(std::ostream& out, std::istream& in, CLI* cli, const std::string& vertexName, bool canBeEmpty) :
        View(out, in, cli) {
    _vertexName = vertexName;
    _canBeEmpty = canBeEmpty;
    _selected = nullptr;
}

void VertexSelector::show() {
    out() << "Liste des sommets du graphe" << std::endl;

    for(auto vertex = cli()->graph()->sommets(); vertex; vertex = vertex->next) {
        out() << vertex->value->cle() << '\t';
    }

    do {
        out() << "\nChoix du sommet " << _vertexName;

        if(_canBeEmpty) {
            out() << " (laissez vide pour ne pas en sélectionner)";
        }

        out() << ":";

        std::string selectedVertex;
        std::getline(in(), selectedVertex);

        if(selectedVertex.empty() && _canBeEmpty) {
            _selected = nullptr;
            return;
        }

        for(auto vertex = cli()->graph()->sommets(); vertex; vertex = vertex->next) {
            if(vertex->value->cle() == selectedVertex) {
                _selected = vertex->value;
                return;
            }
        }

        out() << "Sommet inexistant" << std::endl;
    } while(true);
}
