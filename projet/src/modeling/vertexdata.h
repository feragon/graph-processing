#pragma once

#include <string>
#include <ostream>

class VertexData {
    public:
        VertexData();
        VertexData(int x, int y);

        inline int inf() const;

        inline void setInf(int x);

        inline int sup() const;

        inline void setSup(int y);

        inline bool canWait() const;

        inline void setCanWait(bool canWait);

        friend std::ostream& operator<<(std::ostream& os, const VertexData& data);

    private:
        bool _canWait;
        int _inf;
        int _sup;
};

int VertexData::inf() const {
    return _inf;
}

void VertexData::setInf(int x) {
    _inf = x;
}

int VertexData::sup() const {
    return _sup;
}

void VertexData::setSup(int y) {
    _sup = y;
}

bool VertexData::canWait() const {
    return _canWait;
}

void VertexData::setCanWait(bool canWait) {
    _canWait = canWait;
}