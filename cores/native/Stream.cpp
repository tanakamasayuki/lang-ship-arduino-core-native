#include "Stream.h"

#include "Arduino.h"

#include <cctype>
#include <cmath>

Stream::Stream() = default;

void Stream::setTimeout(unsigned long timeout) {
    timeout_ = timeout;
}

unsigned long Stream::getTimeout() const {
    return timeout_;
}

size_t Stream::readBytes(char *buffer, size_t length) {
    if (buffer == nullptr) {
        return 0;
    }
    size_t index = 0;
    while (index < length) {
        int c = timedRead();
        if (c < 0) {
            break;
        }
        buffer[index++] = static_cast<char>(c);
    }
    return index;
}

size_t Stream::readBytes(uint8_t *buffer, size_t length) {
    return readBytes(reinterpret_cast<char *>(buffer), length);
}

size_t Stream::readBytesUntil(char terminator, char *buffer, size_t length) {
    if (buffer == nullptr || length == 0) {
        return 0;
    }
    size_t index = 0;
    while (index < length) {
        int c = timedRead();
        if (c < 0 || c == terminator) {
            break;
        }
        buffer[index++] = static_cast<char>(c);
    }
    return index;
}

size_t Stream::readBytesUntil(char terminator, uint8_t *buffer, size_t length) {
    return readBytesUntil(terminator, reinterpret_cast<char *>(buffer), length);
}

long Stream::parseInt() {
    bool negative = false;
    long value = 0;
    int c = timedPeek();
    while (c >= 0 && !std::isdigit(c) && c != '-') {
        read();
        c = timedPeek();
    }
    if (c == '-') {
        negative = true;
        read();
    }
    while (true) {
        c = timedPeek();
        if (c < 0 || !std::isdigit(c)) {
            break;
        }
        read();
        value = value * 10 + (c - '0');
    }
    return negative ? -value : value;
}

float Stream::parseFloat() {
    bool negative = false;
    float value = 0.0f;
    float divider = 1.0f;
    bool fraction = false;
    int c = timedPeek();
    while (c >= 0 && !(std::isdigit(c) || c == '-' || c == '.')) {
        read();
        c = timedPeek();
    }
    if (c == '-') {
        negative = true;
        read();
    }
    while (true) {
        c = timedPeek();
        if (c == '.' && !fraction) {
            fraction = true;
            read();
            continue;
        }
        if (c < 0 || !std::isdigit(c)) {
            break;
        }
        read();
        if (fraction) {
            divider *= 10.0f;
            value += (c - '0') / divider;
        } else {
            value = value * 10.0f + (c - '0');
        }
    }
    return negative ? -value : value;
}

int Stream::timedRead() {
    unsigned long start = millis();
    while (millis() - start < timeout_) {
        if (available() > 0) {
            int c = read();
            if (c >= 0) {
                return c;
            }
        }
        yield();
    }
    return -1;
}

int Stream::timedPeek() {
    unsigned long start = millis();
    while (millis() - start < timeout_) {
        int c = peek();
        if (c >= 0) {
            return c;
        }
        if (available() > 0) {
            continue;
        }
        yield();
    }
    return -1;
}

