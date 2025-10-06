#pragma once

#include <stddef.h>
#include <stdint.h>

#include "Print.h"

unsigned long millis(void);

class Stream : public Print {
public:
    Stream();
    void setTimeout(unsigned long timeout); // milliseconds
    unsigned long getTimeout() const;

    virtual int available() = 0;
    virtual int read() = 0;
    virtual int peek() = 0;
    virtual void flush() = 0;

    size_t readBytes(char *buffer, size_t length);
    size_t readBytes(uint8_t *buffer, size_t length);
    size_t readBytesUntil(char terminator, char *buffer, size_t length);
    size_t readBytesUntil(char terminator, uint8_t *buffer, size_t length);

    long parseInt();
    float parseFloat();

protected:
    int timedRead();
    int timedPeek();

private:
    unsigned long timeout_{1000};
};

