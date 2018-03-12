#include <fstream>
#include "file/gprparser.h"

int main(int argc, char** argv) {
    std::ifstream fstream("data.gpr");
    GPRParser parser(fstream);
    parser.load();
}