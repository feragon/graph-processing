#include <catch.hpp>
#include <modeling/vertexdata.h>
#include <graph/graphe.h>
#include <modeling/edgedata.h>
#include <file/gprparser.h>
#include <algorithm/pccft.h>
#include <fstream>


TEST_CASE("testPCCFT") {

    std::cout << std::endl << "=== testPCCFT" << std::endl;

    std::ifstream fstream("data/data_VRPTW_20.gpr");
    GPRParser gprp(fstream);
    gprp.load();


    PCCFT *pccft = new PCCFT(&gprp.graphe());
    pccft->begin(gprp.source());


    pccft->meilleurChemin(gprp.puits(), cout, 0, 30);
    // Jouer sur la fenetre pour voir toutes les possibilités
    // 3 PCC pour le cout : temps = 9, 12, 19
}