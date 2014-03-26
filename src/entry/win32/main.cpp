#include <glfw/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

#include "object.hpp"
#include "application.hpp"
#include "luastate.hpp"
#include "luaobject.hpp"

using namespace jade;

class CFoo: public CObject
{
public:
    CFoo() {
        DEBUG("CFoo::construct\n");
    }
    ~CFoo() {
        DEBUG("CFoo::destruct\n");
    }
    bool init() {
        DEBUG("CFoo::init\n");
        return true;
    }
    void foo() {
        DEBUG("CFoo::foo\n");
    }
    void bar(int i) {
        DEBUG("CFoo::bar %d\n", i);
    }
};

//class LFoo: public CFoo,
//            public TLuaObject<LFoo>
//{
//public:
//    int init(lua_State *L) {
//        DEBUG("LFoo init\n");
//        CFoo::init();
//        return 0;
//    }
//    int bar(lua_State *L) {
//        DEBUG("LFoo bar\n");
//        int i = luaL_checkint(L, 1);
//        CFoo::bar(i);
//        return 0;
//    }
//public:
//    typedef TLuaObject<LFoo>::RegType ReType;
//    static const char className_[];
//    static const RegType register_[];
//};

//const char LFoo::className_[] = "Foo";
//const LFoo::RegType LFoo::register_[] = {
//    {"init", &LFoo::init},
//    {"bar", &LFoo::bar},
//};

int
main(void)
{
    CGLFWApplication * app = new CGLFWApplication(640, 480);
    app->init();

    LuaClass<CFoo>("Foo")
        .constructor()
        .method("foo", &CFoo::foo);

    //LFoo::regist();
    CLuaState & lua = CLuaState::instance();

    //lua.call("test");
    //lua.call("test", 1);
    //lua.call("test", "hi");
    //lua.call("test", 1, "hi");
    //lua.call("test", "hi", 1, "say");
    //lua.call("test", 5, "hi", 6, "say");

    lua.call("test2");

    app->run();
}
