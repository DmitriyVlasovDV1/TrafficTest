/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : win.h
 * PURPOSE     : Window class.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 20.08.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */

#ifndef __WIN_H_
#define __WIN_H_

/* Includes */
#include "../def.h"

/* Space math namespace */
namespace digl
{
  /* Window representation type */
  class win
  {
  protected:
    HWND hWnd;            // window handle
    INT W, H;             // window size
    HINSTANCE hInstance;  // application handle
    INT MouseWheel;       // mouse wheel value

  private:
    /* Handle Messages function.
     * ARGUMENTS:
     *   - window discriptor:
     *       HWND hWnd;
     *   - message number:
     *       UINT Message;
     *   - message param:
     *       WPARAM wParam;
     *   - message param:
     *       LPARAM lParam;
     * RETURN:
     *   (LRESULT) result.
     */
    static LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg,
                                     WPARAM wParam, LPARAM lParam );

    BOOL IsFullScreen;        // Full screen flag
    RECT FullScreenSaveRect;  // Full screen rectangle
    BOOL IsInit;              // Initialization flag

  public:
    BOOL IsActive;  // Activation flag

    /* Window constructor function.
     * ARGUMENTS:
     *   - instance:
     *       HINSTANCE hInst;
     * RETUNRS: None.
     */
    win( HINSTANCE hInst = GetModuleHandle(NULL) );

    /* Destructor */
    ~win( VOID );

    /* Message handle loop function.
     * ARGUMENTS: None.
     * RETUNRS: None.
     */
    VOID Run( VOID );

    /* Flip full screen handle function.
     * ARGUMENTS: None.
     * RETUNRS: None.
     */
    VOID FlipFullScreen( VOID );

  private:
    /* Message cracks */

    /* Get minmax info handle function.
     * ARGUMENTS:
     *   - minmax info:
     *       MINMAXINFO *MinMax;
     * RETUNRS: None.
     */
    VOID OnGetMinMaxInfo( MINMAXINFO *MinMax );

    /* Window creation handle function.
     * ARGUMENTS:
     *   - creature struct:
     *       CREATESTRUCT *CS;
     * RETUNRS:
     *   (BOOL) creation result.
     */
    BOOL OnCreate( CREATESTRUCT *CS );

    /* Window resize handle function.
     * ARGUMENTS:
     *   - state:
     *       UINT State;
     *   - size:
     *       INT W, H;
     * RETUNRS: None.
     */
    VOID OnSize( UINT State, INT W, INT H );

    /* Timer handle function.
     * ARGUMENTS:
     *   - id:
     *       INT Id;
     * RETUNRS: None.
     */
    VOID OnTimer( INT Id );

    /* Mouse wheel handle function.
     * ARGUMENTS:
     *   - coords:
     *       INT X, Y, Z;
     *   - keys:
     *       UINT Keys;
     * RETUNRS: None.
     */
    VOID OnMouseWheel( INT X, INT Y, INT Z, UINT Keys );

    /* Left mouse button press down handle function.
     * ARGUMENTS:
     *   - double click flag:
     *       BOOL IsDblClick;
     *   - coords:
     *       INT X, Y, Z;
     *   - keys:
     *       UINT Keys;
     * RETUNRS: None.
     */
    VOID OnLButtonDown( BOOL IsDblClick, INT X, INT Y, UINT Keys );

    /* Left mouse button raising handle function.
     * ARGUMENTS:
     *   - coords:
     *       INT X, Z;
     *   - keys:
     *       UINT Keys;
     * RETUNRS: None.
     */
    VOID OnLButtonUp( INT X, INT Y, UINT Keys );

    /* Erase background handle function.
     * ARGUMENTS:
     *   - coords:
     *       INT X, Y, Z;
     *   - keys:
     *       UINT Keys;
     * RETUNRS:
     *   (BOOL) erase background result.
     */
    BOOL OnEraseBackground( HDC hDC );

    /* Paint handle function.
     * ARGUMENTS:
     *   - device context:
     *       HDC hDC;
     *   - paint struct:
     *       PAINTSTRUCT *PS;
     * RETUNRS: None.
     */
    VOID OnPaint( HDC hDC, PAINTSTRUCT *PS );

    /* Close handle function.
     * ARGUMENTS: None.
     * RETUNRS: None.
     */
    VOID OnClose( VOID );

    /* Destroy handle function.
     * ARGUMENTS: None.
     * RETUNRS: None.
     */
    VOID OnDestroy( VOID );

    /* Activate handle function.
     * ARGUMENTS:
     *   - reason:
     *       UINT Reason.
     *   - window act/deact:
     *       HWND hWndActDeact;
     *   - minimized flag:
     *       BOOL IsMinimized;
     * RETUNRS: None.
     */
    VOID OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized );

    /* Callbacks */

    /* Initialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Init( VOID )
    {
    } /* End of 'Init' function */

    /* Close function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Close( VOID )
    {
    } /* End of 'Close' function */

    /* Resize function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Resize( VOID )
    {
    } /* End of 'Resize' function */

    /* Timer function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Timer( VOID )
    {
    } /* End of 'Timer' function */

    /* Activate function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Activate( VOID )
    {
    } /* End of 'Activate' function */

    /* Idle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Idle( VOID )
    {
    } /* End of 'Idle' function */

    /* Erase function.
     * ARGUMENTS:
     *   - device context:
     *       HDC hDC;
     * RETURNS: None.
     */
    virtual VOID Erase( HDC hDC )
    {
    } /* End of 'Erase' function */

    /* Paint function.
     * ARGUMENTS:
     *   - device context:
     *       HDC hDC;
     * RETURNS: None.
     */
    virtual VOID Paint( HDC hDC )
    {
    } /* End of 'Paint' function */
  }; /* End of 'win' class */
} /* end of 'digl' namespace */

#endif /* __WIN_H_*/

/* END OF 'win.h' FILE */

