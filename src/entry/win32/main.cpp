#include "jade.hpp"

#include "object.hpp"
#include "application.hpp"
#include "luastate.hpp"
#include "luaobject.hpp"

using namespace jade;

int
main(void)
{
    CGLFWApplication * app = new CGLFWApplication(640, 480);
    if (!app->init())
        return 0;
    app->run();
}

