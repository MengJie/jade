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

USING_JADE_NS

CShader::CShader(GLenum shaderType, const char * shaderSource)
{
    type_ = shaderType;
    source_ = shaderSource;
}

CShader::~CShader()
{
    if (0 != id_) {
        glDeleteShader(id_);
    }
}

bool
CShader::compile()
{
    id_ = glCreateShader(type_);
    const char *source = source_.c_str();
    glShaderSource(id_, 1, &source, NULL);

    glCompileShader(id_);

    GLint status;
    glGetShaderiv(id_, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint length;
        glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &length);

        GLchar *log = new GLchar[length + 1];
        glGetShaderInfoLog(id_, length, NULL, log);

        const char *strType = NULL;
        switch(type_)
        {
        case GL_VERTEX_SHADER: strType = "vertex"; break;
        case GL_GEOMETRY_SHADER: strType = "geometry"; break;
        case GL_FRAGMENT_SHADER: strType = "fragment"; break;
        }
        ERROR("Compile failure in %s shader:\n%s\n", strType, log);
        delete[] log;
        return false;
    }
    return true;
}

