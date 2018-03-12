#include <sstream>
#include "identifiable.h"

Identifiable::Identifiable(const std::string& cle) {
    _cle = cle;
}

Identifiable::operator std::string() const {
    std::ostringstream oss;
    oss << "Identifiable(" << _cle << ")";
    return oss.str();
}

std::ostream& operator<<(std::ostream& o, const Identifiable& i) {
    o << (std::string) i;
    return o;
}
