#pragma once

#include <string>

class Identifiable {
    private:
        std::string _cle;

    public:
        /**
         * @brief Crée un élément identifiable
         * @param cle Clé
         */
        Identifiable(const std::string& cle);

        /**
         * @return Clé
         */
        inline std::string cle() const;

        /**
         * @brief Change la clé
         * @param cle Nouvelle clé
         */
        inline void setCle(const std::string& cle);

        operator std::string() const;
        friend std::ostream& operator << (std::ostream& o, const Identifiable& i);
};

std::string Identifiable::cle() const {
    return _cle;
}

void Identifiable::setCle(const std::string& cle) {
    _cle = cle;
}