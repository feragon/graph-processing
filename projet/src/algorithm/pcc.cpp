#include <limits>
#include <set>
#include "pcc.h"

PCC::PCC(const Graphe<EdgeData, VertexData>* graphe) :
        Search(graphe) {
    _ppv = nullptr;
}

PCC::~PCC() {
    if(_ppv) {
        delete _ppv;
    }
}

void PCC::reset() {
    Search::reset();
    if(_ppv) {
        delete _ppv;
        _ppv = nullptr;
    }
}

void PCC::begin(const Sommet<VertexData>* start, int (* choix)(Arete<EdgeData, VertexData>*)) {
    reset();
    _sommetsMarques.clear();
    _ppv = new pairPereValeur(graph(), start);
    _start = start;
    _choixDonnee = choix;

    search(start);
}

void PCC::analyzeVertex(const Sommet<VertexData>* vertex) {
    if(closed(vertex)) {
        return;
    }

    auto neighbors = graph()->adjacences(vertex);
    std::pair<Sommet<VertexData>*, Arete<EdgeData, VertexData>*>* nextVertex = NULL;

    for(auto l = neighbors; l; l = l->next) {
        if(!closed(l->value->first)) {

            int nouveauLambda = std::numeric_limits<int>::max();

            if (_ppv->getLambda(vertex) < nouveauLambda)
                nouveauLambda = _ppv->getLambda(vertex) + _choixDonnee(l->value->second);

            if (nouveauLambda < _ppv->getLambda(l->value->first)) {
                _ppv->setLambda(l->value->first, nouveauLambda);
                _ppv->setPere(l->value->first, vertex);

                std::cout << "Mise a jour de " << l->value->first->cle()
                          << " : pere=" << vertex->cle()
                          << " val=" << _ppv->getLambda(l->value->first) << std::endl;
            }

            if(!explored(l->value->first)) {
                auto it = nextVertices().begin();
                while((it != nextVertices().end())
                      && (_ppv->getLambda(l->value->first) > _ppv->getLambda(it->first))) {
                    it++;
                }
                nextVertices().insert(it, *(l->value));
            }

        }
    }

    setExplored(vertex);
    setClosed(vertex);

    Liste<std::pair<Sommet<VertexData>*, Arete<EdgeData, VertexData>*>>::efface1(neighbors);
}

void PCC::pluscourtchemin(Sommet<VertexData>* sommet) {
    int valeur = _ppv->getLambda(sommet);

    if(valeur == std::numeric_limits<int>::max())
        std::cout << "Il n'existe pas de chemin entre " << _start->cle() << " et " << sommet->cle() << std::endl;
    else {
        std::cout << "PCC de valeur " << valeur << " : ";

        const Sommet<VertexData> *s = sommet;
        while (s != _start) {
            std::cout << s->cle();
            s = _ppv->getPere(s);
            std::cout << " <- ";
        }
        std::cout << s->cle() << std::endl;
    }
}

int cout(Arete<EdgeData, VertexData>* arete) {
    return arete->contenu().cost();
}
int duree(Arete<EdgeData, VertexData>* arete) {
    return arete->contenu().time();
}