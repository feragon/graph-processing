#pragma once

#include <iosfwd>
#include <modeling/modelinggraph.h>

class CLI {
    public:
        CLI(std::ostream& out, std::istream& in);

        virtual ~CLI();

        /**
         * @brief Lance l'interface en ligne de commande
         */
        void start();

    private:
        /**
         * @brief Laisse l'utilisateur choisir un graphe ou le créer
         */
        void chooseGraph();

        /**
         * @brief Compare deux suffixes
         * @param fileName Nom du fichier
         * @param suffix Suffixe
         * @return Vrai s'ils sont egaux
         */
        bool sameSuffix(const std::string& fileName, const std::string& suffix) const;

        /**
         * @brief Ouvre un graphe
         * @param path Chemin du graphe
         */
        void openGraph(const std::string& path);

        ModelingGraph* _graph;

        std::ostream& _out;
        std::istream& _in;
};