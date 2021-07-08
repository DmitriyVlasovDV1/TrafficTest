/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : render.cpp
 * PURPOSE     : Animation system project.
 *             : Render system implementation module.
 *             : Basic functions implementation file.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 26.07.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support of 30 Phys-Math Lyceum.
 */

#include <iostream>

#include "render.h"
#include "../anim.h"

/* Debug output function.
 * ARGUMENTS:
 *   - source APi or device:
 *      UINT Source;
 *   - error type:
 *      UINT Type;
 *   - error message id:
 *      UINT Id, 
 *   - message severity:
 *      UINT severity, 
 *   - message text length:
 *      INT Length, 
 *   - message text:
 *      CHAR *Message, 
 *   - user addon parameters pointer:
 *      VOID *UserParam;
 * RETURNS: None.
 */
static VOID APIENTRY glDebugOutput( UINT Source, UINT Type, UINT Id, UINT Severity,
                                    INT Length, const CHAR *Message, const VOID *UserParam )
{
  INT len = 0;
  static CHAR Buf[10000];

  /* Ignore non-significant error/warning codes */
  if (Id == 131169 || Id == 131185 || Id == 131218 || Id == 131204)
    return;

  len += sprintf(Buf + len, "Debug message (%i) %s\n", Id, Message);

  switch (Source)
  {
  case GL_DEBUG_SOURCE_API:
    len += sprintf(Buf + len, "Source: API\n");
    break;
  case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
    len += sprintf(Buf + len, "Source: Window System\n");
    break;
  case GL_DEBUG_SOURCE_SHADER_COMPILER:
    len += sprintf(Buf + len, "Source: Shader Compiler\n");
    break;
  case GL_DEBUG_SOURCE_THIRD_PARTY:
    len += sprintf(Buf + len, "Source: Third Party\n");
    break;
  case GL_DEBUG_SOURCE_APPLICATION:
    len += sprintf(Buf + len, "Source: Application");
    break;
  case GL_DEBUG_SOURCE_OTHER:
    len += sprintf(Buf + len, "Source: Other");
    break;
  }
  len += sprintf(Buf + len, "\n");

  switch (Type)
  {
  case GL_DEBUG_TYPE_ERROR:
    len += sprintf(Buf + len, "Type: Error");
    break;
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
    len += sprintf(Buf + len, "Type: Deprecated Behaviour");
    break;
  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
    len += sprintf(Buf + len, "Type: Undefined Behaviour");
    break; 
  case GL_DEBUG_TYPE_PORTABILITY:
    len += sprintf(Buf + len, "Type: Portability");
    break;
  case GL_DEBUG_TYPE_PERFORMANCE:
    len += sprintf(Buf + len, "Type: Performance");
    break;
  case GL_DEBUG_TYPE_MARKER:
    len += sprintf(Buf + len, "Type: Marker");
    break;
  case GL_DEBUG_TYPE_PUSH_GROUP:
    len += sprintf(Buf + len, "Type: Push Group");
    break;
  case GL_DEBUG_TYPE_POP_GROUP:
    len += sprintf(Buf + len, "Type: Pop Group");
    break;
  case GL_DEBUG_TYPE_OTHER:
    len += sprintf(Buf + len, "Type: Other");
    break;
  }
  len += sprintf(Buf + len, "\n");

  switch (Severity)
  {
  case GL_DEBUG_SEVERITY_HIGH:
    len += sprintf(Buf + len, "Severity: high");
    break;
  case GL_DEBUG_SEVERITY_MEDIUM:
    len += sprintf(Buf + len, "Severity: medium");
    break;
  case GL_DEBUG_SEVERITY_LOW:
    len += sprintf(Buf + len, "Severity: low");
    break;
  case GL_DEBUG_SEVERITY_NOTIFICATION:
    len += sprintf(Buf + len, "Severity: notification");
    break;
  }
  len += sprintf(Buf + len, "\n\n");

  OutputDebugString(Buf);
} /* End of 'glDebugOutput' function */

/* Render constructor function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND &hWnd;
 *   - window sizes:
 *       INT &W, &H;
 */
digl::render::render( HWND &hWnd, INT &W, INT &H ) :
  manager_shader(), manager_material(), manager_prim(),
  manager_geom(), manager_emitter(), pipeline(),
  hWnd(hWnd), FrameW(W), FrameH(H), hDC(), hGLRC(),
  CurrentCS(), CurrentFill(), PushedCS(), PushedFill()
{
  /* Old variant */
  INT i;
  PIXELFORMATDESCRIPTOR pfd = {0};

  /* New variant */
  INT PixelFormatID;
  UINT NumOfFormats;

  PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormat = NULL;
  PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribs = NULL;

  /* Attributes array */
  INT PixelAttribs[] =
  {
    WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
    WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
    WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_ALPHA_BITS_ARB, 8,
    WGL_DEPTH_BITS_ARB, 24,
    WGL_STENCIL_BITS_ARB, 8,
    WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
    WGL_SAMPLES_ARB, 4,
    0
  };
  INT ContextAttribs[] =
  {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
    WGL_CONTEXT_MINOR_VERSION_ARB, 6,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
    0
  };
  HGLRC hRC;

  /* Store window and context */
  hDC = GetDC(hWnd);

  /* OpenGL initialization */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(hDC, &pfd);
  DescribePixelFormat(hDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(hDC, i, &pfd);

  /* OpenGL init: setup rendering context */
  hGLRC = wglCreateContext(hDC);
  wglMakeCurrent(hDC, hGLRC);

  if (glewInit() != GLEW_OK ||
      !(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
  {
    MessageBox(hWnd, "Error OpenGL initialization", "ERROR",
      MB_ICONERROR | MB_OK);
    exit(0);
  }

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
  glDebugMessageCallback(glDebugOutput, NULL);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);

  /* New issue */
  wglCreateContextAttribs =
    (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
  wglChoosePixelFormat =
    (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");

  wglChoosePixelFormat(hDC, PixelAttribs, NULL, 1, &PixelFormatID, &NumOfFormats);
  DescribePixelFormat(hDC, PixelFormatID, sizeof(pfd), &pfd);
  SetPixelFormat(hDC, PixelFormatID, &pfd);

  hRC = wglCreateContextAttribs(hDC, 0, ContextAttribs);

  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(hGLRC);
  hGLRC = hRC;
  wglMakeCurrent(hDC, hGLRC);
  if (glewInit() != GLEW_OK)
  {
    MessageBox(hWnd, "Error OpenGL initialization", "ERROR",
      MB_ICONERROR | MB_OK);
    exit(0);
  }

  /* Render parameters setup */
  glClearColor(0.30, 0.47, 0.8, 1);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(-1);

  PFNWGLSWAPINTERVALEXTPROC wglSwapInterval = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
  wglSwapInterval(0);

  /* Setup camera fields */
  Cam.SetView(vec3(5, 5, 5), vec3(0), vec3(0, 1, 0));

  /* Pipeline initialization */
  pipeline::Init();
} /* End of 'render' function */

/* Render destructor function */
digl::render::~render( VOID )
{
} /* End of 'render::~render' function */

/* Resize render function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID digl::render::Resize( VOID )
{
  glViewport(0, 0, FrameW, FrameH);
  Cam.SetProj(FrameW, FrameH);
  pipeline::Resize();
} /* End of 'render::Resize' function */

/* Start frame render function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID digl::render::FrameStart( VOID )
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
} /* End of 'render::FrameStart' function */

/* End frame render function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID digl::render::FrameEnd( VOID )
{
  glFinish();
} /* End of 'render::FrameEnd' function */

/* Copy frame function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID digl::render::FrameCopy( VOID )
{
  wglSwapLayerBuffers(hDC, WGL_SWAP_MAIN_PLANE);
 // glSwapBuffers();
} /* End of 'render::FrameCopy' function */

/* Set current coordinate system function.
 * ARGUMENTS:
 *   - coordinate system to set:
 *       cs NewCS;
 * RETURNS: None.
 */
VOID digl::render::Set( cs NewCS )
{
  CurrentCS = NewCS;
} /* End of 'render::Set' function */

/* Set current fill type function.
 * ARGUMENTS:
 *   - fill type to set:
 *       fill NewFill;
 * RETURNS: None.
 */
VOID digl::render::Set( fill NewFill )
{
  CurrentFill = NewFill;
} /* End of 'render::Set' function */

/* Push temporary coordinate system function.
 * ARGUMENTS:
 *   - coordinate system to push:
 *       cs NewCS;
 * RETURNS: None.
 */
VOID digl::render::Push( cs NewCS )
{
  PushedCS = CurrentCS;
  CurrentCS = NewCS;
} /* End of 'render::Push' function */

/* Push temporary drawing fill type function.
 * ARGUMENTS:
 *   - fill type to push:
 *       fill NewFill;
 * RETURNS: None.
 */
VOID digl::render::Push( fill NewFill )
{
  PushedFill = CurrentFill;
  CurrentFill = NewFill;
} /* End of 'render::Push' function */

/* Pop old coordinate system function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID digl::render::PopCS( VOID )
{
  CurrentCS = PushedCS;
  PushedCS = cs();
} /* End of 'render::PopCS' function */

/* Pop old drawing fill function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID digl::render::PopFill( VOID )
{
  CurrentFill = PushedFill;
  PushedFill = fill();
} /* End of 'render::PopFill' function */


/* Draw primitive function.
 * ARGUMENTS:
 *   - primitive to draw:
 *       const prim Pr;
 * RETURNS: None.
 */
VOID digl::render::DrawPrims( const primitives::primitives &Prs, const matr &World )
{
  for (auto Pr : Prs.Prims)
    if (1 || Pr->Material->Trans >= 1)
      Draw(*Pr, Pr->Transform * World);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  for (auto Pr : Prs.Prims)
    if (Pr->Material->Trans >= 1)
      Draw(*Pr, Pr->Transform * World);

  glCullFace(GL_BACK);
  for (auto Pr : Prs.Prims)
    if (Pr->Material->Trans >= 1)
      Draw(*Pr, Pr->Transform * World);

  glDisable(GL_CULL_FACE);
} /* End of 'digl::render::DrawPrims' function */

/* Draw primitive function.
 * ARGUMENTS:
 *   - primitive to draw:
 *       const prim Pr;
 * RETURNS: None.
 */
VOID digl::render::Draw( const primitives::prim &Pr, const matr &World )
  {
    INT Type =
      (Pr.Type == prim_type::TRIMESH) ? GL_TRIANGLES :
      (Pr.Type == prim_type::STRIP) ? GL_TRIANGLE_STRIP : GL_POINTS;

    matr WVP = World * Cam.VP;

    glLoadMatrixf(WVP);

    INT ProgId = Pr.ApplyMaterial();

    INT loc;
    if ((loc = glGetUniformLocation(ProgId, "MatrWVP")) != -1)
      glUniformMatrix4fv(loc, 1, FALSE, WVP);
    if ((loc = glGetUniformLocation(ProgId, "MatrW")) != -1)
      glUniformMatrix4fv(loc, 1, FALSE, (matr)World);

    if ((loc = glGetUniformLocation(ProgId, "Time")) != -1)
      glUniform1f(loc, anim::Get().Time);
    /*
    if ((loc = glGetUniformLocation(ProgId, "GlobalTime")) != -1)
      glUniform1f(loc, anim::Get());*/
    if ((loc = glGetUniformLocation(ProgId, "CamLoc")) != -1)
      glUniform3fv(loc, 1, Cam.Loc);
    if ((loc = glGetUniformLocation(ProgId, "CamDir")) != -1)
      glUniform3fv(loc, 1, Cam.Dir);

    glBindVertexArray(Pr.VA);
    if (Pr.NumOfElements != 0)
    {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr.IBuf);
      glDrawElements(Type, Pr.NumOfElements, GL_UNSIGNED_INT, NULL);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    else
      glDrawArrays(Type, 0, Pr.NumOfElements);
    glBindVertexArray(0);
  } /* End of 'Draw' function */
/* END OF 'render.cpp' FILE */
