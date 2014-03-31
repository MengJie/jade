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

template<typename T>
struct TLuaClassTraits {
    static string className_;
    static void push(lua_State *, T);
    static T to(lua_State *, int);
};
template<typename T> string TLuaClassTraits<T>::className_;

template<typename T>
struct TLuaClassTraits<T*> {
    static void push(lua_State *L, T* obj) {
        string & name = TLuaClassTraits<T>::className_;
        T** a = static_cast<T**>(lua_newuserdata(L_, sizeof(T*)));
        *a = obj;
        luaL_getmetatable(L, name.c_str());
        lua_setmetatable(L, -2);
        // when a object pointer push into lua state, a reference must be kept
        // otherwise, this object will be released while gc.
        obj->retain();
    }
    static T* to(lua_State *L, int index) {
        string & name = TLuaClassTraits<T>::className_;
        T** a = static_cast<T**>(luaL_checkudata(L, -1, name.c_str()));
        T* obj = *a;
        return obj;
    }
};
template<>
struct TLuaClassTraits<const char*> {
    static void push(lua_State *L, const char * str) {
        lua_pushstring(L, str);
    }
    static const char * to(lua_State *L, int index) {
        return lua_tostring(L, index);
    }
};
template<>
struct TLuaClassTraits<int> {
    static void push(lua_State *L, int i) {
        lua_pushinteger(L, i);
    }
    static int to(lua_State *L, int index) {
        return lua_tointeger(L, index);
    }
};
template<>
struct TLuaClassTraits<unsigned int> {
    static void push(lua_State *L, unsigned int i) {
        lua_pushinteger(L, i);
    }
    static unsigned int to(lua_State *L, int index) {
        return lua_tointeger(L, index);
    }
};
template<>
struct TLuaClassTraits<bool> {
    static void push(lua_State *L, bool b) {
        lua_pushboolean(L, b);
    }
    static bool to(lua_State *L, int index) {
        return lua_toboolean(L, index) != 0;
    }
};
template<>
struct TLuaClassTraits<float> {
    static void push(lua_State *L, float f) {
        lua_pushnumber(L, f);
    }
    static float to(lua_State *L, int index) {
        return (float)lua_tonumber(L, index);
    }
};

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

#define LUA_CALL_BEGIN \
        LuaStackBalancer_ balancer(L_); \
        int msgh = _prepareCall(); \
        lua_getglobal(L_, name);

#define LUA_CALL_END \
        if (0 != lua_pcall(L_, 0, 0, msgh)) { \
            ERROR("lua error on call [%s]: %s\n", name, lua_tostring(L_, -1)); \
        }


class CLuaState: public TSingleton<CLuaState>
{
    friend TSingleton<CLuaState>;
public:
    void call(const char * name) {
        LUA_CALL_BEGIN
        LUA_CALL_END
    }

    template <typename A1>
    void call(const char * name, A1 a1) {
        LUA_CALL_BEGIN
        TLuaClassTraits<A1>::push(L_, a1);
        LUA_CALL_END
    }

    template <typename A1, typename A2>
    void call(const char * name, A1 a1, A2 a2) {
        LUA_CALL_BEGIN
        TLuaClassTraits<A1>::push(L_, a1);
        TLuaClassTraits<A2>::push(L_, a2);
        LUA_CALL_END
    }

    template <typename A1, typename A2, typename A3>
    void call(const char * name, A1 a1, A2 a2, A3 a3) {
        LUA_CALL_BEGIN
        TLuaClassTraits<A1>::push(L_, a1);
        TLuaClassTraits<A2>::push(L_, a2);
        TLuaClassTraits<A3>::push(L_, a3);
        LUA_CALL_END
    }

    template <typename A1, typename A2, typename A3, typename A4>
    void call(const char * name, A1 a1, A2 a2, A3 a3, A4 a4) {
        LUA_CALL_BEGIN
        TLuaClassTraits<A1>::push(L_, a1);
        TLuaClassTraits<A2>::push(L_, a2);
        TLuaClassTraits<A3>::push(L_, a3);
        TLuaClassTraits<A4>::push(L_, a4);
        LUA_CALL_END
    }

    template<typename T>
    void setGlobal(const char *name, T value) {
        TLuaClassTraits<T>::push(L_, value);
        lua_setglobal(L_, name);
    }

    template<typename T>
    T getGlobal(const char *name) {
        LuaStackBalancer_ balancer(L_);
        lua_getglobal(L_, name);
        return TLuaClassTraits<T>::to(L_, -1);
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

