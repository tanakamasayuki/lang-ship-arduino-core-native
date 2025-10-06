#include "Arduino.h"

#include <array>
#include <atomic>
#include <chrono>
#include <mutex>
#include <random>
#include <thread>

namespace {
std::chrono::steady_clock::time_point g_start;
std::mt19937 g_rng{0x1234ABCD};
std::array<uint8_t, 256> g_pin_modes{};
std::array<uint8_t, 256> g_pin_values{};
std::mutex g_pin_mutex;
}

void init(void) {
    g_start = std::chrono::steady_clock::now();
}

void yield(void) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

unsigned long millis(void) {
    auto now = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - g_start);
    return static_cast<unsigned long>(diff.count());
}

unsigned long micros(void) {
    auto now = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(now - g_start);
    return static_cast<unsigned long>(diff.count());
}

void delay(unsigned long ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void delayMicroseconds(unsigned int us) {
    std::this_thread::sleep_for(std::chrono::microseconds(us));
}

void randomSeed(unsigned long seed) {
    if (seed == 0) {
        seed = static_cast<unsigned long>(std::chrono::steady_clock::now().time_since_epoch().count());
    }
    g_rng.seed(seed);
}

long random(long howbig) {
    if (howbig <= 0) {
        return 0;
    }
    std::uniform_int_distribution<long> dist(0, howbig - 1);
    return dist(g_rng);
}

long random(long howsmall, long howbig) {
    if (howsmall >= howbig) {
        return howsmall;
    }
    std::uniform_int_distribution<long> dist(howsmall, howbig - 1);
    return dist(g_rng);
}

void pinMode(uint8_t pin, uint8_t mode) {
    std::lock_guard<std::mutex> lock(g_pin_mutex);
    g_pin_modes[pin] = mode;
}

void digitalWrite(uint8_t pin, uint8_t val) {
    std::lock_guard<std::mutex> lock(g_pin_mutex);
    g_pin_values[pin] = (val != LOW) ? HIGH : LOW;
}

int digitalRead(uint8_t pin) {
    std::lock_guard<std::mutex> lock(g_pin_mutex);
    return g_pin_values[pin] == HIGH ? HIGH : LOW;
}

int analogRead(uint8_t /*pin*/) {
    return 0;
}

void analogWrite(uint8_t /*pin*/, int /*value*/) {
    // Not yet implemented for native target
}

void tone(uint8_t /*pin*/, unsigned int /*frequency*/, unsigned long /*duration*/) {
    // TODO: integrate with audio backend
}

void noTone(uint8_t /*pin*/) {
    // TODO: integrate with audio backend
}

