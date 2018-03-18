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
    _ppv = new pairPereValeur(graph(), start);
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

            if (_ppv->getLambda(vertex) < nouveauLambda)
                nouveauLambda = _ppv->getLambda(vertex) + _choixDonnee(l->value);

            if (nouveauLambda < _ppv->getLambda(l->value->fin())) {
                _ppv->setLambda(l->value->fin(), nouveauLambda);
                _ppv->setPere(l->value->fin(), vertex);

                /*std::cout << "Mise a jour de " << l->value->fin()->cle()
                          << " : pere=" << vertex->cle()
                          << " val=" << _ppv->getLambda(l->value->fin()) << std::endl;*/
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

std::vector<const Sommet<VertexData>*> PCC::plusCourtChemin(Sommet<VertexData>* sommet) {

    int valeur = _ppv->getLambda(sommet);
    std::vector<const Sommet<VertexData>*> chemin;

    if(valeur == std::numeric_limits<int>::max())
        std::cout << "Il n'existe pas de chemin entre " << _start->cle() << " et " << sommet->cle() << std::endl;
    else {
        std::cout << "PCC de valeur " << valeur << " : ";

        const Sommet<VertexData> *s = sommet;

        std::string sorti = "";
        while (s != _start) {
            sorti.insert(0, " -> " + s->cle());
            chemin.insert(chemin.begin(), s);
            s = _ppv->getPere(s);
        }
        std::cout << sorti.insert(0, s->cle()) << std::endl;
        chemin.insert(chemin.begin(), s);
    }

    return chemin;
}

int cout(Arete<EdgeData, VertexData>* arete) {
    return arete->contenu().cost();
}
int temps(Arete<EdgeData, VertexData>* arete) {
    return arete->contenu().time();
}