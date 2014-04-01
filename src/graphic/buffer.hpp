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

JADE_NS_BEGIN

template<typename T>
class CGLBufferCommon
{
public:
    CGLBufferCommon() {
        glGenBuffers(1, &id_);
    }
    virtual ~CGLBufferCommon() {
        if (0 != id_) {
            glDeleteBuffers(1, &id_);
        }
    }
    inline void bind() {
        glBindBuffer(GL_ARRAY_BUFFER, id_);
    }
    inline void unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    inline void update() {
        glBufferData(GL_ARRAY_BUFFER,
            sizeof(T::Vertex) * static_cast<T*>(this)->datas_.size(),
            &static_cast<T*>(this)->datas_[0],
            GL_STREAM_DRAW);
    }
protected:
    GLuint id_;
};

template<
    typename C1
    ,typename C2 = void
    ,typename C3 = void
>
class CGLBuffer: public CGLBufferCommon< CGLBuffer<C1, C2, C3> >
{
public:
    struct Vertex {
        C1 c1;
        C2 c2;
        C3 c3;
    };
    vector<Vertex> datas_;
};
template<
    typename C1
    ,typename C2
>
class CGLBuffer<C1, C2>: public CGLBufferCommon<CGLBuffer<C1,C2> >
{
public:
    struct Vertex {
        C1 c1;
        C2 c2;
    };
    vector<Vertex> datas_;
};
template<
    typename C1
>
class CGLBuffer<C1>: public CGLBufferCommon<CGLBuffer<C1> >
{
public:
    struct Vertex {
        C1 c1;
    };
    vector<Vertex> datas_;
};

JADE_NS_END

#endif

