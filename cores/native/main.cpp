#include "Arduino.h"

#include <exception>
#include <iostream>

extern void setup(void);
extern void loop(void);

#ifndef __has_include
#define __has_include(x) 0
#endif

#if __has_include(<M5GFX.h>)
#define LANGSHIP_HAS_LGFX 1
#include <M5GFX.h>
#elif __has_include(<LovyanGFX.hpp>)
#define LANGSHIP_HAS_LGFX 1
#include <LovyanGFX.hpp>
#else
#define LANGSHIP_HAS_LGFX 0
#endif

namespace {
bool g_keep_running = true;
}

extern "C" void langship_native_request_quit() {
    g_keep_running = false;
}

#if LANGSHIP_HAS_LGFX

namespace {

__attribute__((weak))
int user_func(bool *running) {
    init();
    initVariant();

    try {
        setup();
    } catch (const std::exception &ex) {
        std::cerr << "Exception in setup(): " << ex.what() << std::endl;
        g_keep_running = false;
        return 1;
    } catch (...) {
        std::cerr << "Unknown exception in setup()" << std::endl;
        g_keep_running = false;
        return 1;
    }

    while (*running && g_keep_running) {
        try {
            loop();
        } catch (const std::exception &ex) {
            std::cerr << "Exception in loop(): " << ex.what() << std::endl;
            g_keep_running = false;
            break;
        } catch (...) {
            std::cerr << "Unknown exception in loop()" << std::endl;
            g_keep_running = false;
            break;
        }
        yield();
    }

    return 0;
}

}  // namespace

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;
    g_keep_running = true;

    // 16 ms slow execution keeps redraws smooth while allowing breakpoints.
    return lgfx::Panel_sdl::main(user_func, 16);
}

#else  // LANGSHIP_HAS_LGFX == 0

#include <SDL.h>

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    init();
    initVariant();

    try {
        setup();
    } catch (const std::exception &ex) {
        std::cerr << "Exception in setup(): " << ex.what() << std::endl;
        g_keep_running = false;
    } catch (...) {
        std::cerr << "Unknown exception in setup()" << std::endl;
        g_keep_running = false;
    }

    while (g_keep_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                g_keep_running = false;
            }
        }

        try {
            loop();
        } catch (const std::exception &ex) {
            std::cerr << "Exception in loop(): " << ex.what() << std::endl;
            break;
        } catch (...) {
            std::cerr << "Unknown exception in loop()" << std::endl;
            break;
        }

        yield();
    }

    SDL_Quit();
    return 0;
}

#endif  // LANGSHIP_HAS_LGFX
