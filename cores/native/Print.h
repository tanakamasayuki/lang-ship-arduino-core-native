#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

#include "Printable.h"

class String;

enum : uint8_t {
    DEC = 10,
    HEX = 16,
    OCT = 8,
    BIN = 2
};

class Print {
public:
    virtual ~Print() = default;

    size_t write(const char *str);
    virtual size_t write(uint8_t b) = 0;
    virtual size_t write(const uint8_t *buffer, size_t size);

    size_t print(const String &s);
    size_t print(const char s[]);
    size_t print(char c);
    size_t print(unsigned char b, int base = DEC);
    size_t print(int n, int base = DEC);
    size_t print(unsigned int n, int base = DEC);
    size_t print(long n, int base = DEC);
    size_t print(unsigned long n, int base = DEC);
    size_t print(double n, int digits = 2);
    size_t print(const Printable &p);

    size_t println(void);
    size_t println(const String &s);
    size_t println(const char s[]);
    size_t println(char c);
    size_t println(unsigned char b, int base = DEC);
    size_t println(int num, int base = DEC);
    size_t println(unsigned int num, int base = DEC);
    size_t println(long num, int base = DEC);
    size_t println(unsigned long num, int base = DEC);
    size_t println(double num, int digits = 2);
    size_t println(const Printable &p);

protected:
    size_t printNumber(unsigned long n, uint8_t base);
    size_t printFloat(double number, uint8_t digits);
};

