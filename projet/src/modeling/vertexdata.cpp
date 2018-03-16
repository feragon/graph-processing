#include "vertexdata.h"

VertexData::VertexData(int inf, int sup) {
    _inf = inf;
    _sup = sup;
    _canWait = true;
}

VertexData::VertexData() {
    _canWait = false;
    _inf = 0;
    _sup = 0;
}

std::ostream& operator<<(std::ostream& os, const VertexData& data) {
    os << "VertexData(_canWait: " << data._canWait << " _inf: " << data._inf << " _sup: " << data._sup << ")";
    return os;
}
