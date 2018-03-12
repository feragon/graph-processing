#pragma once

#include <graph/graphe.h>
#include "search.h"
#include "pairPereValeur.h"


class PCC : public Search {
public:
    PCC(const Graphe<EdgeData, VertexData>* graphe, const Sommet<VertexData>* start, int (*choix)(Arete<EdgeData, VertexData>*));

    virtual void analyzeVertex(const Sommet<VertexData>* vertex) override;

    void search1();
private:
    /**
     * @brief Pointeur de fonction pour la donnée du cout ou de la duree de l'arete
     * @return int choix de donnée
     */
    int (*_choix)(Arete<EdgeData, VertexData>*);
    std::set<const Sommet<VertexData>*>* _sommetsMarques;
    pairPereValeur* _ppv;
};

int cout(Arete<EdgeData, VertexData>* arete) {
    return arete->contenu().cost();
}
int duree(Arete<EdgeData, VertexData>* arete) {
    return arete->contenu().time();
}
