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

#ifndef _JADE_LUAOBJECT_INLCUDE_
#define _JADE_LUAOBJECT_INLCUDE_

JADE_NS_BEGIN

// a light weight cpp class wrapper for lua
// reference: http://lua-users.org/wiki/LunaWrapper
#include "jade.hpp"
#include "luastate.hpp"

using namespace std;

//template<typename T>
//class TLuaObject
//{
//public:
//    static void regist() {
//        lua_State * L = CLuaState::instance().state();
//        lua_pushcfunction(L, &TLuaObject<T>::constructor);
//        lua_setglobal(L, T::className_);
//
//        luaL_newmetatable(L, T::className_);
//        lua_pushstring(L, "__gc");
//        lua_pushcfunction(L, &TLuaObject<T>::gc);
//        lua_settable(L, -3);
//
//        lua_pushstring(L, "__index");
//        lua_newtable(L);
//        for (int i = 0; T::register_[i].name; i++) {
//            lua_pushstring(L, T::register_[i].name);
//            lua_pushnumber(L, i);
//            lua_pushcclosure(L, &TLuaObject<T>::thunk, 1);
//            lua_settable(L, -3);
//        }
//        lua_settable(L, -3);
//    }
//
//    static int constructor(lua_State *L) {
//        T* obj = new T();
//        T** a = (T**)lua_newuserdata(L, sizeof(T*));
//        *a = obj;
//        luaL_getmetatable(L, T::className_);
//        lua_setmetatable(L, -2);
//        return 1;
//    }
//
//    static int thunk(lua_State *L) {
//        int i = (int)lua_tonumber(L, lua_upvalueindex(1));
//        T** obj = static_cast<T**>(luaL_checkudata(L, 1, T::className_));
//        lua_remove(L, 1);
//        return ((*obj)->*(T::register_[i].mfunc))(L);
//    }
//
//    static int gc(lua_State *L) {
//        T** obj = static_cast<T**>(luaL_checkudata(L, -1, T::className_));
//        (*obj)->release();
//        return 0;
//    }
//
//    struct RegType {
//        const char *name;
//        int(T::*mfunc)(lua_State*);
//    };
//};



template<typename T>
class TLuaClassRegister
{
    template<typename T>
    struct TLuaMethod_0_0
    {
        void (T::*func_)(void);
        TLuaClassRegister<T> * register_;
    };
public:
    TLuaClassRegister<T>(const TLuaClassRegister<T> & rhs) {
        className_ = rhs.className_;
        L_ = rhs.L_;
    }

    TLuaClassRegister<T>(const char * name) {
        className_ = name;

        L_ = CLuaState::instance().state();
        LuaStackBalancer_ balancer(L_);

        luaL_newmetatable(L_, className_.c_str());
        lua_pushstring(L_, "__gc");
        TLuaMethod_0_0<T> * method = (TLuaMethod_0_0<T> *)lua_newuserdata(L_, sizeof(TLuaMethod_0_0<T>));
        method->register_ = this;
        lua_pushcclosure(L_, &TLuaClassRegister<T>::gc, 1);
        lua_settable(L_, -3);

        lua_pushstring(L_, "__index");
        lua_newtable(L_);
        lua_settable(L_, -3);
    }

    TLuaClassRegister<T>& constructor() {
        LuaStackBalancer_ balancer(L_);

        TLuaMethod_0_0<T> * method = (TLuaMethod_0_0<T> *)lua_newuserdata(L_, sizeof(TLuaMethod_0_0<T>));
        method->register_ = this;
        lua_pushcclosure(L_, &TLuaClassRegister<T>::construct, 1);
        lua_setglobal(L_, method->register_->className_.c_str());

        return *this;
    }

    TLuaClassRegister<T>& method(const char * name, void (T::*func)(void)) {
        LuaStackBalancer_ balancer(L_);

        luaL_getmetatable(L_, className_.c_str());
        lua_pushstring(L_, "__index");
        lua_gettable(L_, -2);

        lua_pushstring(L_, name);
        TLuaMethod_0_0<T> * method = (TLuaMethod_0_0<T> *)lua_newuserdata(L_, sizeof(TLuaMethod_0_0<T>));
        method->func_ = func;
        method->register_ = this;
        lua_pushcclosure(L_, &TLuaClassRegister<T>::thunk_0_0, 1);
        lua_settable(L_, -3);

        return *this;
    }

protected:
    static int thunk_0_0(lua_State *L) {
        TLuaMethod_0_0<T> * method = (TLuaMethod_0_0<T> *)lua_touserdata(L, lua_upvalueindex(1));
        T** obj = static_cast<T**>(luaL_checkudata(L, 1, method->register_->className_.c_str()));
        ((*obj)->*(method->func_))();
        return 0;
    }
    static int construct(lua_State *L) {
        TLuaMethod_0_0<T> * method = (TLuaMethod_0_0<T> *)lua_touserdata(L, lua_upvalueindex(1));
        T* obj = new T();
        T** a = (T**)lua_newuserdata(L, sizeof(T*));
        *a = obj;
        luaL_getmetatable(L, method->register_->className_.c_str());
        lua_setmetatable(L, -2);
        return 1;
    }
    static int gc(lua_State *L) {
        TLuaMethod_0_0<T> * method = (TLuaMethod_0_0<T> *)lua_touserdata(L, lua_upvalueindex(1));
        T** obj = static_cast<T**>(luaL_checkudata(L, -1, method->register_->className_.c_str()));
        (*obj)->release();
        return 0;
    }
private:
    string className_;
    lua_State * L_;
};

template<typename T>
TLuaClassRegister<T>&
LuaClass(const char * name) {
    return *(new TLuaClassRegister<T>(name));
}

JADE_NS_END

#endif

