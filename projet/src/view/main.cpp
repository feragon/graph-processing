#include <iostream>
#include "cli.h"

int main(int argc, char** argv) {
    CLI cli(std::cout, std::cin);
    cli.start();
}