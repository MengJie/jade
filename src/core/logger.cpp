//========================================================================
// JADE 0.1
//------------------------------------------------------------------------
// Copyright (c) 2014 Jie Meng <inmouse@gmail.com>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================

#include "logger.hpp"

#include <stdlib.h>
#include <stdio.h>

USING_JADE_NS

const int CLogger::BUF_SIZE = 4096;
char CLogger::buffer_[BUF_SIZE];

CLogger::CLogger()
{
}

CLogger::~CLogger()
{
}

void
CLogger::debug(const char * fmt, ...)
{
    int writed = 0;

    writed += _snprintf_s(buffer_ + writed, BUF_SIZE - writed,
            _TRUNCATE, "[DEBUG] ");

    va_list argp;
    va_start(argp, fmt);
    writed += vsnprintf(buffer_ + writed, BUF_SIZE - writed,
            fmt, argp);
    va_end(argp);

    flush();
}

void CLogger::info(const char * fmt, ...)
{
    int writed = 0;

    writed += _snprintf_s(buffer_ + writed, BUF_SIZE - writed,
            _TRUNCATE, "[INFO] ");

    va_list argp;
    va_start(argp, fmt);
    writed += vsnprintf(buffer_ + writed, BUF_SIZE - writed,
            fmt, argp);
    va_end(argp);

    flush();
}

void
CLogger::warn(const char * fmt, ...)
{
    int writed = 0;

    writed += _snprintf_s(buffer_ + writed, BUF_SIZE - writed,
            _TRUNCATE, "[WARN] ");

    va_list argp;
    va_start(argp, fmt);
    writed += vsnprintf(buffer_ + writed, BUF_SIZE - writed,
            fmt, argp);
    va_end(argp);

    flush();
}

void
CLogger::error(const char * fmt, ...)
{
    int writed = 0;

    writed += _snprintf_s(buffer_ + writed, BUF_SIZE - writed,
            _TRUNCATE, "[ERROR] ");

    va_list argp;
    va_start(argp, fmt);
    writed += vsnprintf(buffer_ + writed, BUF_SIZE - writed,
            fmt, argp);
    va_end(argp);

    flush();
}

void
CLogger::flush()
{
    fputs(buffer_, stderr);
}

