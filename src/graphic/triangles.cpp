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
    position_ = program->getAttribLocation("a_position");
    color_ = program_->getAttribLocation("a_color");
    mvp_ = program_->getUniformLocation("mvp_matrix");
    mvp_matrix_ = glm::ortho(0.0, 640.0, 480.0, 0.0);
}

CTriangles::~CTriangles()
{
    if (0 != program_) {
        program_->release();
    }
}

void
CTriangles::draw() {
    program_->use();
    buffer_.bind();
    buffer_.update();

    glUniformMatrix4fv(mvp_, 1, GL_FALSE, &mvp_matrix_[0][0]);

    glEnableVertexAttribArray(position_);
    glEnableVertexAttribArray(color_);

    glVertexAttribPointer(position_, 4, GL_FLOAT, GL_FALSE,
        8*sizeof(float), 0);
    glVertexAttribPointer(color_, 4, GL_FLOAT, GL_FALSE,
        8*sizeof(float), (const void*)(4*sizeof(float)));

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(position_);
    glDisableVertexAttribArray(color_);

    buffer_.unbind();
    program_->unuse();
}

void
CTriangles::setPoint(int index, float x, float y, float z, float w) {
    buffer_.datas_[index].c1.x = x;
    buffer_.datas_[index].c1.y = y;
    buffer_.datas_[index].c1.z = z;
    buffer_.datas_[index].c1.w = w;
}

void
CTriangles::setColor(int index, float r, float g, float b, float a) {
    buffer_.datas_[index].c2.r = r;
    buffer_.datas_[index].c2.g = g;
    buffer_.datas_[index].c2.b = b;
    buffer_.datas_[index].c2.a = a;
}

