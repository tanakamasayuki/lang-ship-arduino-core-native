#include "HardwareSerial.h"

#include <iostream>
#include <mutex>

HardwareSerial Serial;

HardwareSerial::HardwareSerial() = default;

void HardwareSerial::begin(unsigned long baud) {
    std::lock_guard<std::mutex> lock(mutex_);
    baudRate_ = baud;
    (void)baudRate_;
}

void HardwareSerial::end() {
    std::lock_guard<std::mutex> lock(mutex_);
    std::cout.flush();
}

int HardwareSerial::available() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (peeked_ >= 0) {
        return 1;
    }
    std::streamsize count = std::cin.rdbuf()->in_avail();
    return count > 0 ? static_cast<int>(count) : 0;
}

int HardwareSerial::read() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (peeked_ >= 0) {
        int value = peeked_;
        peeked_ = -1;
        return value;
    }
    int value = std::cin.get();
    if (value == EOF) {
        return -1;
    }
    return value & 0xFF;
}

int HardwareSerial::peek() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (peeked_ >= 0) {
        return peeked_;
    }
    int value = std::cin.peek();
    if (value == EOF) {
        return -1;
    }
    peeked_ = value & 0xFF;
    return peeked_;
}

void HardwareSerial::flush() {
    std::lock_guard<std::mutex> lock(mutex_);
    std::cout.flush();
}

size_t HardwareSerial::write(uint8_t b) {
    std::lock_guard<std::mutex> lock(mutex_);
    std::cout.put(static_cast<char>(b));
    if (b == '\n') {
        std::cout.flush();
    }
    return 1;
}

size_t HardwareSerial::write(const uint8_t *buffer, size_t size) {
    if (buffer == nullptr) {
        return 0;
    }
    size_t total = 0;
    while (total < size) {
        total += write(buffer[total]);
    }
    return total;
}

