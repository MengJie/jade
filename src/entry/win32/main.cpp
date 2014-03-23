#include <glfw/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

#include "application.hpp"

using namespace jade;

int
main(void)
{
    CGLFWApplication * app = new CGLFWApplication(640, 480);
    app->init();
    app->run();
}
