#pragma once

#include <stdexcept>

class NegativeValuation : public std::runtime_error {
    public:
        NegativeValuation(const char* m) : runtime_error(m) {

        }
};