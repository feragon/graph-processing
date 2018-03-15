#pragma once

#include <graph/liste.h>
#include <graph/graphe.h>
#include <graph/sommet.h>
#include <modeling/vertexdata.h>
#include <modeling/edgedata.h>

class Etiquette {
private:
    const Sommet<VertexData>* _sommet;
    Etiquette* _predecesseur;
    int _cost;
    int _time;

public:
    Etiquette(const Sommet<VertexData>* sommet, Etiquette* predecesseur, int cout, int duree);

    const Sommet<VertexData>* sommet();

    Etiquette* predecesseur();

    int cost();

    int time();
};
