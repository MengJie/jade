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

#ifndef _JADE_TRIANGLES_INCLUDE_
#define _JADE_TRIANGLES_INCLUDE_

#include "jade.hpp"
#include "object.hpp"
#include "program.hpp"
#include "buffer.hpp"

JADE_NS_BEGIN

class CTriangles: public CObject
{
public:
    CTriangles(CProgram * program);
    virtual ~CTriangles();
    void draw();
    void setPoint(int index, float x, float y, float z, float w);
    void setColor(int index, float r, float g, float b, float a);
private:
    CProgram * program_;
    CGLBuffer<glm::vec4, glm::vec4> buffer_;
    GLuint position_;
    GLuint color_;
    GLuint mvp_;
    glm::mat4 mvp_matrix_;
};

JADE_NS_END

#endif

