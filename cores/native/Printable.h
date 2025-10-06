#pragma once

#include <stddef.h>

class Print;

class Printable {
public:
    virtual ~Printable() = default;
    virtual size_t printTo(Print &p) const = 0;
};

