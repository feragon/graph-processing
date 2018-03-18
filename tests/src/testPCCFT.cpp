#include <catch.hpp>
#include <modeling/vertexdata.h>
#include <graph/graphe.h>
#include <modeling/edgedata.h>
#include <file/gprparser.h>
#include <algorithm/pccft.h>
#include <fstream>


TEST_CASE("testPCCFT") {

    std::cout << std::endl << "=== testPCCFT" << std::endl;


    /* === Exercice 5.1 du TD === */

    Graphe<EdgeData, VertexData> graphe;

    auto x0 = graphe.creerSommet("x0", VertexData());
    auto x1 = graphe.creerSommet("x1", VertexData());
    auto x2 = graphe.creerSommet("x2", VertexData());
    auto x3 = graphe.creerSommet("x3", VertexData());
    auto x4 = graphe.creerSommet("x4", VertexData());
    auto x5 = graphe.creerSommet("x5", VertexData());
    auto x6 = graphe.creerSommet("x6", VertexData());
    auto x7 = graphe.creerSommet("x7", VertexData());
    auto x8 = graphe.creerSommet("x8", VertexData());
    auto x9 = graphe.creerSommet("x9", VertexData());

    graphe.creeArete("arc1", EdgeData(3,2), x0, x1);
    graphe.creeArete("arc2", EdgeData(3,1), x0, x2);
    graphe.creeArete("arc3", EdgeData(1,4), x0, x3);
    graphe.creeArete("arc4", EdgeData(5,2), x1, x4);
    graphe.creeArete("arc5", EdgeData(2,4), x1, x7);
    graphe.creeArete("arc6", EdgeData(5,4), x2, x4);
    graphe.creeArete("arc7", EdgeData(2,3), x2, x5);
    graphe.creeArete("arc8", EdgeData(3,4), x3, x5);
    graphe.creeArete("arc9", EdgeData(5,1), x3, x7);
    graphe.creeArete("arc10", EdgeData(3,2), x4, x6);
    graphe.creeArete("arc11", EdgeData(4,4), x5, x6);
    graphe.creeArete("arc12", EdgeData(2,2), x5, x7);
    graphe.creeArete("arc13", EdgeData(3,3), x5, x8);
    graphe.creeArete("arc14", EdgeData(4,1), x6, x9);
    graphe.creeArete("arc15", EdgeData(6,5), x7, x9);
    graphe.creeArete("arc16", EdgeData(3,3), x8, x9);


    PCCFT *pccft = new PCCFT(&graphe);
    pccft->begin(x0);

    pccft->meilleurChemin(x9, PCCFT::temps);
    pccft->meilleurChemin(x9, PCCFT::cout);
    pccft->meilleurChemin(x9, PCCFT::cout, 0, 12);
    delete pccft;
}
