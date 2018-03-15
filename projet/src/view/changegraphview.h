#pragma once

#include "view.h"
#include "menuview.h"

class ChangeGraphView : public MenuView {
    public:
        ChangeGraphView(std::ostream& out, std::istream& in, CLI* cli);

        void show() override;

    private:
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
};