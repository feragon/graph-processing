#pragma once

class EdgeData {
    public:
        EdgeData(int cost = 0, int time = 0);

        inline int cost() const;

        inline void setCost(int cost);

        inline int time() const;

        inline void setTime(int time);

    private:
        int _cost;
        int _time;
};

int EdgeData::cost() const {
    return _cost;
}

void EdgeData::setCost(int cost) {
    _cost = cost;
}

int EdgeData::time() const {
    return _time;
}

void EdgeData::setTime(int time) {
    _time = time;
}