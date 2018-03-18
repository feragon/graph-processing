#pragma once

#include <graph/graphe.h>
#include "search.h"
#include "pairPereValeur.h"


class PCC : public Search {
protected:
    void analyzeVertex(const Sommet<VertexData>* vertex) override;

public:
    PCC(const Graphe<EdgeData, VertexData>* graphe);

    /**
     * @brief Commence la recherche
     * @param start Départ
     * @param choix Fonction de choix de l'arête
     */
    void begin(const Sommet<VertexData>* start, int (*choix)(Arete<EdgeData, VertexData>*));

    /**
     * @brief Donne le plus court chemin
     * @param sommet
     * @return std::vector<const Sommet<VertexData>*> Meilleur chemin de _start à destination
     */
    std::vector<const Sommet<VertexData>*> plusCourtChemin(Sommet<VertexData>* sommet);

    static int cout(Arete<EdgeData, VertexData>* arete);
    static int temps(Arete<EdgeData, VertexData>* arete);

    void reset() override;
    virtual ~PCC();

private:
    /**
     * @brief Pointeur de fonction pour choisir la donnée soit du cout soit de la duree de l'arete
     * @return int choix de donnée
     */
    int (*_choixDonnee)(Arete<EdgeData, VertexData>*);
    const Sommet<VertexData>* _start;
    pairPereValeur* _ppv;
};