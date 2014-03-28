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

#include "logger.hpp"
#include "shader.hpp"
#include "program.hpp"

USING_JADE_NS

CProgram::CProgram()
    :program_(0)
{ }

CProgram::~CProgram()
{
    if (0 != program_) {
        glDeleteProgram(program_);
    }
    for (auto it = shaders_.begin();it!=shaders_.end(); ++it) {
        (*it)->release();
    }
}

bool
CProgram::addShader(CShader * shader)
{
    shaders_.push_back(shader);
    shader->retain();
	return true;
}

bool
CProgram::link()
{
    program_ = glCreateProgram();

    for (auto it = shaders_.begin();it!=shaders_.end(); ++it) {
        glAttachShader(program_, (*it)->shader_);
    }

    glLinkProgram(program_);

    GLint status;
    glGetProgramiv (program_, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint length;
        glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &length);

        GLchar *log = new GLchar[length + 1];
        glGetProgramInfoLog(program_, length, NULL, log);
        ERROR("Linker failure: %s\n", log);
        delete[] log;
        return false;
    }

    for (auto it = shaders_.begin();it!=shaders_.end(); ++it) {
        glDetachShader(program_, (*it)->shader_);
    }

    return true;
}

