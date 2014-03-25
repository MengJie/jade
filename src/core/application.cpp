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

#include "application.hpp"
#include "logger.hpp"
#include "luastate.hpp"

USING_JADE_NS

void
CGLFWApplication::keyCallback(GLFWwindow * window, int key, int scancode,
        int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void
CGLFWApplication::errorCallback(int error, const char * desc)
{
    ERROR("%d:%s", error, desc);
}

CGLFWApplication::CGLFWApplication(int width, int height):
    width_(width),
    height_(height)
{
}

CGLFWApplication::~CGLFWApplication()
{
}

bool
CGLFWApplication::init()
{
    CLuaState::instance();

    glfwSetErrorCallback(CGLFWApplication::errorCallback);

    if (!glfwInit())
        return false;

    window_ = glfwCreateWindow(width_, height_, "JADE", NULL, NULL);
    if (!window_) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window_);
    glfwSetKeyCallback(window_, keyCallback);

    return true;
}

void
CGLFWApplication::run()
{
    while (!glfwWindowShouldClose(window_))
    {
        float ratio;
        int width, height;

        glfwGetFramebufferSize(window_, &width, &height);
        ratio = width / (float)height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

        glBegin(GL_TRIANGLES);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }

    glfwTerminate();
}

