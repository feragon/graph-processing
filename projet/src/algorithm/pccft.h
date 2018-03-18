#pragma once

#include <limits>
#include "search.h"
#include "etiquette.h"

class PCCFT : public Search {
    protected:
        void analyzeVertex(const Sommet<VertexData>* vertex) override;

        void initEtiquettes();

        Liste<Etiquette>* pareto(std::pair<Sommet<VertexData>*, Liste<Etiquette>*> *pair, Etiquette *E);

        std::pair<Sommet<VertexData>*, Liste<Etiquette>*>* ETIQ(const Sommet<VertexData>* sommet);

    public:
        PCCFT(const Graphe<EdgeData, VertexData>* graph);

        /**
         * @brief Commence la recherche
         * @param start Départ
         */
        void begin(const Sommet<VertexData>* start);

        /**
         * @brief Donne le meilleur chemin
         * @param destination Destination
         * @param choix Fonction de choix
         * @param fenetreMin Fenetre minimale
         * @param fenetreMax Fenetre maximale
         * @TODO: retourner std::vector<Sommet<VertexData>*>
         */
        void meilleurChemin(Sommet<VertexData>* destination, std::pair<int, int> (*choix)(Etiquette* E), int fenetreMin = 0, int fenetreMax = std::numeric_limits<int>::max());

        void reset() override;

        virtual ~PCCFT();

    private:
        const Sommet<VertexData>* _start;
        Liste<std::pair<Sommet<VertexData>*, Liste<Etiquette>*>>* _etiquettes;
};

std::pair<int, int> cout(Etiquette* E);
std::pair<int, int> temps(Etiquette* E);