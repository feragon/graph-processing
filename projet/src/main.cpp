#include <fstream>
#include <file/dotwriter.h>
#include "file/gprparser.h"
#include <iostream>

int main(int argc, char** argv) {
    std::ifstream fstream("data.gpr");
    GPRParser parser(fstream);
    parser.load();

    DotWriter dw(std::cout);
    dw.writeGraph("g", parser.graphe());
}