#pragma once

#include <string>

class VertexData {
    public:
        VertexData();
        VertexData(int x, int y);

        inline int x() const;

        inline void setX(int x);

        inline int y() const;

        inline void setY(int y);

        inline bool canWait() const;

        inline void setCanWait(bool canWait);

    private:
        bool _canWait;
        int _inf;
        int _sup;
};

int VertexData::x() const {
    return _inf;
}

void VertexData::setX(int x) {
    _inf = x;
}

int VertexData::y() const {
    return _sup;
}

void VertexData::setY(int y) {
    _sup = y;
}

bool VertexData::canWait() const {
    return _canWait;
}

void VertexData::setCanWait(bool canWait) {
    _canWait = canWait;
}
