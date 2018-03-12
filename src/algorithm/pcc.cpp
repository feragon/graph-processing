#include <limits>
#include <set>
#include "pcc.h"

PCC::PCC(const Graphe<EdgeData, VertexData>* graphe, const Sommet<VertexData>* start, int (*choix)(Arete<EdgeData, VertexData>*)) :
        Search(graphe, start){
    _choix = choix;
    _sommetsMarques = new std::set<const Sommet<VertexData>*>;
    _ppv = new pairPereValeur(graph());
}

void PCC::analyzeVertex(const Sommet<VertexData>* vertex) {

    Liste<Sommet<VertexData>>* l = graph()->voisins(vertex);

    while(l->next != NULL) {

        if(_sommetsMarques->find(l->value) == _sommetsMarques->end()) {

            int nouveauLambda = _ppv->getLambda(vertex) + _choix(graph()->getAreteParSommets(vertex, l->value));

            if(nouveauLambda < _ppv->getLambda(l->value)) {
                _ppv->setLambda(l->value, nouveauLambda);
                _ppv->setPere(l->value, vertex);
            }
        }

        l = l->next;
    }
}

void PCC::search1() {
    int n = graph()->nombreSommets();
    bool fin = false;

    const Sommet<VertexData>* sommetk = start();
    _sommetsMarques->insert(start());


    while(_sommetsMarques->size() < n && !fin) {
        analyzeVertex(sommetk);

        //pour tous les sommets de X-S checher le min des lambdas
        Liste<Sommet<VertexData>>* l = graph()->sommets();

        while(l->next != NULL) {
            if(_sommetsMarques->find(l->value) == _sommetsMarques->end()) {
                if(_ppv->getLambda(l->value) < _ppv->getLambda(sommetk))
                    sommetk = l->value;
            }

            l = l->next;
        }

        if(_ppv->getLambda(sommetk) == std::numeric_limits<int>::max()) {
            fin = true;
        }
        else {
            _sommetsMarques->insert(sommetk);
        }
    }

}