#include "WString.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include <sstream>
#include <string>

namespace {
constexpr const char *kDigits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

std::string toBaseStringUnsigned(unsigned long value, int base) {
    if (base < 2 || base > 36) {
        base = 10;
    }
    std::string result;
    do {
        unsigned long digit = value % static_cast<unsigned long>(base);
        result.push_back(kDigits[digit]);
        value /= static_cast<unsigned long>(base);
    } while (value != 0);
    std::reverse(result.begin(), result.end());
    if (result.empty()) {
        result = "0";
    }
    return result;
}

std::string toBaseStringSigned(long value, int base) {
    if (base < 2 || base > 36) {
        base = 10;
    }
    bool negative = value < 0;
    unsigned long magnitude = negative ? static_cast<unsigned long>(-value) : static_cast<unsigned long>(value);
    std::string out = toBaseStringUnsigned(magnitude, base);
    if (negative) {
        out.insert(out.begin(), '-');
    }
    return out;
}

std::string toFloatString(double value, unsigned char decimalPlaces) {
    std::ostringstream oss;
    if (!std::isfinite(value)) {
        return value > 0 ? "inf" : "-inf";
    }
    oss.setf(std::ios::fixed);
    oss << std::setprecision(decimalPlaces) << value;
    return oss.str();
}

} // namespace

String::String() = default;

String::String(const String &other) = default;

String::String(String &&other) noexcept = default;

String::String(const char *cstr) : buffer_(cstr ? cstr : "") {}

String::String(const std::string &str) : buffer_(str) {}

String::String(char c) : buffer_(1, c) {}

String::String(int value, int base) : buffer_(toBaseStringSigned(static_cast<long>(value), base)) {}

String::String(unsigned int value, int base) : buffer_(toBaseStringUnsigned(static_cast<unsigned long>(value), base)) {}

String::String(long value, int base) : buffer_(toBaseStringSigned(value, base)) {}

String::String(unsigned long value, int base) : buffer_(toBaseStringUnsigned(value, base)) {}

String::String(float value, unsigned char decimalPlaces) : buffer_(toFloatString(static_cast<double>(value), decimalPlaces)) {}

String::String(double value, unsigned char decimalPlaces) : buffer_(toFloatString(value, decimalPlaces)) {}

String &String::operator=(const String &other) = default;

String &String::operator=(String &&other) noexcept = default;

String &String::operator=(const char *cstr) {
    buffer_ = cstr ? cstr : "";
    return *this;
}

String &String::operator+=(const String &other) {
    buffer_ += other.buffer_;
    return *this;
}

String &String::operator+=(const char *cstr) {
    buffer_ += (cstr ? cstr : "");
    return *this;
}

String &String::operator+=(char c) {
    buffer_.push_back(c);
    return *this;
}

String String::operator+(const String &rhs) const {
    String tmp(*this);
    tmp += rhs;
    return tmp;
}

String String::operator+(const char *rhs) const {
    String tmp(*this);
    tmp += rhs;
    return tmp;
}

bool String::operator==(const String &rhs) const {
    return buffer_ == rhs.buffer_;
}

bool String::operator!=(const String &rhs) const {
    return !(*this == rhs);
}

char String::charAt(unsigned int index) const {
    if (index >= buffer_.size()) {
        return '\0';
    }
    return buffer_[index];
}

void String::setCharAt(unsigned int index, char c) {
    if (index < buffer_.size()) {
        buffer_[index] = c;
    }
}

const char *String::c_str() const {
    return buffer_.c_str();
}

char *String::begin() {
    return buffer_.data();
}

char *String::end() {
    return buffer_.data() + buffer_.size();
}

const char *String::begin() const {
    return buffer_.c_str();
}

const char *String::end() const {
    return buffer_.c_str() + buffer_.size();
}

unsigned int String::length() const {
    return static_cast<unsigned int>(buffer_.size());
}

bool String::isEmpty() const {
    return buffer_.empty();
}

int String::compareTo(const String &other) const {
    return buffer_.compare(other.buffer_);
}

bool String::equals(const String &other) const {
    return buffer_ == other.buffer_;
}

bool String::equalsIgnoreCase(const String &other) const {
    if (buffer_.size() != other.buffer_.size()) {
        return false;
    }
    for (size_t i = 0; i < buffer_.size(); ++i) {
        if (std::tolower(static_cast<unsigned char>(buffer_[i])) !=
            std::tolower(static_cast<unsigned char>(other.buffer_[i]))) {
            return false;
        }
    }
    return true;
}

String String::substring(unsigned int beginIndex, unsigned int endIndex) const {
    if (beginIndex >= buffer_.size() || beginIndex >= endIndex) {
        return String();
    }
    endIndex = std::min<unsigned int>(endIndex, static_cast<unsigned int>(buffer_.size()));
    return String(buffer_.substr(beginIndex, endIndex - beginIndex));
}

String String::substring(unsigned int beginIndex) const {
    if (beginIndex >= buffer_.size()) {
        return String();
    }
    return String(buffer_.substr(beginIndex));
}

long String::toInt() const {
    return std::strtol(buffer_.c_str(), nullptr, 10);
}

float String::toFloat() const {
    return std::strtof(buffer_.c_str(), nullptr);
}

double String::toDouble() const {
    return std::strtod(buffer_.c_str(), nullptr);
}

void String::clear() {
    buffer_.clear();
}

String operator+(const char *lhs, const String &rhs) {
    String result(lhs);
    result += rhs;
    return result;
}

