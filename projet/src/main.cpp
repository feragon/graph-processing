#include <fstream>
#include <file/dotwriter.h>
#include "file/gprparser.h"
#include <view/dfsmetadata.h>

int main(int argc, char** argv) {
    std::ifstream fstream("data.gpr");
    GPRParser parser(fstream);
    parser.load();

    ModelingGraph g;
    auto s0 = g.creerSommet("s0", VertexData());
    auto s1 = g.creerSommet("s1", VertexData());
    auto s2 = g.creerSommet("s2", VertexData());
    auto s3 = g.creerSommet("s3", VertexData());
    auto s4 = g.creerSommet("s4", VertexData());
    auto s5 = g.creerSommet("s5", VertexData());
    auto s6 = g.creerSommet("s6", VertexData());

    g.creeArete("a1", EdgeData(), s0, s1);
    g.creeArete("a2", EdgeData(), s0, s2);
    g.creeArete("a3", EdgeData(), s1, s3);
    g.creeArete("a4", EdgeData(), s2, s3);
    g.creeArete("a5", EdgeData(), s4, s5);
    g.creeArete("a6", EdgeData(), s5, s6);
    g.creeArete("a7", EdgeData(), s6, s4);

    DFS dfs(&g, s0);
    dfs.search();

    DFSMetaData* metaData = new DFSMetaData(&dfs);

    DotWriter dw(std::cout);
    dw.writeGraph("g", g, metaData);

    delete metaData;
}