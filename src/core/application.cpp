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
#include "luaobject.hpp"

#include "program.hpp"
#include "shader.hpp"
#include "triangles.hpp"

USING_JADE_NS

CApplication::CApplication()
{
    CLuaState & lua = CLuaState::instance();

    LuaClass<CProgram>("Program")
        .method(LuaConstructor<CProgram>())
        .method("addShader", &CProgram::addShader)
        .method("link", &CProgram::link)
        .method("getAttribLocation", &CProgram::getAttribLocation)
        ;

    LuaClass<CShader>("Shader")
        .method(LuaConstructor<CShader, GLenum, const char*>())
        .method("compile", &CShader::compile)
        ;

    LuaClass<CTriangles>("Triangles")
        .method(LuaConstructor<CTriangles, CProgram*>())
        .method("setPoint", &CTriangles::setPoint)
        ;

    lua.setGlobal("GL_VERTEX_SHADER", GL_VERTEX_SHADER);
    lua.setGlobal("GL_FRAGMENT_SHADER", GL_FRAGMENT_SHADER);
}

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
    ERROR("GLFW ERROR [%d]:%s", error, desc);
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
    CLuaState & lua = CLuaState::instance();

    glfwSetErrorCallback(CGLFWApplication::errorCallback);

    if (!glfwInit())
        return false;

    //glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(width_, height_, "JADE", NULL, NULL);
    if (!window_) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window_);

    INFO("                 GL_VERSION: %s\n", glGetString(GL_VERSION));
    INFO("GL_SHADING_LANGUAGE_VERSION: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    glewExperimental=GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        ERROR("glew init error: %s\n", ::glewGetErrorString(err));
        return false;
    }

    glfwSetKeyCallback(window_, keyCallback);

    lua.call("init");

    //glGenVertexArrays(1, &vao);
    //glBindVertexArray(vao);

    return true;
}

void
CGLFWApplication::run()
{
    CLuaState & lua = CLuaState::instance();

    while (!glfwWindowShouldClose(window_))
    {
        float ratio;
        int width, height;

        glfwGetFramebufferSize(window_, &width, &height);
        ratio = width / (float)height;

        glViewport(0, 0, width, height);

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        CTriangles * triangles = lua.getGlobal<CTriangles *>("triangles");

        triangles->draw();

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }

    glfwTerminate();
}

