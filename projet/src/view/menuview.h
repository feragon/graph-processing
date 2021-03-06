#pragma once

#include <functional>
#include <vector>
#include "view.h"

class MenuView : public View {
    public:
        MenuView(std::ostream& out, std::istream& in, CLI* cli, bool canQuit);

        void show() override;

    protected:
        /**
         * @brief Ferme le menu
         */
        void quitMenu();

        /**
         * @brief Ajoute un item au menu
         * @param name Nom
         * @param callback Fonction appelée lors de la selection
         */
        void addItem(const std::string& name, const std::function<void(void)>& callback);

    private:
        bool _canQuit;
        bool _showMenu;
        std::vector<std::pair<std::string, std::function<void(void)>>> _items;
};