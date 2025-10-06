#include "Print.h"

#include <cmath>
#include <cstring>

#include "WString.h"

size_t Print::write(const char *str) {
    if (str == nullptr) {
        return 0;
    }
    return write(reinterpret_cast<const uint8_t *>(str), std::strlen(str));
}

size_t Print::write(const uint8_t *buffer, size_t size) {
    size_t n = 0;
    while (size--) {
        n += write(*buffer++);
    }
    return n;
}

size_t Print::print(const String &s) {
    return write(s.c_str());
}

size_t Print::print(const char s[]) {
    return write(s);
}

size_t Print::print(char c) {
    return write(static_cast<uint8_t>(c));
}

size_t Print::print(unsigned char b, int base) {
    return print(static_cast<unsigned long>(b), base);
}

size_t Print::print(int n, int base) {
    return print(static_cast<long>(n), base);
}

size_t Print::print(unsigned int n, int base) {
    return print(static_cast<unsigned long>(n), base);
}

size_t Print::print(long n, int base) {
    if (base == DEC) {
        if (n < 0) {
            int t = print('-');
            return printNumber(static_cast<unsigned long>(-n), DEC) + t;
        }
        return printNumber(static_cast<unsigned long>(n), DEC);
    }
    return printNumber(static_cast<unsigned long>(n), static_cast<uint8_t>(base));
}

size_t Print::print(unsigned long n, int base) {
    return printNumber(n, static_cast<uint8_t>(base));
}

size_t Print::print(double number, int digits) {
    return printFloat(number, static_cast<uint8_t>(digits));
}

size_t Print::print(const Printable &p) {
    return p.printTo(*this);
}

size_t Print::println(void) {
    size_t n = print('\r');
    n += print('\n');
    return n;
}

size_t Print::println(const String &s) {
    size_t n = print(s);
    n += println();
    return n;
}

size_t Print::println(const char s[]) {
    size_t n = print(s);
    n += println();
    return n;
}

size_t Print::println(char c) {
    size_t n = print(c);
    n += println();
    return n;
}

size_t Print::println(unsigned char b, int base) {
    size_t n = print(b, base);
    n += println();
    return n;
}

size_t Print::println(int num, int base) {
    size_t n = print(num, base);
    n += println();
    return n;
}

size_t Print::println(unsigned int num, int base) {
    size_t n = print(num, base);
    n += println();
    return n;
}

size_t Print::println(long num, int base) {
    size_t n = print(num, base);
    n += println();
    return n;
}

size_t Print::println(unsigned long num, int base) {
    size_t n = print(num, base);
    n += println();
    return n;
}

size_t Print::println(double num, int digits) {
    size_t n = print(num, digits);
    n += println();
    return n;
}

size_t Print::println(const Printable &p) {
    size_t n = print(p);
    n += println();
    return n;
}

size_t Print::printNumber(unsigned long n, uint8_t base) {
    if (base < 2) {
        base = DEC;
    }
    char buf[33];
    char *str = &buf[sizeof(buf) - 1];
    *str = '\0';
    do {
        unsigned long digit = n % base;
        *--str = (digit < 10) ? ('0' + digit) : ('A' + digit - 10);
        n /= base;
    } while (n);
    return write(str);
}

size_t Print::printFloat(double number, uint8_t digits) {
    if (std::isnan(number)) {
        return write("nan");
    }
    if (std::isinf(number)) {
        return write("inf");
    }

    size_t n = 0;
    if (number < 0.0) {
        n += write('-');
        number = -number;
    }

    double rounding = 0.5;
    for (uint8_t i = 0; i < digits; ++i) {
        rounding /= 10.0;
    }
    number += rounding;

    unsigned long int_part = static_cast<unsigned long>(number);
    double remainder = number - static_cast<double>(int_part);
    n += printNumber(int_part, DEC);

    if (digits > 0) {
        n += write('.');
    }

    while (digits-- > 0) {
        remainder *= 10.0;
        unsigned int toPrint = static_cast<unsigned int>(remainder);
        n += write(static_cast<uint8_t>('0' + toPrint));
        remainder -= toPrint;
    }

    return n;
}

