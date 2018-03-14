#pragma once

#include <graph/graphe.h>
#include "search.h"
#include "pairPereValeur.h"


class PCC : public Search {
    public:
        PCC(const Graphe<EdgeData, VertexData>* graphe);

        /**
         * @brief Commence la recherche
         * @param start Départ
         * @param choix Fonction de choix de l'arête
         */
        void begin(const Sommet<VertexData>* start, int (*choix)(Arete<EdgeData, VertexData>*));

        virtual void analyzeVertex(const Sommet<VertexData>* vertex) override;

        void pluscourtchemin(Sommet<VertexData>* sommet);

        void reset() override;

        virtual ~PCC();

    private:
        /**
         * @brief Pointeur de fonction pour choisir la donnée soit du cout soit de la duree de l'arete
         * @return int choix de donnée
         */
        int (*_choixDonnee)(Arete<EdgeData, VertexData>*);
        std::set<const Sommet<VertexData>*> _sommetsMarques;
        pairPereValeur* _ppv;

        const Sommet<VertexData>* _start;
};

int cout(Arete<EdgeData, VertexData>* arete);
int duree(Arete<EdgeData, VertexData>* arete);