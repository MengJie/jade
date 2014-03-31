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

#include "buffer.hpp"

USING_JADE_NS

CBuffer::CBuffer()
{
    glGenBuffers(1, &id_);
}

CBuffer::~CBuffer()
{
    if (0 != id_) {
        glDeleteBuffers(1, &id_);
    }
}

void
CBuffer::bindBuffer(GLenum target)
{
    glBindBuffer(target, id_);
}

void
CBuffer::bufferData(GLenum target,
        GLsizeiptr size,
        const GLvoid * data,
        GLenum usage)
{
    glBindBuffer(target, id_);
    glBufferData(target, size, data, usage);
    glBindBuffer(target, 0);
}

////////////////////////////////////////////////////////////////////////////////

CTrianglesBuffer::CTrianglesBuffer(GLuint location)
    :positions_(3), location_(location)
{
}

CTrianglesBuffer::~CTrianglesBuffer()
{
}

bool
CTrianglesBuffer::init()
{
    bufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*3, &positions_[0], GL_STATIC_DRAW);
    return true;
}

void
CTrianglesBuffer::enable()
{
    bindBuffer(GL_ARRAY_BUFFER);
    glEnableVertexAttribArray(location_);
    glVertexAttribPointer(location_, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void
CTrianglesBuffer::disable()
{
    glDisableVertexAttribArray(location_);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void
CTrianglesBuffer::draw()
{
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void
CTrianglesBuffer::setPoint(int index, float x, float y, float z, float a)
{
    positions_[index].x = x;
    positions_[index].y = y;
    positions_[index].z = z;
    positions_[index].a = a;
}

