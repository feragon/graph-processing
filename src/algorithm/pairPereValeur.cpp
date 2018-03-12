#include <limits>
#include "pairPereValeur.h"

pairPereValeur::pairPereValeur(const Graphe<EdgeData, VertexData> *graphe) {

    Liste<Sommet<VertexData>>* l = graphe->sommets();

    while(l != NULL) {

        PereLambda* pl;
        pl->sommet = l->value;
        pl->pere = NULL;
        pl->lamba = std::numeric_limits<int>::max();

        l = l->next;
    }
}

int pairPereValeur::getLambda(const Sommet<VertexData> *sommet) {
    Liste<PereLambda>* l = liste;

    while(l->next != NULL) {
        if(l->value->sommet == sommet)
            return l->value->lamba;
        l = l->next;
    }
    return -1;
}

const Sommet<VertexData> *pairPereValeur::getPere(const Sommet<VertexData> *sommet) {
    Liste<PereLambda>* l = liste;

    while(l->next != NULL) {
        if(l->value->sommet == sommet)
            return l->value->pere;
        l = l->next;
    }
    return NULL;
}

void pairPereValeur::setLambda(const Sommet<VertexData> *sommet, int lambda) {
    Liste<PereLambda>* l = liste;

    while(l->next != NULL) {
        if(l->value->sommet == sommet)
            l->value->lamba = lambda;
        l = l->next;
    }
}

void pairPereValeur::setPere(const Sommet<VertexData> *sommet, const Sommet<VertexData> *pere) {
    Liste<PereLambda>* l = liste;

    while(l->next != NULL) {
        if(l->value->sommet == sommet)
            l->value->pere = pere;
        l = l->next;
    }
}
