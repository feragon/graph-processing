#include "etiquette.h"

Etiquette::Etiquette(const Sommet<VertexData> *sommet, Etiquette *predecesseur, int cout, int duree) {
    _sommet = sommet;
    _predecesseur = predecesseur;
    _cost = cout;
    _time = duree;
}

const Sommet<VertexData>* Etiquette::sommet() {
    return _sommet;
}

Etiquette* Etiquette::predecesseur() {
    return _predecesseur;
}

int Etiquette::cost() {
    return _cost;
}

int Etiquette::time() {
    return _time;
}
