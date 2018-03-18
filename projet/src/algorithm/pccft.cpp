#include <graph/graphe.h>
#include "pccft.h"

PCCFT::PCCFT(const Graphe<EdgeData, VertexData>* graph) :
        Search(graph) {

}


void PCCFT::analyzeVertex(const Sommet<VertexData> *vertex) {

    auto successors = graph()->successeurs(vertex);
    bool etiquetteUpdated = false;

    for(auto l = successors; l; l = l->next) {

        for(auto m = _etiquettes[vertex]; m; m = m->next) {
            Etiquette *E = new Etiquette(l->value->fin(), m->value, m->value->cost() + l->value->contenu().cost(), m->value->time() + l->value->contenu().time());
            _etiquettes[l->value->fin()] = pareto(_etiquettes[l->value->fin()], E, &etiquetteUpdated);
            if(!etiquetteUpdated) {
                delete E;
            }

            if(etiquetteUpdated) {
                nextEdges().insert(nextEdges().end(), l->value);
            }
        }
    }

    Liste<Arete<EdgeData, VertexData>>::efface1(successors);
}

void PCCFT::begin(const Sommet<VertexData> *start) {

    reset();
    _start = start;
    initEtiquettes();

    search(start);
}

Liste<Etiquette>* PCCFT::pareto(Liste<Etiquette>* etiquettes, Etiquette *E, bool *etiquetteUpdated) {

    *etiquetteUpdated = false;

    if(etiquettes) {
        auto l = etiquettes;
        while (l) {
            if (E->cost() <= l->value->cost() && E->time() <= l->value->time()) {
                if (E->cost() < l->value->cost() || E->time() < l->value->time()) {
                    auto suppr = l->value;
                    l = l->next;
                    Liste<Etiquette>::retire(suppr, etiquettes);
                    delete suppr;
                }
                else if(E->predecesseur() == l->value->predecesseur()) {
                    return etiquettes;
                }
                else {
                    l = l->next;
                }
            }
            else {
                l = l->next;
            }
        }

        l = etiquettes;
        while (l) {
            if (E->cost() >= l->value->cost() && E->time() >= l->value->time()) {
                if (E->cost() > l->value->cost() || E->time() > l->value->time())
                    return etiquettes;
                else
                    l = l->next;
            } else
                l = l->next;
        }

        *etiquetteUpdated = true;
        return new Liste<Etiquette>(E, etiquettes);
    }
    else {

        *etiquetteUpdated = true;
        return new Liste<Etiquette>(E, nullptr);
    }
}

std::vector<const Sommet<VertexData>*> PCCFT::meilleurChemin(const Sommet<VertexData> *sommet, std::pair<int, int> (*choix)(Etiquette* E), int fenetreMin, int fenetreMax) {

    Etiquette *res = nullptr;
    std::vector<const Sommet<VertexData>*> chemin;

    for(auto l = _etiquettes[sommet]; l; l = l->next) {

        if(choix(l->value).second >= fenetreMin && choix(l->value).second <= fenetreMax) {
            if(!res)
                res = l->value;
            else if(choix(l->value).first < choix(res).first)
                res = l->value;
        }
    }

    if(res) {
        std::cout << "Meilleur chemin de valeur " << choix(res).first
                  << " (ressource de " << choix(res).second << ") dans la fenetre ["
                  << fenetreMin << ";" << fenetreMax << "] :" << std::endl;

        std::string sorti = "";
        while (res->predecesseur()) {
            sorti.insert(0, " -> " + res->sommet()->cle());
            chemin.insert(chemin.begin(), res->sommet());
            res = res->predecesseur();
        }
        std::cout << sorti.insert(0, res->sommet()->cle()) << std::endl;
        chemin.insert(chemin.begin(), res->sommet());
    }
    else {
        std::cout << "Il n'y a pas de chemin possible entre "
                  << _start->cle() << " et " << sommet->cle() << " dans la fenetre ["
                  << fenetreMin << ";" << fenetreMax << "]." << std::endl;
    }
    std::cout << std::endl;

    return chemin;
}

void PCCFT::reset() {
    Search::reset();

    for(auto pair : _etiquettes) {
        Liste<Etiquette>::efface2(pair.second);
    }

    _etiquettes.clear();
}

PCCFT::~PCCFT() {
    reset();
}

void PCCFT::initEtiquettes() {
    auto sommets = graph()->sommets();
    for(auto l = sommets; l; l = l->next) {
        _etiquettes[l->value] = NULL;
    }

    Etiquette *E = new Etiquette(_start, nullptr, 0, 0);
    _etiquettes[_start] = new Liste<Etiquette>(E, nullptr);
}

std::pair<int, int> PCCFT::cout(Etiquette* E) {
    return std::pair<int, int>(E->cost(), E->time());
}

std::pair<int, int> PCCFT::temps(Etiquette* E) {
    return std::pair<int, int>(E->time(), E->cost());
}