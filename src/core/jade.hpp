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

#ifndef _JADE_INCLUDE_
#define _JADE_INCLUDE_

#define JADE_NS_BEGIN namespace jade {
#define JADE_NS_END }
#define USING_JADE_NS using namespace jade;

//#define GLEW_STATIC
#include <gl/glew.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <algorithm>

#include "lua.hpp"
#include "logger.hpp"

typedef unsigned char u_char;
typedef u_char byte;

using namespace std;

#endif

