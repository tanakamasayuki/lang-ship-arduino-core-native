#pragma once

#include <string>
#include <utility>
#include <stddef.h>

class String {
public:
    String();
    String(const String &other);
    String(String &&other) noexcept;
    String(const char *cstr);
    String(const std::string &str);
    String(char c);
    String(int value, int base = 10);
    String(unsigned int value, int base = 10);
    String(long value, int base = 10);
    String(unsigned long value, int base = 10);
    String(float value, unsigned char decimalPlaces = 2);
    String(double value, unsigned char decimalPlaces = 2);
    ~String() = default;

    String &operator=(const String &other);
    String &operator=(String &&other) noexcept;
    String &operator=(const char *cstr);

    String &operator+=(const String &other);
    String &operator+=(const char *cstr);
    String &operator+=(char c);

    String operator+(const String &rhs) const;
    String operator+(const char *rhs) const;

    bool operator==(const String &rhs) const;
    bool operator!=(const String &rhs) const;

    char charAt(unsigned int index) const;
    void setCharAt(unsigned int index, char c);
    const char *c_str() const;
    char *begin();
    char *end();
    const char *begin() const;
    const char *end() const;
    unsigned int length() const;
    bool isEmpty() const;

    int compareTo(const String &other) const;
    bool equals(const String &other) const;
    bool equalsIgnoreCase(const String &other) const;

    String substring(unsigned int beginIndex, unsigned int endIndex) const;
    String substring(unsigned int beginIndex) const;

    long toInt() const;
    float toFloat() const;
    double toDouble() const;

    void clear();

    const std::string &std() const { return buffer_; }

private:
    std::string buffer_;
};

String operator+(const char *lhs, const String &rhs);

