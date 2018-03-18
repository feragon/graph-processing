#include <limits>
#include "PairPereValeur.h"

PairPereValeur::PairPereValeur(const Graphe<EdgeData, VertexData> *graphe, const Sommet<VertexData>* source) {

    Liste<Sommet<VertexData>>* l = graphe->sommets();
    liste = NULL;

    while(l != NULL) {

        PereLambda* pl = new PereLambda;
        pl->sommet = l->value;
        pl->pere = NULL;
        pl->_lambda = (l->value == source) ? 0 : std::numeric_limits<int>::max();

        liste = new Liste<PereLambda>(pl, liste);

        l = l->next;
    }
}

int PairPereValeur::getLambda(const Sommet<VertexData> *sommet) {
    Liste<PereLambda>* l = liste;

    while(l != NULL) {
        if(l->value->sommet == sommet)
            return l->value->_lambda;
        l = l->next;
    }
    return std::numeric_limits<int>::max();
}

const Sommet<VertexData> *PairPereValeur::getPere(const Sommet<VertexData> *sommet) {
    Liste<PereLambda>* l = liste;

    while(l != NULL) {
        if(l->value->sommet == sommet)
            return l->value->pere;
        l = l->next;
    }
    return NULL;
}

void PairPereValeur::setLambda(const Sommet<VertexData> *sommet, int lambda) {
    Liste<PereLambda>* l = liste;

    while(l != NULL) {
        if(l->value->sommet == sommet)
            l->value->_lambda = lambda;
        l = l->next;
    }
}

void PairPereValeur::setPere(const Sommet<VertexData> *sommet, const Sommet<VertexData> *pere) {
    Liste<PereLambda>* l = liste;

    while(l != NULL) {
        if(l->value->sommet == sommet)
            l->value->pere = pere;
        l = l->next;
    }
}

PairPereValeur::~PairPereValeur() {
    Liste<PereLambda>::efface2(liste);
}
