#include <limits>
#include <set>
#include "pcc.h"

PCC::PCC(const Graphe<EdgeData, VertexData>* graphe, const Sommet<VertexData>* start, int (*choix)(Arete<EdgeData, VertexData>*)) :
        Search(graphe, start){
    _choixDonnee = choix;
    _sommetsMarques = new std::set<const Sommet<VertexData>*>;
    _ppv = new pairPereValeur(graph(), start);
}

void PCC::analyzeVertex(const Sommet<VertexData>* vertex) {

    Liste<Sommet<VertexData>>* l = graph()->voisins(vertex);
    int nouveauLambda;

    while(l != NULL) {

        if(_sommetsMarques->find(l->value) == _sommetsMarques->end()) {

            if(_ppv->getLambda(vertex) == std::numeric_limits<int>::max())
                nouveauLambda = _ppv->getLambda(vertex);
            else {
                nouveauLambda = _ppv->getLambda(vertex) + _choixDonnee(graph()->getAreteParSommets(vertex, l->value));
            }

            if(nouveauLambda < _ppv->getLambda(l->value)) {
                _ppv->setLambda(l->value, nouveauLambda);
                _ppv->setPere(l->value, vertex);

                std::cout << "Mise a jour de " << l->value->cle() << " : pere=" << vertex->cle() << " val=" << _ppv->getLambda(l->value) << std::endl;
            }


        }

        l = l->next;
    }
}

void PCC::search1() {
    int n = graph()->nombreSommets();
    bool fin = false;

    const Sommet<VertexData>* sommetk = start();
    _sommetsMarques->insert(sommetk);


    while(_sommetsMarques->size() < n && !fin) {
        analyzeVertex(sommetk);

        //pour tous les sommets de X-S checher le min des lambdas
        Liste<Sommet<VertexData>>* l = graph()->sommets();
        sommetk = NULL;

        while(l != NULL) {
            if(_sommetsMarques->find(l->value) == _sommetsMarques->end()) {
                if(sommetk == NULL)
                    sommetk = l->value;
                else {
                    if(_ppv->getLambda(l->value) <= _ppv->getLambda(sommetk))
                        sommetk = l->value;
                }
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


void PCC::pluscourtchemin(Sommet<VertexData>* sommet) {
    int valeur = _ppv->getLambda(sommet);

    if(valeur == std::numeric_limits<int>::max())
        std::cout << "Il n'existe pas de chemin entre " << start()->cle() << " et " << sommet->cle() << std::endl;
    else {
        std::cout << "PCC de valeur " << valeur << " : ";

        const Sommet<VertexData> *s = sommet;
        while (s != start()) {
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