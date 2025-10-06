#pragma once

#include <mutex>

#include "Stream.h"

class HardwareSerial : public Stream {
public:
    HardwareSerial();

    void begin(unsigned long baud);
    void end();

    int available() override;
    int read() override;
    int peek() override;
    void flush() override;

    size_t write(uint8_t b) override;
    size_t write(const uint8_t *buffer, size_t size) override;

private:
    unsigned long baudRate_{115200};
    int peeked_{-1};
    std::mutex mutex_;
};

extern HardwareSerial Serial;

