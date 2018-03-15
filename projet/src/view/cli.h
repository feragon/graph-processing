#pragma once

#include <iosfwd>
#include <modeling/modelinggraph.h>
#include "view.h"

class CLI {
    public:
        CLI(std::ostream& out, std::istream& in);

        virtual ~CLI();

        /**
         * @brief Lance l'interface en ligne de commande
         */
        void start();

        /**
         * @return Graphe
         */
        inline ModelingGraph* graph() const;

        /**
         * @brief Change le graphe
         * @param graph Graphe
         */
        inline void setGraph(ModelingGraph* graph);

        /**
         * @brief Affiche une nouvelle vue
         * @param view Nouvelle vue
         */
        void setView(View* view);

    private:
        /**
         * @brief Affiche la vue précédente
         */
        void previousView();

        Liste<View>* _views;
        View* _currentView;

        ModelingGraph* _graph;

        std::ostream& _out;
        std::istream& _in;
};

ModelingGraph* CLI::graph() const {
    return _graph;
}

void CLI::setGraph(ModelingGraph* graph) {
    if(_graph) {
        delete _graph;
    }

    _graph = graph;
}
