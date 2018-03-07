#pragma once

#include <stdexcept>
#include <gmpxx.h>

class VertexNotFound : public std::runtime_error {
    public:
        VertexNotFound(const char* s) : runtime_error(s) {

        }
};