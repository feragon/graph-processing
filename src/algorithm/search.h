#pragma once

#include <processor/vertexdata.h>
#include <processor/edgedata.h>
#include <graph/arete.h>
#include <vector>

class Search {
    public:
        /**
         * @brief Commence le parcours
         */
        virtual void search() = 0;

        /**
         * @return Ordre de parcours des arêtes
         */
        inline const std::vector<const Arete<EdgeData, VertexData>*>& order() const;

    protected:
        /**
         * @brief Ajoute une arête à la liste du parcours
         * @param edge Arête parcourue
         */
        inline void addEdge(const Arete<EdgeData, VertexData>* edge);

    private:
        std::vector<const Arete<EdgeData, VertexData>*> _order;
};

const std::vector<const Arete<EdgeData, VertexData>*>& Search::order() const {
    return _order;
}

void Search::addEdge(const Arete<EdgeData, VertexData>* edge) {
    _order.push_back(edge);
}
