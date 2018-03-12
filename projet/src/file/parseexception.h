#pragma once

#include <stdexcept>
#include <gmpxx.h>

class ParseException : public std::runtime_error {
    public:
        ParseException(const char* m) : runtime_error(m) {

        }
};