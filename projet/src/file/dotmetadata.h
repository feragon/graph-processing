#pragma once

#include <modeling/vertexdata.h>
#include <modeling/edgedata.h>
#include <graph/arete.h>
#include <graph/liste.h>
#include <vector>
#include <map>

class DotMetaData {
    public:
        virtual ~DotMetaData() = default;
        /**
         * Les double quotes doivent être échapées
         * @param edge Arête
         * @return Label de l'arête
         */
        virtual std::string getEdgeLabel(const Arete<EdgeData, VertexData>* edge);

        /**
         * Les double quotes doivent être échapées
         * @param vertex Sommet
         * @return Couleur de fond du sommet
         */
        virtual std::string getVertexBackground(const Sommet<VertexData>* vertex);

        /**
         * @param edge Arête
         * @return Donne le style de l'arête (dotted, bold, filled)
         */
        virtual std::string getEdgeStyle(const Arete<EdgeData, VertexData>* edge);

        /**
         * @brief Donne le label d'un sommet
         * @param vertex Sommet
         * @return Label
         */
        virtual std::string getVertexLabel(const Sommet<VertexData>* vertex);

        /**
         * @brief Retourne la liste des clusters et des sommets associés
         * @param vertices Liste des sommets à traiter
         * @return Association nom -> sommets
         */
        virtual std::map<std::string, std::vector<Sommet<VertexData>*>> getVerticesCluster(Liste<Sommet<VertexData>>* vertices);

        /**
         * @brief Ajoute des données supplémentaires à la fin du graphe
         * @return Données DOT suplémentaires
         */
        virtual std::string additionalData();
};