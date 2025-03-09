#ifndef _STDIO_H
    #include <stdio.h>
#endif
#ifndef _GLIBCXX_IOSTREAM
    #include <iostream>
#endif

#ifndef __ERRORHANDLER_H__
    #include <chrono>
    #define __ERRORHANDLER_H__

    #define TRACE(text, ...) log(stdout, WHITE, "[TRACE]\t", text, ##__VA_ARGS__)
    #define ERROR(text, ...) log(stderr, RED, "[ERROR]\t%s:%d\n\t", text, __FILE__, __LINE__, ##__VA_ARGS__)
    #define WARN(text, ...) log(stdout, YELLOW, "[WARN]\t", text, ##__VA_ARGS__)

    #define ASSERT(expr, success, failure, ...) \
    { \
        if (!(expr)) \
        { \
            log(stderr, BRIGHT_RED, "[CRIT]\tAssertion failed: (%s) at %s:%d in function: %s\n\t", failure, #expr, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); \
            exit(EXIT_FAILURE); \
        }else \
        { \
            log(stdout, GREEN, "[PASS]\t", success, ##__VA_ARGS__); \
        } \
    }
    enum FGCOLORS {
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE,
        GRAY,
        BRIGHT_RED,
        BRIGHT_GREEN,
        BRIGHT_YELLOW,
        BRIGHT_BLUE,
        BRIGHT_MAGENTA,
        BRIGHT_CYAN,
        BRIGHT_WHITE
    };

    const char colTable[16][6] = {
        "\e[30m",
        "\e[31m",
        "\e[32m",
        "\e[33m",
        "\e[34m",
        "\e[35m",
        "\e[36m",
        "\e[37m",
        "\e[90m",
        "\e[91m",
        "\e[92m",
        "\e[93m",
        "\e[94m",
        "\e[95m",
        "\e[96m",
        "\e[97m"
    };
    #define LOG_MAXSIZE 128
    void log(_IO_FILE* stream, FGCOLORS colorInt, char* preText, char* string, ...);
#endif