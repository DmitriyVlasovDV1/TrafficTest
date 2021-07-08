/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : render.h
 * PURPOSE     : Animation system project.
 *             : Render system implementation module.
 *             : Main class declaration file.
 * PROGRAMMER  : Vlasov Dmitriy.
 * LAST UPDATE : 26.07.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support of 30 Phys-Math Lyceum.
 */

#ifndef __RENDER_H_
#define __RENDER_H_

#include "res.h"
#include "pipeline.h"
#include "../../def.h"

/* Project namespace */
namespace digl
{
  /* Render system representation class */
  class render : public manager_texture, public manager_shader, 
    public manager_material, public manager_prim, public manager_prims, public manager_font,
    public manager_geom, public manager_emitter, public pipeline
  {
  private:
    HWND &hWnd;  // Window handle

    HDC hDC;     // Device context handle
    HGLRC hGLRC; // Render context handle

  public:
    INT &FrameW, &FrameH;  // Window sizes
    mth::camera Cam;  // Render main camera

    /* Render constructor function.
     * ARGUMENTS:
     *   - window handle:
     *       HWND &hWnd;
     *   - window sizes:
     *       INT &W, &H;
     */
    render( HWND &hWnd, INT &W, INT &H );

    /* Render destructor function */
    ~render( VOID );

    /* Resize render function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Resize( VOID );

    /* Start frame render function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FrameStart( VOID );

    /* End frame render function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FrameEnd( VOID );

    /* Copy frame function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FrameCopy( VOID );

    /* Current coordinate system type enumeration */
    enum struct cs
    {
      WORLD, SCREEN
    } CurrentCS;

    /* Current drawing fill type enumeration */
    enum struct fill
    {
      WIREFRAME, SOLID
    } CurrentFill;

  private:
    cs PushedCS;     // Pushed coordinate system type
    fill PushedFill; // Pushed drawing fill type

  public:
    /* Set current coordinate system function.
     * ARGUMENTS:
     *   - coordinate system to set:
     *       cs NewCS;
     * RETURNS: None.
     */
    VOID Set( cs NewCS );

    /* Set current fill type function.
     * ARGUMENTS:
     *   - fill type to set:
     *       fill NewFill;
     * RETURNS: None.
     */
    VOID Set( fill NewFill );

    /* Push temporary coordinate system function.
     * ARGUMENTS:
     *   - coordinate system to push:
     *       cs NewCS;
     * RETURNS: None.
     */
    VOID Push( cs NewCS );

    /* Push temporary drawing fill type function.
     * ARGUMENTS:
     *   - fill type to push:
     *       fill NewFill;
     * RETURNS: None.
     */
    VOID Push( fill NewFill );

    /* Pop old coordinate system function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID PopCS( VOID );

    /* Pop old drawing fill function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID PopFill( VOID );

    /* Draw primitive function.
      * ARGUMENTS:
      *   - primitive to draw:
      *       const prim Pr;
      * RETURNS: None.
      */
    VOID Draw( const primitives::prim &Pr, const matr &World);

    /* Draw primitives function.
     * ARGUMENTS:
     *   - primitives to draw:
     *       const stock<primitives::prim> &Prs;
     * RETURNS: None.
     */
    VOID DrawPrims( const primitives::primitives &Prs, const matr &World);
  }; /* End of 'render' class */
} /* end of 'dagl' namespace */

#endif /* __render_h_ */

/* END OF 'render.h' FILE */
