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
// inspired by http://lua-users.org/wiki/LunaWrapper and luabind

#include "jade.hpp"
#include "luastate.hpp"

using namespace std;

#define LUA_CTOR_BEGIN \
        const char * name = lua_tostring(L, lua_upvalueindex(1));

#define LUA_CTOR_END \
        C** a = (C**)lua_newuserdata(L, sizeof(C*)); \
        *a = obj; \
        luaL_getmetatable(L, name); \
        lua_setmetatable(L, -2); \
        return 1;

template<
    typename C
    ,typename A1 = void
    ,typename A2 = void
    ,typename A3 = void
    ,typename A4 = void
    ,typename A5 = void
    ,typename A6 = void
    ,typename A7 = void
    ,typename A8 = void
>
struct LuaConstructor {
    static int ctor(lua_State * L) {
        LUA_CTOR_BEGIN
        A1 a1 = TLuaClassTraits<A1>::to(L, 1);
        A2 a2 = TLuaClassTraits<A2>::to(L, 2);
        A3 a3 = TLuaClassTraits<A3>::to(L, 3);
        A4 a4 = TLuaClassTraits<A4>::to(L, 4);
        A5 a5 = TLuaClassTraits<A5>::to(L, 5);
        A6 a6 = TLuaClassTraits<A6>::to(L, 6);
        A7 a7 = TLuaClassTraits<A7>::to(L, 7);
        A8 a8 = TLuaClassTraits<A8>::to(L, 8);
        C* obj = new C(a1, a2, a3, a4, a5, a6, a7, a8);
        LUA_CTOR_END
    }
};
template<
    typename C
    ,typename A1
    ,typename A2
    ,typename A3
    ,typename A4
    ,typename A5
    ,typename A6
    ,typename A7
>
struct LuaConstructor<C, A1, A2, A3, A4, A5, A6, A7> {
    static int ctor(lua_State * L) {
        LUA_CTOR_BEGIN
        A1 a1 = TLuaClassTraits<A1>::to(L, 1);
        A2 a2 = TLuaClassTraits<A2>::to(L, 2);
        A3 a3 = TLuaClassTraits<A3>::to(L, 3);
        A4 a4 = TLuaClassTraits<A4>::to(L, 4);
        A5 a5 = TLuaClassTraits<A5>::to(L, 5);
        A6 a6 = TLuaClassTraits<A6>::to(L, 6);
        A7 a7 = TLuaClassTraits<A7>::to(L, 7);
        C* obj = new C(a1, a2, a3, a4, a5, a6, a7);
        LUA_CTOR_END
    }
};
template<
    typename C
    ,typename A1
    ,typename A2
    ,typename A3
    ,typename A4
    ,typename A5
    ,typename A6
>
struct LuaConstructor<C, A1, A2, A3, A4, A5, A6> {
    static int ctor(lua_State * L) {
        LUA_CTOR_BEGIN
        A1 a1 = TLuaClassTraits<A1>::to(L, 1);
        A2 a2 = TLuaClassTraits<A2>::to(L, 2);
        A3 a3 = TLuaClassTraits<A3>::to(L, 3);
        A4 a4 = TLuaClassTraits<A4>::to(L, 4);
        A5 a5 = TLuaClassTraits<A5>::to(L, 5);
        A6 a6 = TLuaClassTraits<A6>::to(L, 6);
        C* obj = new C(a1, a2, a3, a4, a5, a6);
        LUA_CTOR_END
    }
};
template<
    typename C
    ,typename A1
    ,typename A2
    ,typename A3
    ,typename A4
    ,typename A5
>
struct LuaConstructor<C, A1, A2, A3, A4, A5> {
    static int ctor(lua_State * L) {
        LUA_CTOR_BEGIN
        A1 a1 = TLuaClassTraits<A1>::to(L, 1);
        A2 a2 = TLuaClassTraits<A2>::to(L, 2);
        A3 a3 = TLuaClassTraits<A3>::to(L, 3);
        A4 a4 = TLuaClassTraits<A4>::to(L, 4);
        A5 a5 = TLuaClassTraits<A5>::to(L, 5);
        C* obj = new C(a1, a2, a3, a4, a5);
        LUA_CTOR_END
    }
};
template<
    typename C
    ,typename A1
    ,typename A2
    ,typename A3
    ,typename A4
>
struct LuaConstructor<C, A1, A2, A3, A4> {
    static int ctor(lua_State * L) {
        LUA_CTOR_BEGIN
        A1 a1 = TLuaClassTraits<A1>::to(L, 1);
        A2 a2 = TLuaClassTraits<A2>::to(L, 2);
        A3 a3 = TLuaClassTraits<A3>::to(L, 3);
        A4 a4 = TLuaClassTraits<A4>::to(L, 4);
        C* obj = new C(a1, a2, a3, a4);
        LUA_CTOR_END
    }
};
template<
    typename C
    ,typename A1
    ,typename A2
    ,typename A3
>
struct LuaConstructor<C, A1, A2, A3> {
    static int ctor(lua_State * L) {
        LUA_CTOR_BEGIN
        A1 a1 = TLuaClassTraits<A1>::to(L, 1);
        A2 a2 = TLuaClassTraits<A2>::to(L, 2);
        A3 a3 = TLuaClassTraits<A3>::to(L, 3);
        C* obj = new C(a1, a2, a3);
        LUA_CTOR_END
    }
};
template<
    typename C
    ,typename A1
    ,typename A2
>
struct LuaConstructor<C, A1, A2> {
    static int ctor(lua_State * L) {
        LUA_CTOR_BEGIN
        A1 a1 = TLuaClassTraits<A1>::to(L, 1);
        A2 a2 = TLuaClassTraits<A2>::to(L, 2);
        C* obj = new C(a1, a2);
        LUA_CTOR_END
    }
};
template<
    typename C
    ,typename A1
>
struct LuaConstructor<C, A1> {
    static int ctor(lua_State * L) {
        LUA_CTOR_BEGIN
        A1 a1 = TLuaClassTraits<A1>::to(L, 1);
        C* obj = new C(a1);
        LUA_CTOR_END
    }
};
template<typename C>
struct LuaConstructor<C> {
    static int ctor(lua_State * L) {
        LUA_CTOR_BEGIN
        C* obj = new C();
        LUA_CTOR_END
    }
};

template<typename T>
class TLuaClassRegister
{

#define LUA_THUNK_BEGIN \
            const char * name = lua_tostring(L, lua_upvalueindex(1)); \
            MT * method = static_cast<MT *>(lua_touserdata(L, lua_upvalueindex(2))); \
            C** obj = static_cast<C**>(luaL_checkudata(L, 1, name)); \
            lua_remove(L, 1);

    template<
        typename C = T
        ,typename R = void
        ,typename A1 = void
        ,typename A2 = void
        ,typename A3 = void
        ,typename A4 = void
        ,typename A5 = void
        ,typename A6 = void
        ,typename A7 = void
        ,typename A8 = void
    >
    struct LuaMethod {
        typedef LuaMethod<C, R, A1, A2, A3, A4, A5, A6, A7, A8> MT;
        R (C::*func)(A1, A2, A3, A4, A5, A6, A7, A8);
        static int thunk(lua_State * L) {
            LUA_THUNK_BEGIN
            A1 a1 = TLuaClassTraits<A1>::to(L, 1);
            A2 a2 = TLuaClassTraits<A2>::to(L, 2);
            A3 a3 = TLuaClassTraits<A3>::to(L, 3);
            A4 a4 = TLuaClassTraits<A4>::to(L, 4);
            A5 a5 = TLuaClassTraits<A5>::to(L, 5);
            A6 a6 = TLuaClassTraits<A6>::to(L, 6);
            A7 a7 = TLuaClassTraits<A7>::to(L, 7);
            A8 a8 = TLuaClassTraits<A8>::to(L, 8);
            R r = ((*obj)->*(method->func))(a1, a2, a3, a4, a5, a6, a7, a8);
            TLuaClassTraits<R>::push(L, r);
            return 1;
        }
    };
    template<
        typename C
        ,typename R
        ,typename A1
        ,typename A2
        ,typename A3
        ,typename A4
        ,typename A5
        ,typename A6
        ,typename A7
    >
    struct LuaMethod<C, R, A1, A2, A3, A4, A5, A6, A7> {
        typedef LuaMethod<C, R, A1, A2, A3, A4, A5, A6, A7> MT;
        R (C::*func)(A1, A2, A3, A4, A5, A6, A7);
        static int thunk(lua_State * L) {
            LUA_THUNK_BEGIN
            A1 a1 = TLuaClassTraits<A1>::to(L, 1);
            A2 a2 = TLuaClassTraits<A2>::to(L, 2);
            A3 a3 = TLuaClassTraits<A3>::to(L, 3);
            A4 a4 = TLuaClassTraits<A4>::to(L, 4);
            A5 a5 = TLuaClassTraits<A5>::to(L, 5);
            A6 a6 = TLuaClassTraits<A6>::to(L, 6);
            A7 a7 = TLuaClassTraits<A7>::to(L, 7);
            R r = ((*obj)->*(method->func))(a1, a2, a3, a4, a5, a6, a7);
            TLuaClassTraits<R>::push(L, r);
            return 1;
        }
    };
    template<
        typename C
        ,typename R
        ,typename A1
        ,typename A2
        ,typename A3
        ,typename A4
        ,typename A5
        ,typename A6
    >
    struct LuaMethod<C, R, A1, A2, A3, A4, A5, A6> {
        typedef LuaMethod<C, R, A1, A2, A3, A4, A5, A6> MT;
        R (C::*func)(A1, A2, A3, A4, A5, A6);
        static int thunk(lua_State * L) {
            LUA_THUNK_BEGIN
            A1 a1 = TLuaClassTraits<A1>::to(L, 1);
            A2 a2 = TLuaClassTraits<A2>::to(L, 2);
            A3 a3 = TLuaClassTraits<A3>::to(L, 3);
            A4 a4 = TLuaClassTraits<A4>::to(L, 4);
            A5 a5 = TLuaClassTraits<A5>::to(L, 5);
            A6 a6 = TLuaClassTraits<A6>::to(L, 6);
            R r = ((*obj)->*(method->func))(a1, a2, a3, a4, a5, a6);
            TLuaClassTraits<R>::push(L, r);
            return 1;
        }
    };
    template<
        typename C
        ,typename R
        ,typename A1
        ,typename A2
        ,typename A3
        ,typename A4
        ,typename A5
    >
    struct LuaMethod<C, R, A1, A2, A3, A4, A5> {
        typedef LuaMethod<C, R, A1, A2, A3, A4, A5> MT;
        R (C::*func)(A1, A2, A3, A4, A5);
        static int thunk(lua_State * L) {
            LUA_THUNK_BEGIN
            A1 a1 = TLuaClassTraits<A1>::to(L, 1);
            A2 a2 = TLuaClassTraits<A2>::to(L, 2);
            A3 a3 = TLuaClassTraits<A3>::to(L, 3);
            A4 a4 = TLuaClassTraits<A4>::to(L, 4);
            A5 a5 = TLuaClassTraits<A5>::to(L, 5);
            R r = ((*obj)->*(method->func))(a1, a2, a3, a4, a5);
            TLuaClassTraits<R>::push(L, r);
            return 1;
        }
    };
    template<
        typename C
        ,typename R
        ,typename A1
        ,typename A2
        ,typename A3
        ,typename A4
    >
    struct LuaMethod<C, R, A1, A2, A3, A4> {
        typedef LuaMethod<C, R, A1, A2, A3, A4> MT;
        R (C::*func)(A1, A2, A3, A4);
        static int thunk(lua_State * L) {
            LUA_THUNK_BEGIN
            A1 a1 = TLuaClassTraits<A1>::to(L, 1);
            A2 a2 = TLuaClassTraits<A2>::to(L, 2);
            A3 a3 = TLuaClassTraits<A3>::to(L, 3);
            A4 a4 = TLuaClassTraits<A4>::to(L, 4);
            R r = ((*obj)->*(method->func))(a1, a2, a3, a4);
            TLuaClassTraits<R>::push(L, r);
            return 1;
        }
    };
    template<
        typename C
        ,typename R
        ,typename A1
        ,typename A2
        ,typename A3
    >
    struct LuaMethod<C, R, A1, A2, A3> {
        typedef LuaMethod<C, R, A1, A2, A3> MT;
        R (C::*func)(A1, A2, A3);
        static int thunk(lua_State * L) {
            LUA_THUNK_BEGIN
            A1 a1 = TLuaClassTraits<A1>::to(L, 1);
            A2 a2 = TLuaClassTraits<A2>::to(L, 2);
            A3 a3 = TLuaClassTraits<A3>::to(L, 3);
            R r = ((*obj)->*(method->func))(a1, a2, a3);
            TLuaClassTraits<R>::push(L, r);
            return 1;
        }
    };
    template<
        typename C
        ,typename R
        ,typename A1
        ,typename A2
    >
    struct LuaMethod<C, R, A1, A2> {
        typedef LuaMethod<C, R, A1, A2> MT;
        R (C::*func)(A1, A2);
        static int thunk(lua_State * L) {
            LUA_THUNK_BEGIN
            A1 a1 = TLuaClassTraits<A1>::to(L, 1);
            A2 a2 = TLuaClassTraits<A2>::to(L, 2);
            R r = ((*obj)->*(method->func))(a1, a2);
            TLuaClassTraits<R>::push(L, r);
            return 1;
        }
    };
    template<
        typename C
        ,typename R
        ,typename A1
    >
    struct LuaMethod<C, R, A1> {
        typedef LuaMethod<C, R, A1> MT;
        R (C::*func)(A1);
        static int thunk(lua_State * L) {
            LUA_THUNK_BEGIN
            A1 a1 = TLuaClassTraits<A1>::to(L, 1);
            R r = ((*obj)->*(method->func))(a1);
            TLuaClassTraits<R>::push(L, r);
            return 1;
        }
    };
    template<
        typename C
        ,typename R
    >
    struct LuaMethod<C, R> {
        typedef LuaMethod<C, R> MT;
        R (C::*func)();
        static int thunk(lua_State * L) {
            LUA_THUNK_BEGIN
            R r = ((*obj)->*(method->func))();
            TLuaClassTraits<R>::push(L, r);
            return 1;
        }
    };
    template<
        typename C
        ,typename A1
        ,typename A2
        ,typename A3
        ,typename A4
        ,typename A5
        ,typename A6
        ,typename A7
        ,typename A8
    >
    struct LuaMethod<C, void, A1, A2, A3, A4, A5, A6, A7, A8> {
        typedef LuaMethod<C, void, A1, A2, A3, A4, A5, A6, A7, A8> MT;
        void (C::*func)(A1, A2, A3, A4, A5, A6, A7, A8);
        static int thunk(lua_State * L) {
            LUA_THUNK_BEGIN
            A1 a1 = TLuaClassTraits<A1>::to(L, 1);
            A2 a2 = TLuaClassTraits<A2>::to(L, 2);
            A3 a3 = TLuaClassTraits<A3>::to(L, 3);
            A4 a4 = TLuaClassTraits<A4>::to(L, 4);
            A5 a5 = TLuaClassTraits<A5>::to(L, 5);
            A6 a6 = TLuaClassTraits<A6>::to(L, 6);
            A7 a7 = TLuaClassTraits<A7>::to(L, 7);
            A8 a8 = TLuaClassTraits<A8>::to(L, 8);
            ((*obj)->*(method->func))(a1, a2, a3, a4, a5, a6, a7, a8);
            return 0;
        }
    };
    template<
        typename C
        ,typename A1
        ,typename A2
        ,typename A3
        ,typename A4
        ,typename A5
        ,typename A6
        ,typename A7
    >
    struct LuaMethod<C, void, A1, A2, A3, A4, A5, A6, A7> {
        typedef LuaMethod<C, void, A1, A2, A3, A4, A5, A6, A7> MT;
        void (C::*func)(A1, A2, A3, A4, A5, A6, A7);
        static int thunk(lua_State * L) {
            LUA_THUNK_BEGIN
            A1 a1 = TLuaClassTraits<A1>::to(L, 1);
            A2 a2 = TLuaClassTraits<A2>::to(L, 2);
            A3 a3 = TLuaClassTraits<A3>::to(L, 3);
            A4 a4 = TLuaClassTraits<A4>::to(L, 4);
            A5 a5 = TLuaClassTraits<A5>::to(L, 5);
            A6 a6 = TLuaClassTraits<A6>::to(L, 6);
            A7 a7 = TLuaClassTraits<A7>::to(L, 7);
            ((*obj)->*(method->func))(a1, a2, a3, a4, a5, a6, a7);
            return 0;
        }
    };
    template<
        typename C
        ,typename A1
        ,typename A2
        ,typename A3
        ,typename A4
        ,typename A5
        ,typename A6
    >
    struct LuaMethod<C, void, A1, A2, A3, A4, A5, A6> {
        typedef LuaMethod<C, void, A1, A2, A3, A4, A5, A6> MT;
        void (C::*func)(A1, A2, A3, A4, A5, A6);
        static int thunk(lua_State * L) {
            LUA_THUNK_BEGIN
            A1 a1 = TLuaClassTraits<A1>::to(L, 1);
            A2 a2 = TLuaClassTraits<A2>::to(L, 2);
            A3 a3 = TLuaClassTraits<A3>::to(L, 3);
            A4 a4 = TLuaClassTraits<A4>::to(L, 4);
            A5 a5 = TLuaClassTraits<A5>::to(L, 5);
            A6 a6 = TLuaClassTraits<A6>::to(L, 6);
            ((*obj)->*(method->func))(a1, a2, a3, a4, a5, a6);
            return 0;
        }
    };
    template<
        typename C
        ,typename A1
        ,typename A2
        ,typename A3
        ,typename A4
        ,typename A5
    >
    struct LuaMethod<C, void, A1, A2, A3, A4, A5> {
        typedef LuaMethod<C, void, A1, A2, A3, A4, A5> MT;
        void (C::*func)(A1, A2, A3, A4, A5);
        static int thunk(lua_State * L) {
            LUA_THUNK_BEGIN
            A1 a1 = TLuaClassTraits<A1>::to(L, 1);
            A2 a2 = TLuaClassTraits<A2>::to(L, 2);
            A3 a3 = TLuaClassTraits<A3>::to(L, 3);
            A4 a4 = TLuaClassTraits<A4>::to(L, 4);
            A5 a5 = TLuaClassTraits<A5>::to(L, 5);
            ((*obj)->*(method->func))(a1, a2, a3, a4, a5);
            return 0;
        }
    };
    template<
        typename C
        ,typename A1
        ,typename A2
        ,typename A3
        ,typename A4
    >
    struct LuaMethod<C, void, A1, A2, A3, A4> {
        typedef LuaMethod<C, void, A1, A2, A3, A4> MT;
        void (C::*func)(A1, A2, A3, A4);
        static int thunk(lua_State * L) {
            LUA_THUNK_BEGIN
            A1 a1 = TLuaClassTraits<A1>::to(L, 1);
            A2 a2 = TLuaClassTraits<A2>::to(L, 2);
            A3 a3 = TLuaClassTraits<A3>::to(L, 3);
            A4 a4 = TLuaClassTraits<A4>::to(L, 4);
            ((*obj)->*(method->func))(a1, a2, a3, a4);
            return 0;
        }
    };
    template<
        typename C
        ,typename A1
        ,typename A2
        ,typename A3
    >
    struct LuaMethod<C, void, A1, A2, A3> {
        typedef LuaMethod<C, void, A1, A2, A3> MT;
        void (C::*func)(A1, A2, A3);
        static int thunk(lua_State * L) {
            LUA_THUNK_BEGIN
            A1 a1 = TLuaClassTraits<A1>::to(L, 1);
            A2 a2 = TLuaClassTraits<A2>::to(L, 2);
            A3 a3 = TLuaClassTraits<A3>::to(L, 3);
            ((*obj)->*(method->func))(a1, a2, a3);
            return 0;
        }
    };
    template<
        typename C
        ,typename A1
        ,typename A2
    >
    struct LuaMethod<C, void, A1, A2> {
        typedef LuaMethod<C, void, A1, A2> MT;
        void (C::*func)(A1, A2);
        static int thunk(lua_State * L) {
            LUA_THUNK_BEGIN
            A1 a1 = TLuaClassTraits<A1>::to(L, 1);
            A2 a2 = TLuaClassTraits<A2>::to(L, 2);
            ((*obj)->*(method->func))(a1, a2);
            return 0;
        }
    };
    template<
        typename C
        ,typename A1
    >
    struct LuaMethod<C, void, A1> {
        typedef LuaMethod<C, void, A1> MT;
        void (C::*func)(A1);
        static int thunk(lua_State * L) {
            LUA_THUNK_BEGIN
            A1 a1 = TLuaClassTraits<A1>::to(L, 1);
            ((*obj)->*(method->func))(a1);
            return 0;
        }
    };
    template<typename C>
    struct LuaMethod<C> {
        typedef LuaMethod<C> MT;
        void (C::*func)();
        static int thunk(lua_State * L) {
            LUA_THUNK_BEGIN
            ((*obj)->*(method->func))();
            return 0;
        }
    };

public:
    TLuaClassRegister<T>(const char * name) {
        className_ = name;

        L_ = CLuaState::instance().state();
        LuaStackBalancer_ balancer(L_);

        luaL_newmetatable(L_, className_.c_str());
        lua_pushstring(L_, "__gc");
        lua_pushstring(L_, className_.c_str());
        lua_pushcclosure(L_, &TLuaClassRegister<T>::gc, 1);
        lua_settable(L_, -3);

        lua_pushstring(L_, "__cname");
        lua_pushstring(L_, className_.c_str());
        lua_settable(L_, -3);

        lua_pushstring(L_, "__index");
        lua_newtable(L_);
        lua_settable(L_, -3);
    }

    template<typename CT>
    TLuaClassRegister<T>& method(CT _ct) {
        LuaStackBalancer_ balancer(L_);
        lua_pushstring(L_, className_.c_str());
        lua_pushcclosure(L_, &CT::ctor, 1);
        lua_setglobal(L_, className_.c_str());
        return *this;
    }

#define LUA_METHOD_BODY \
    LuaStackBalancer_ balancer(L_); \
    luaL_getmetatable(L_, className_.c_str()); \
    lua_pushstring(L_, "__index"); \
    lua_gettable(L_, -2); \
    lua_pushstring(L_, name); \
    lua_pushstring(L_, className_.c_str()); \
    MT * method = static_cast<MT *>(lua_newuserdata(L_, sizeof(MT))); \
    method->func = func; \
    lua_pushcclosure(L_, &MT::thunk, 2); \
    lua_settable(L_, -3); \
    return *this;

    template<
        typename R
        ,typename A1
        ,typename A2
        ,typename A3
        ,typename A4
        ,typename A5
        ,typename A6
        ,typename A7
        ,typename A8
    >
    TLuaClassRegister<T>& method(const char * name, R (T::*func)(A1, A2, A3, A4, A5, A6, A7, A8)) {
        typedef LuaMethod<T, R, A1, A2, A3, A4, A5, A6, A7, A8> MT;
        LUA_METHOD_BODY
    }
    template<
        typename R
        ,typename A1
        ,typename A2
        ,typename A3
        ,typename A4
        ,typename A5
        ,typename A6
        ,typename A7
    >
    TLuaClassRegister<T>& method(const char * name, R (T::*func)(A1, A2, A3, A4, A5, A6, A7)) {
        typedef LuaMethod<T, R, A1, A2, A3, A4, A5, A6, A7> MT;
        LUA_METHOD_BODY
    }
    template<
        typename R
        ,typename A1
        ,typename A2
        ,typename A3
        ,typename A4
        ,typename A5
        ,typename A6
    >
    TLuaClassRegister<T>& method(const char * name, R (T::*func)(A1, A2, A3, A4, A5, A6)) {
        typedef LuaMethod<T, R, A1, A2, A3, A4, A5, A6> MT;
        LUA_METHOD_BODY
    }
    template<
        typename R
        ,typename A1
        ,typename A2
        ,typename A3
        ,typename A4
        ,typename A5
    >
    TLuaClassRegister<T>& method(const char * name, R (T::*func)(A1, A2, A3, A4, A5)) {
        typedef LuaMethod<T, R, A1, A2, A3, A4, A5> MT;
        LUA_METHOD_BODY
    }
    template<
        typename R
        ,typename A1
        ,typename A2
        ,typename A3
        ,typename A4
    >
    TLuaClassRegister<T>& method(const char * name, R (T::*func)(A1, A2, A3, A4)) {
        typedef LuaMethod<T, R, A1, A2, A3, A4> MT;
        LUA_METHOD_BODY
    }
    template<
        typename R
        ,typename A1
        ,typename A2
        ,typename A3
    >
    TLuaClassRegister<T>& method(const char * name, R (T::*func)(A1, A2, A3)) {
        typedef LuaMethod<T, R, A1, A2, A3> MT;
        LUA_METHOD_BODY
    }
    template<
        typename R
        ,typename A1
        ,typename A2
    >
    TLuaClassRegister<T>& method(const char * name, R (T::*func)(A1, A2)) {
        typedef LuaMethod<T, R, A1, A2> MT;
        LUA_METHOD_BODY
    }
    template<
        typename R
        ,typename A1
    >
    TLuaClassRegister<T>& method(const char * name, R (T::*func)(A1)) {
        typedef LuaMethod<T, R, A1> MT;
        LUA_METHOD_BODY
    }
    template<
        typename R
    >
    TLuaClassRegister<T>& method(const char * name, R (T::*func)()) {
        typedef LuaMethod<T, R> MT;
        LUA_METHOD_BODY
    }

protected:
    static int gc(lua_State *L) {
        const char * name = lua_tostring(L, lua_upvalueindex(1));
        T** obj = static_cast<T**>(luaL_checkudata(L, -1, name));
        (*obj)->release();
        return 0;
    }
private:
    string className_;
    lua_State * L_;
};


template<typename T>
TLuaClassRegister<T>&
LuaClass(const char * name, const char * parent = nullptr) {
    TLuaClassTraits<T>::className_ = name;
    if (parent != nullptr) {
        CLuaInheritRelation & relation = CLuaInheritRelation::instance();
        relation.addRelation(name, parent);
    }
    return *(new TLuaClassRegister<T>(name));
}

JADE_NS_END

#endif

