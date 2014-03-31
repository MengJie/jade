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

#include "triangles.hpp"

USING_JADE_NS

CTriangles::CTriangles(CProgram * program)
{
    program_ = program;
    program_->retain();
    buffer_.datas_.resize(3);
    location_ = program->getAttribLocation("position");
}

CTriangles::~CTriangles()
{
    if (0 != program_) {
        program_->release();
    }
}

void
CTriangles::draw() {
    glUseProgram(program_->getId());
    buffer_.bind();
    buffer_.update();
    glEnableVertexAttribArray(location_);
    glVertexAttribPointer(location_, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(location_);
    buffer_.unbind();
    glUseProgram(0);
}

void
CTriangles::setPoint(int index, float x, float y, float z, float a) {
    buffer_.datas_[index].c1.x = x;
    buffer_.datas_[index].c1.y = y;
    buffer_.datas_[index].c1.z = z;
    buffer_.datas_[index].c1.a = a;
}

