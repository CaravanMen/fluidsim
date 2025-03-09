#include <errorhandler.h>
#include <stdarg.h>
#include <memory.h>
#include <chrono>

void log(_IO_FILE* stream, FGCOLORS colorInt, char* preText, char* string, ...)
{
    va_list args;
    va_start(args, string);
    char* colStr;
    if (colorInt <= 15 && colorInt >= 0)
    {
        colStr = (char*)&colTable[colorInt][0];
    }
    char strBuff0[LOG_MAXSIZE];
    snprintf(strBuff0, LOG_MAXSIZE, "%s%s%s\e[0m\n\0", colStr, preText, string);
    char strBuff1[LOG_MAXSIZE];
    vsnprintf(strBuff1, LOG_MAXSIZE, strBuff0, args);

    fputs(strBuff1, stream);
    va_end(args);
    return;
}