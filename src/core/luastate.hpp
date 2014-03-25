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

#ifndef _JADE_LUASTATE_INCLUDE_
#define _JADE_LUASTATE_INCLUDE_

#include "jade.hpp"
#include "singleton.hpp"
#include "logger.hpp"

JADE_NS_BEGIN

class LuaStackBalancer_
{
public:
    LuaStackBalancer_(lua_State *L):L_(L){
        top_ = lua_gettop(L_);
    }
    ~LuaStackBalancer_() {
        lua_settop(L_, top_);
    }
private:
    lua_State * L_;
    int top_;
};

class CLuaState: public TSingleton<CLuaState>
{
    friend TSingleton<CLuaState>;
public:
    template <typename T>
    T to(int index);
    template<>
    const char * to(int index) {
        return lua_tostring(L_, index);
    }
    template<>
    int to(int index) {
        return lua_tointeger(L_, index);
    }

    template <typename T>
    void push(T value);
    template <>
    void push(const char * str) {
        lua_pushstring(L_, str);
    }
    template <>
    void push(int i) {
        lua_pushinteger(L_, i);
    }

    void call(const char * name) {
        LuaStackBalancer_ balancer(L_);
        int msgh = _prepareCall();
        lua_getglobal(L_, name);
        if (0 != lua_pcall(L_, 0, 0, msgh)) {
            ERROR("lua error on call [%s]: %s", name, to<const char *>(-1));
        }
    }

    template <typename A1>
    void call(const char * name, A1 a1) {
        LuaStackBalancer_ balancer(L_);
        int msgh = _prepareCall();
        lua_getglobal(L_, name);
        push<A1>(a1);
        if (0 != lua_pcall(L_, 1, 0, msgh)) {
            ERROR("lua error on call [%s]: %s", name, to<const char *>(-1));
        }
    }

    template <typename A1, typename A2>
    void call(const char * name, A1 a1, A2 a2) {
        LuaStackBalancer_ balancer(L_);
        int msgh = _prepareCall();
        lua_getglobal(L_, name);
        push<A1>(a1);
        push<A2>(a2);
        if (0 != lua_pcall(L_, 2, 0, msgh)) {
            ERROR("lua error on call [%s]: %s", name, to<const char *>(-1));
        }
    }

    template <typename A1, typename A2, typename A3>
    void call(const char * name, A1 a1, A2 a2, A3 a3) {
        LuaStackBalancer_ balancer(L_);
        int msgh = _prepareCall();
        lua_getglobal(L_, name);
        push<A1>(a1);
        push<A2>(a2);
        push<A3>(a3);
        if (0 != lua_pcall(L_, 3, 0, msgh)) {
            ERROR("lua error on call [%s]: %s", name, to<const char *>(-1));
        }
    }

    template <typename A1, typename A2, typename A3, typename A4>
    void call(const char * name, A1 a1, A2 a2, A3 a3, A4 a4) {
        LuaStackBalancer_ balancer(L_);
        int msgh = _prepareCall();
        lua_getglobal(L_, name);
        push<A1>(a1);
        push<A2>(a2);
        push<A3>(a3);
        push<A4>(a4);
        if (0 != lua_pcall(L_, 4, 0, msgh)) {
            ERROR("lua error on call [%s]: %s", name, to<const char *>(-1));
        }
    }

public:
    inline lua_State * state() {
        return L_;
    }

private:
    int _prepareCall() {
        int msgh = lua_gettop(L_);
        lua_getglobal(L_, "debug");
        lua_getfield(L_, -1, "traceback");
        lua_remove(L_, -2);
        return msgh + 1;
    }

private:
    CLuaState();
    ~CLuaState();
private:
    lua_State * L_;
};

JADE_NS_END

#endif

