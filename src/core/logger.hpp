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

#ifndef _JADE_LOGGER_INCLUDE_
#define _JADE_LOGGER_INCLUDE_

#include "jade.hpp"
#include "singleton.hpp"

JADE_NS_BEGIN

class CLogger: public TSingleton<CLogger>
{
    friend TSingleton<CLogger>;
public:
    void debug(const char * fmt, ...);
    void info(const char * fmt, ...);
    void warn(const char * fmt, ...);
    void error(const char * fmt, ...);

private:
    CLogger();
    ~CLogger();
    void flush();

private:
    static const int BUF_SIZE;
    static char buffer_[];
};

#define DEBUG(fmt, ...) CLogger::instance().debug(fmt, ##__VA_ARGS__)
#define INFO(fmt, ...)  CLogger::instance().info(fmt, ##__VA_ARGS__)
#define WARN(fmt, ...)  CLogger::instance().warn(fmt, ##__VA_ARGS__)
#define ERROR(fmt, ...) CLogger::instance().error(fmt, ##__VA_ARGS__)

JADE_NS_END

#endif

