#include <limits>
#include "pairPereValeur.h"

pairPereValeur::pairPereValeur(const Graphe<EdgeData, VertexData> *graphe, const Sommet<VertexData>* source) {

    Liste<Sommet<VertexData>>* l = graphe->sommets();
    liste = NULL;

    while(l != NULL) {

        PereLambda* pl = new PereLambda;
        pl->sommet = l->value;
        pl->pere = NULL;
        pl->lamba = (l->value == source) ? 0 : std::numeric_limits<int>::max();

        liste = new Liste<PereLambda>(pl, liste);

        l = l->next;
    }
}

int pairPereValeur::getLambda(const Sommet<VertexData> *sommet) {
    Liste<PereLambda>* l = liste;

    while(l != NULL) {
        if(l->value->sommet == sommet)
            return l->value->lamba;
        l = l->next;
    }
    return std::numeric_limits<int>::max();
}

const Sommet<VertexData> *pairPereValeur::getPere(const Sommet<VertexData> *sommet) {
    Liste<PereLambda>* l = liste;

    while(l != NULL) {
        if(l->value->sommet == sommet)
            return l->value->pere;
        l = l->next;
    }
    return NULL;
}

void pairPereValeur::setLambda(const Sommet<VertexData> *sommet, int lambda) {
    Liste<PereLambda>* l = liste;

    while(l != NULL) {
        if(l->value->sommet == sommet)
            l->value->lamba = lambda;
        l = l->next;
    }
}

void pairPereValeur::setPere(const Sommet<VertexData> *sommet, const Sommet<VertexData> *pere) {
    Liste<PereLambda>* l = liste;

    while(l != NULL) {
        if(l->value->sommet == sommet)
            l->value->pere = pere;
        l = l->next;
    }
}
