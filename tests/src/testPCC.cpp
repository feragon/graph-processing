#include <catch.hpp>
#include <modeling/vertexdata.h>
#include <graph/graphe.h>
#include <modeling/edgedata.h>
#include <file/gprparser.h>
#include <algorithm/pcc.h>
#include <fstream>


TEST_CASE("testPCC") {

    /*
    std::ifstream fstream("data_VRPTW_10_3_2_4.gpr");
    GPRParser gprp(fstream);
    gprp.load();
     */

    Graphe<EdgeData, VertexData> graphe;
    auto x1 = graphe.creerSommet("x1", VertexData());
    auto x2 = graphe.creerSommet("x2", VertexData());
    auto x3 = graphe.creerSommet("x3", VertexData());
    auto x4 = graphe.creerSommet("x4", VertexData());
    auto x5 = graphe.creerSommet("x5", VertexData());
    auto x6 = graphe.creerSommet("x6", VertexData());
    auto x7 = graphe.creerSommet("x7", VertexData());

    graphe.creeArete("arc1", EdgeData(2,0), x1, x2);
    graphe.creeArete("arc2", EdgeData(7,0), x1, x3);
    graphe.creeArete("arc3", EdgeData(2,0), x2, x4);
    graphe.creeArete("arc4", EdgeData(4,0), x2, x5);
    graphe.creeArete("arc5", EdgeData(3,0), x3, x5);
    graphe.creeArete("arc6", EdgeData(1,0), x4, x3);
    graphe.creeArete("arc7", EdgeData(8,0), x4, x6);
    graphe.creeArete("arc8", EdgeData(2,0), x5, x6);

    PCC *pcc = new PCC(&graphe, x1, cout);
    pcc->search();
    pcc->pluscourtchemin(x6);
}