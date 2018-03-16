#pragma once

#include <string>
#include <ostream>

class VertexData {
    public:
        VertexData();
        VertexData(int inf, int sup);

        inline int inf() const;

        inline void setInf(int inf);

        inline int sup() const;

        inline void setSup(int sup);

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

void VertexData::setInf(int inf) {
    _inf = inf;
}

int VertexData::sup() const {
    return _sup;
}

void VertexData::setSup(int sup) {
    _sup = sup;
}

bool VertexData::canWait() const {
    return _canWait;
}

void VertexData::setCanWait(bool canWait) {
    _canWait = canWait;
}