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

#ifndef _JADE_GLBUFFER_INCLUDE_
#define _JADE_GLBUFFER_INCLUDE_

#include "jade.hpp"
#include "globject.hpp"

JADE_NS_BEGIN

class CBuffer : public CGLObject
{
public:
    CBuffer();
    virtual ~CBuffer();

    virtual void enable() {};
    virtual void disable() {};
    virtual void draw() {};

protected:
    void bindBuffer(GLenum target);
    void bufferData(GLenum target,
            GLsizeiptr size,
            const GLvoid * data,
            GLenum usage);
};

class CTrianglesBuffer: public CBuffer
{
    struct Vertex {
        float x;
        float y;
        float z;
        float a;
    };
public:
    CTrianglesBuffer(GLuint location);
    virtual ~CTrianglesBuffer();

    virtual bool init();
    virtual void enable();
    virtual void disable();
    virtual void draw();

    void setPoint(int index, float x, float y, float z, float a);
private:
    vector<Vertex> positions_;
    GLuint location_;
};

JADE_NS_END

#endif
