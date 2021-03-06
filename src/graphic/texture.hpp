//========================================================================
// jade 0.1
//------------------------------------------------------------------------
// copyright (c) 2014 jie meng <inmouse@gmail.com>
//
// this software is provided 'as-is', without any express or implied
// warranty. in no event will the authors be held liable for any damages
// arising from the use of this software.
//
// permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. the origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. if you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. this notice may not be removed or altered from any source
//    distribution.
//
//========================================================================

#ifndef _JADE_TEXTURE_INCLUDE_
#define _JADE_TEXTURE_INCLUDE_

#include "jade.hpp"
#include "globject.hpp"

JADE_NS_BEGIN

class CTexture: public CGLObject
{
public:
    CTexture();
    virtual ~CTexture();
};

JADE_NS_END

#endif

