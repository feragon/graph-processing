#pragma once

#include <iosfwd>

class CLI;

class View {
    public:
        View(std::ostream& out, std::istream& in, CLI* cli);
        /**
         * @brief Affiche la vue
         */
        virtual void show() = 0;

        /**
         * @return Sortie
         */
        inline std::ostream& out() const;

        /**
         * @return Entrée
         */
        inline std::istream& in() const;

        /**
         * @return CLI
         */
        inline CLI* cli() const;

        /**
         * @brief Change la CLI
         * @param cli CLI
         */
        inline void setCli(CLI* cli);

    private:
        std::ostream& _out;
        std::istream& _in;
        CLI* _cli;
};

std::ostream& View::out() const {
    return _out;
}

std::istream& View::in() const {
    return _in;
}

CLI* View::cli() const {
    return _cli;
}

void View::setCli(CLI* cli) {
    _cli = cli;
}
