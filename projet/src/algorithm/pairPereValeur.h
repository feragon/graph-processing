#pragma once

#include <graph/liste.h>
#include <graph/graphe.h>
#include <graph/sommet.h>
#include <modeling/vertexdata.h>
#include <modeling/edgedata.h>

struct PereLambda {
    const Sommet<VertexData>* sommet;
    const Sommet<VertexData>* pere;
    int lamba;
};

class pairPereValeur {
private:
    Liste<PereLambda>* liste;
public:
    pairPereValeur(const Graphe<EdgeData, VertexData> *graphe, const Sommet<VertexData>* source);

    /**
     * @param sommet Sommet de fin du chemin
     * @return int Longueur du chemin jusqu'à sommet
     */
    int getLambda(const Sommet<VertexData>* sommet);

    /**
     * @param sommet Sommet de fin du chemin
     * @return Sommet<VertexData>* Père de sommet
     */
    const Sommet<VertexData>* getPere(const Sommet<VertexData>* sommet);

    /**
     * @param sommet Sommet de fin du chemin
     * @param lambda Longueur du chemin jusqu'à sommet
     */
    void setLambda(const Sommet<VertexData>* sommet, int lambda);

    /**
     * @param sommet Sommet de fin du chemin
     * @param pere Père de sommet
     */
    void setPere(const Sommet<VertexData>* sommet, const Sommet<VertexData>* pere);
};

