#include <limits>
#include <set>
#include <modeling/negativevaluation.h>
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
    _ppv = new PairPereValeur(graph(), start);
    _start = start;
    _choixDonnee = choix;

    search(start);
}

void PCC::analyzeVertex(const Sommet<VertexData>* vertex) {
    if(closed(vertex)) {
        return;
    }

    auto successors = graph()->successeurs(vertex);

    for(auto l = successors; l; l = l->next) {
        if(!closed(l->value->fin())) {
            int nouveauLambda = std::numeric_limits<int>::max();

            if (_ppv->getLambda(vertex) < nouveauLambda) {
                int valuation = _choixDonnee(l->value);
                if(valuation < 0) {
                    throw NegativeValuation(("L'arête " + l->value->cle() + " a une valuation négative.").c_str());
                }
                nouveauLambda = _ppv->getLambda(vertex) + valuation;
            }

            if (nouveauLambda < _ppv->getLambda(l->value->fin())) {
                _ppv->setLambda(l->value->fin(), nouveauLambda);
                _ppv->setPere(l->value->fin(), vertex);
            }

            if(!explored(l->value->fin())) {
                auto it = nextEdges().begin();
                while((it != nextEdges().end())
                      && (_ppv->getLambda(l->value->fin()) > _ppv->getLambda((*it)->fin()))) {
                    it++;
                }
                nextEdges().insert(it, l->value);
            }
        }
    }

    setExplored(vertex);
    setClosed(vertex);

    Liste<Arete<EdgeData, VertexData>>::efface1(successors);
}

std::vector<std::pair<const Sommet<VertexData>*, int>> PCC::plusCourtChemin(Sommet<VertexData>* sommet, int* res) {
    int valeur = _ppv->getLambda(sommet);
    std::vector<std::pair<const Sommet<VertexData>*, int>> chemin;

    if(valeur != std::numeric_limits<int>::max()) {
        if(res) {
            *res = valeur;
        }
        const Sommet<VertexData> *s = sommet;

        while (s != _start) {
            chemin.insert(chemin.begin(), std::pair<const Sommet<VertexData>*, int>(s, _ppv->getLambda(s)));
            s = _ppv->getPere(s);
        }

        chemin.insert(chemin.begin(), std::pair<const Sommet<VertexData>*, int>(s, _ppv->getLambda(s)));
    }

    return chemin;
}

int PCC::cout(Arete<EdgeData, VertexData>* arete) {
    return arete->contenu().cost();
}
int PCC::temps(Arete<EdgeData, VertexData>* arete) {
    return arete->contenu().time();
}