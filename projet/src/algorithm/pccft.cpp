#include <graph/graphe.h>
#include "pccft.h"

PCCFT::PCCFT(const Graphe<EdgeData, VertexData>* graph) :
        Search(graph) {

}


void PCCFT::analyzeVertex(const Sommet<VertexData> *vertex) {

    if(closed(vertex)) {
        return;
    }

    auto successors = graph()->successeurs(vertex);

    for(auto l = successors; l; l = l->next) {

        for(auto m = ETIQ(vertex)->second; m; m = m->next) {
            Etiquette *E = new Etiquette(l->value->fin(), m->value, m->value->cost() + l->value->contenu().cost(), m->value->time() + l->value->contenu().time());
            ETIQ(l->value->fin())->second = pareto(ETIQ(l->value->fin()), E);

            if(!closed(l->value->fin())) {
                nextEdges().insert(nextEdges().end(), l->value);
            }
        }
    }

    setExplored(vertex);
    setClosed(vertex);

    Liste<Arete<EdgeData, VertexData>>::efface1(successors);
}

void PCCFT::begin(const Sommet<VertexData> *start) {

    reset();
    _start = start;
    initEtiquettes();

    search(start);
}

Liste<Etiquette>* PCCFT::pareto(std::pair<Sommet<VertexData>*, Liste<Etiquette>*> *pair, Etiquette *E) {

    if(pair) {
        auto l = pair->second;
        while (l) {
            if (E->cost() <= l->value->cost() && E->time() <= l->value->time()) {
                if (E->cost() < l->value->cost() || E->time() < l->value->time()) {
                    auto suppr = l->value;
                    l = l->next;
                    Liste<Etiquette>::retire(suppr, pair->second);
                }
                else
                    l = l->next;
            } else
                l = l->next;
        }

        l = pair->second;
        while (l) {
            if (E->cost() >= l->value->cost() && E->time() >= l->value->time()) {
                if (E->cost() > l->value->cost() || E->time() > l->value->time())
                    return pair->second;
                else
                    l = l->next;
            } else
                l = l->next;
        }
    }

    /*std::cout << "Etiquette " << E->sommet()->cle()<< " : P=";
    if(E->predecesseur()) std::cout << E->predecesseur()->sommet()->cle();
    std::cout << " C=" << E->cost() << " T=" << E->time() << std::endl;*/

    if(pair)
        return new Liste<Etiquette>(E, pair->second);
    else
        return new Liste<Etiquette>(E, nullptr);
}

void PCCFT::meilleurChemin(Sommet<VertexData> *sommet, std::pair<int, int> (*choix)(Etiquette* E), int fenetreMin, int fenetreMax) {

    Etiquette *res = nullptr;

    for(auto l = ETIQ(sommet)->second; l; l = l->next) {

        if(choix(l->value).second >= fenetreMin && choix(l->value).second <= fenetreMax) {
            if(!res)
                res = l->value;
            else if(choix(l->value).first < choix(res).first)
                res = l->value;
        }
    }

    if(res) {
        std::cout << "Meilleur chemin de valeur " << choix(res).first
                  << " dans la fenetre ["
                  << fenetreMin << ";" << fenetreMax << "] (" << choix(res).second << ") :" << std::endl;

        std::string sorti = "";
        while (res->predecesseur()) {
            sorti.insert(0, " -> " + res->sommet()->cle());
            res = res->predecesseur();
        }
        std::cout << sorti.insert(0, res->sommet()->cle()) << std::endl;
    }
    else {
        std::cout << "Il n'y a pas de chemin possible entre "
                  << _start->cle() << " et " << sommet->cle() << " dans la fenetre ["
                  << fenetreMin << ";" << fenetreMax << "]." << std::endl;
    }
    std::cout << std::endl;
}

void PCCFT::reset() {
    Search::reset();

    for(auto l = _etiquettes; l; l = l->next)
        Liste<Etiquette>::efface1(_etiquettes->value->second);

    Liste<std::pair<Sommet<VertexData>*, Liste<Etiquette>*>>::efface1(_etiquettes);
}

PCCFT::~PCCFT() {
    reset();
}

void PCCFT::initEtiquettes() {
    _etiquettes = NULL;

    auto sommets = graph()->sommets();
    for(auto l = sommets; l; l = l->next) {
        auto *pair = new std::pair<Sommet<VertexData>*, Liste<Etiquette>*>(l->value, NULL);

        _etiquettes = new Liste<std::pair<Sommet<VertexData>*, Liste<Etiquette>*>>(pair, _etiquettes);
    }

    Etiquette *E = new Etiquette(_start, nullptr, 0, 0);
    ETIQ(_start)->second = new Liste<Etiquette>(E, nullptr);
}

std::pair<Sommet<VertexData>*, Liste<Etiquette>*>* PCCFT::ETIQ(const Sommet<VertexData>* sommet) {
    for(auto l = _etiquettes; l; l = l->next) {
        if(l->value->first == sommet) {
            return l->value;
        }
    }
    return nullptr;
}

std::pair<int, int> cout(Etiquette* E) {
    return std::pair<int, int>(E->cost(), E->time());
}

std::pair<int, int> temps(Etiquette* E) {
    return std::pair<int, int>(E->time(), E->cost());
}