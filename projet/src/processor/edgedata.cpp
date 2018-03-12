#include "edgedata.h"
#include "negativevaluation.h"

EdgeData::EdgeData(int cost, int time) {
    if(cost < 0 || time < 0) {
        throw NegativeValuation("Le coût ou le temps est négatif");
    }
    _cost = cost;
    _time = time;
}
