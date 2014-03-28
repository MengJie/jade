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

#ifndef _JADE_OBJECT_INCLUDE_
#define _JADE_OBJECT_INCLUDE_

#include "jade.hpp"

JADE_NS_BEGIN

class CAutoReleasePool;

class CObject
{
    friend CAutoReleasePool;
public:
    // two phase object initialize.
    // 1. set the initialize parameter in the constructor
    // 2. do the actual initialize work in the init method, and
    //    return the result.
    CObject();
    virtual ~CObject();
    virtual bool init() { return true; }

    void retain();
    void release();
    void autorelease();

private:
    int reference_;
    bool managed_;
};

JADE_NS_END

#endif

