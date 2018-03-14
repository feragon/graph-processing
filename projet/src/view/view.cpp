#include "view.h"

View::View(std::ostream& out, std::istream& in, CLI* cli) :
    _out(out),
    _in(in) {
    _cli = cli;
}
