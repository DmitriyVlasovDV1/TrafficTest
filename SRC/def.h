/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : def.h
 * PURPOSE     : Definition file.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 20.08.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */

#ifndef __DEF_H_
#define __DEF_H_

/* Includes */
#include "mth/mth.h"
#include <cmath>
#include <iostream>

/* OpenGL */
#define GLEW_STATIC
#include "ANIM/RENDER/GL/glew.h"
#include "ANIM/RENDER/GL/wglext.h"
#pragma comment(lib, "opengl32")

/* Memory leaks controller */
#ifndef _NDEBUG
# define _CRTDBG_MAP_ALLOC
# include <crtdbg.h> 
# define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))

static class __Dummy 
{ 
public: 
  /* Class constructor */
  __Dummy( VOID ) 
  { 
    SetDbgMemHooks(); 
  } /* End of '__Dummy' constructor */
} __ooppss;

#endif /* _DEBUG */ 

#ifdef _DEBUG
# ifdef _CRTDBG_MAP_ALLOC 
#   define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
# endif /* _CRTDBG_MAP_ALLOC */ 
#endif /* _DEBUG */

/* Types definition */
typedef mth::vec4<FLT> vec4;
typedef mth::vec3<FLT> vec3;
typedef mth::vec2<FLT> vec2;
typedef mth::matr<FLT> matr;

#endif /* __DEF_H_ */

/* END OF 'def.h' FILE */
