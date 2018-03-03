#include <algorithm>
#include "gprparser.h"

/**
 * @param c1 Caractère 1
 * @param c2 Caractère 2
 * @return Vrai si les deux caractère sont des espaces
 */
bool bothAreSpaces(char c1, char c2) {
    return c1 == ' ' && c2 == ' ';
}

GPRParser::GPRParser(std::istream& buffer) :
    _buffer(buffer) {

}

void GPRParser::load() {
    std::string line;
    while(std::getline(_buffer, line)) {
        cleanLine(line);

        if(line.empty()) {
            continue;
        }

        std::cout << line << std::endl;
    }
}


void GPRParser::cleanLine(std::string& line) {
    unsigned long index;

    //Suppression des commentaires
    index = line.find('#');
    if(index != std::string::npos) {
        line = line.substr(0, index);
    }

    //Remplacement des tabulations par des espaces
    std::replace(line.begin(), line.end(), '\t', ' ');

    //Suppression des espaces en double
    std::string::iterator newEnd = std::unique(line.begin(), line.end(), bothAreSpaces);
    line.erase(newEnd, line.end());

    //Suppression des espaces en début de chaîne
    index = line.find_first_not_of(" \t");
    if(index != std::string::npos) {
        line.erase(0, index);
    }

    //Suppression des espaces en fin de chaîne
    index = line.find_last_not_of(" \t");
    if(index != std::string::npos) {
        line.erase(index + 1, line.length());
    }
}
