#include <catch.hpp>
#include <modeling/vertexdata.h>
#include <graph/graphe.h>
#include <modeling/edgedata.h>
#include <file/gprparser.h>
#include <algorithm/pcc.h>
#include <fstream>


TEST_CASE("testPCCArbreDeuxBranches") {

    std::cout << std::endl << "=== testPCCArbreDeuxBranches" << std::endl;

    Graphe<EdgeData, VertexData> graphe;
    auto x1 = graphe.creerSommet("x1", VertexData());
    auto x2 = graphe.creerSommet("x2", VertexData());
    auto x3 = graphe.creerSommet("x3", VertexData());
    auto x4 = graphe.creerSommet("x4", VertexData());
    auto x5 = graphe.creerSommet("x5", VertexData());

    graphe.creeArete("arc1", EdgeData(2,0), x1, x2);
    graphe.creeArete("arc2", EdgeData(3,0), x2, x3);
    graphe.creeArete("arc3", EdgeData(5,0), x1, x4);
    graphe.creeArete("arc4", EdgeData(1,0), x4, x5);

    PCC *pcc = new PCC(&graphe);
    pcc->begin(x1, cout);
    pcc->plusCourtChemin(x3);
    pcc->plusCourtChemin(x5);

    REQUIRE(pcc->explored(x3));
    REQUIRE(pcc->explored(x5));

}