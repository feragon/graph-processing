#include "vertexdata.h"

VertexData::VertexData(int x, int y) {
    _inf = x;
    _sup = y;
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
