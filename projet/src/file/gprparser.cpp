#include <algorithm>
#include <cstring>
#include "gprparser.h"
#include "resourcessectionparser.h"
#include "parseexception.h"
#include "verticessectionparser.h"
#include "sourcesectionparser.h"
#include "puitssectionparser.h"
#include "arcssectionparser.h"
#include "graphsectionparser.h"

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

    _parser = new ResourcesSectionParser(nullptr);
    _parser = new VerticesSectionParser(_parser);
    _parser = new SourceSectionParser(_parser);
    _parser = new PuitsSectionParser(_parser);
    _parser = new ArcsSectionParser(_parser);
    _parser = new GraphSectionParser(_parser);

    _source = nullptr;
    _puits = nullptr;
}

GPRParser::~GPRParser() {
    SectionParserCOR* next;
    while (_parser) {
        next = _parser->next();
        delete _parser;
        _parser = next;
    }
}

void GPRParser::load() {
    while(_buffer) {
        try {
            _parser->parse(_buffer, this);
        }
        catch (ParseException& e) {
            std::cerr << e.what() << std::endl;
        }

        if(_buffer.fail() && errno != 0) {
            std::cerr << "Erreur de lecture: " << strerror(errno) << std::endl;
        }
    }

    if(_puits && _puits->contenu().canWait()) {
        for(auto vertex = graphe().sommets(); vertex; vertex = vertex->next) {
            if(!vertex->value->contenu().canWait()) {
                vertex->value->contenu().setSup(_puits->contenu().sup());
                vertex->value->contenu().setInf(_puits->contenu().inf());
                vertex->value->contenu().setCanWait(true);
            }
        }
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

    //Suppression des \r
    line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());

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