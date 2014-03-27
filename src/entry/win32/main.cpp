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
        i_ = 0;
    }
    CFoo(int i) {
        DEBUG("CFoo::construct %d\n", i);
        i_ = i;
    }
    CFoo(int i, int j) {
        DEBUG("CFoo::construct %d, %d\n", i, j);
        i_ = i + j;
    }
    CFoo(int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8) {
        DEBUG("CFoo::construct %d, %d, %d, %d, %d, %d, %d, %d\n",
                i1, i2, i3, i4, i5, i6, i7, i8);
        i_ = i1 + i2 + i3 + i4 + i5 + i6 + i7 + i8 ;
    }
    ~CFoo() {
        DEBUG("CFoo::destruct\n");
    }
    bool init() {
        DEBUG("CFoo::init\n");
        return true;
    }
    void foo() {
        DEBUG("CFoo::foo %d\n", i_);
    }
    int bar(int i) {
        i_ = i;
        DEBUG("CFoo::bar %d\n", i_);
        return 71;
    }
private:
    int i_;
};

int
main(void)
{
    CGLFWApplication * app = new CGLFWApplication(640, 480);
    app->init();

    LuaClass<CFoo>("Foo")
        .method(LuaConstructor<CFoo, int, int, int, int, int, int, int, int>())
        .method("foo", &CFoo::foo)
        .method("bar", &CFoo::bar)
		;

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
