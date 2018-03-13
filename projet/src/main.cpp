#include <fstream>
#include <file/dotwriter.h>
#include "file/gprparser.h"
#include <view/dfsmetadata.h>

int main(int argc, char** argv) {
    std::ifstream fstream("data.gpr");
    GPRParser parser(fstream);
    parser.load();

    DFS dfs(&parser.graphe(), parser.source());
    dfs.search();

    DFSMetaData* metaData = new DFSMetaData(&dfs);

    DotWriter dw(std::cout);
    dw.writeGraph("g", parser.graphe(), metaData);

    delete metaData;
}