#pragma once

#include <stdexcept>

class VertexNotFound : public std::runtime_error {
    public:
        VertexNotFound(const char* s) : runtime_error(s) {

        }
};