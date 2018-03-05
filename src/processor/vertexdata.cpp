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
