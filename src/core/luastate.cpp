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

#include "luastate.hpp"
#include "logger.hpp"

USING_JADE_NS

CLuaState * CLuaState::instance = 0;

CLuaState * CLuaState::getInstance()
{
    if (0 == instance) {
        instance = new CLuaState();
    }
    return instance;
}

CLuaState::CLuaState()
{
    L = luaL_newstate();
    luaL_openlibs(L);

    if (luaL_dofile(L, "init.lua")) {
        ERROR("load lua init file failed: %s",
            lua_tostring(L, -1));
    }
}

