#pragma once

#include <graph/graphe.h>
#include <limits>
#include "search.h"
#include "etiquette.h"

class PCCFT : public Search {
    protected:
        void analyzeVertex(const Sommet<VertexData>* vertex) override;

        void initEtiquettes();

        Liste<Etiquette>* pareto(Liste<Etiquette>* etiquettes, Etiquette *E, bool *etiquetteUpdate);

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
         * @param etiquette Résultat, ou nullptr pour ne pas le renvoyer, pas changé si le chemin est vide
         * @return std::vector<const Sommet<VertexData>*> Meilleur chemin de _start à destination
         */
        std::vector<std::pair<const Sommet<VertexData>*, int>> meilleurChemin(const Sommet<VertexData>* destination,
                                                              std::pair<int, int> (*choix)(Etiquette* E),
                                                              int fenetreMin = 0,
                                                              int fenetreMax = std::numeric_limits<int>::max(),
                                                              Etiquette* etiquette = nullptr
        );

        static std::pair<int, int> cout(Etiquette* E);
        static std::pair<int, int> temps(Etiquette* E);

        void reset() override;
        virtual ~PCCFT();

    private:
        /**
         * @brief Pointeur de fonction pour choisir la donnée
         * @return std::pair<int, int> choix de donnée
         */
        std::pair<int, int> (*_choixDonnee)(Etiquette*) = nullptr;
        const Sommet<VertexData>* _start;
        std::map<const Sommet<VertexData>*, Liste<Etiquette>*> _etiquettes;
};