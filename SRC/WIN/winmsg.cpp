/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : winmsg.cpp
 * PURPOSE     : Window message functions.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 20.08.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */

/* Includes */
#include "win.h"

/* Window name */
#define WND_CLASS_NAME "Win"

/* Timer id */
#define TIMER_ID1 30
#define TIMER_ID2 47

/* Window constructor function.
 * ARGUMENTS:
 *   - instance:
 *       HINSTANCE hInst;
 * RETUNRS: None.
 */
digl::win::win( HINSTANCE hInst ) :
  hWnd(0), W(700), H(700), hInstance(hInst), MouseWheel(0),
  IsFullScreen(FALSE), FullScreenSaveRect(), IsInit(FALSE), IsActive(TRUE)
{
  WNDCLASS wc;

  /* Set window params */
  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = sizeof(win *);
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(hInstance, 0);
  wc.hIcon = LoadIcon(NULL, IDI_ERROR);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = WinFunc;
  wc.lpszClassName = WND_CLASS_NAME;

  /* Class registration in system */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error rigister window class", "ERROR", MB_OK);
    return;
  }

  /* Window creation */
  hWnd = CreateWindow(WND_CLASS_NAME, "3D animation",
                      WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                      NULL, NULL, hInstance, reinterpret_cast<VOID *>(this));

  /* Show and redraw window */
  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);
} /* End of 'win' function */

/* Destructor */
digl::win::~win( VOID )
{
} /* End of '~win' function */

/* Message handle loop function.
 * ARGUMENTS: None.
 * RETUNRS: None.
 */
VOID digl::win::Run( VOID )
{
  MSG msg;

  while (TRUE)
  {
    /* Check message at window message queue */
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      if (msg.message == WM_QUIT)
        break;
      else
      {
        /* Displatch message to window */
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    else
    {
      if (IsInit)
        Idle();
    }
  }
} /* End of 'Run' function */

/* Flip full screen handle function.
 * ARGUMENTS: None.
 * RETUNRS: None.
 */
VOID digl::win::FlipFullScreen( VOID )
{
} /* End of 'FlipFullScreen' function */

/* Get minmax info handle function.
 * ARGUMENTS:
 *   - minmax info:
 *       MINMAXINFO *MinMax;
 * RETUNRS: None.
 */
VOID digl::win::OnGetMinMaxInfo( MINMAXINFO *MinMax )
{
} /* End of 'OnGetMinMaxInfo' function */

/* Window creation handle function.
 * ARGUMENTS:
 *   - creature struct:
 *       CREATESTRUCT *CS;
 * RETUNRS:
 *   (BOOL) creation result.
 */
BOOL digl::win::OnCreate( CREATESTRUCT *CS )
{
  SetTimer(hWnd, TIMER_ID1, 100, NULL);
  return TRUE;
} /* End of 'OnCreate' function */

/* Window resize handle function.
 * ARGUMENTS:
 *   - state:
 *       UINT State;
 *   - size:
 *       INT W, H;
 * RETUNRS: None.
 */
VOID digl::win::OnSize( UINT State, INT W, INT H )
{
  this->W = W;
  this->H = H;

  if (IsInit)
    Resize();
} /* End of 'OnSize' function */

/* Timer handle function.
 * ARGUMENTS:
 *   - id:
 *       INT Id;
 * RETUNRS: None.
 */
VOID digl::win::OnTimer( INT Id )
{
  if (!IsInit)
  {
    KillTimer(hWnd, TIMER_ID1);
    SetTimer(hWnd, TIMER_ID2, 1, NULL);

    IsInit = TRUE;
    /* Call callbacks */
    Init();
    Resize();
    Timer();
  }
  else
    Timer();
} /* End of 'OnTimer' function */

/* Mouse wheel handle function.
 * ARGUMENTS:
 *   - coords:
 *       INT X, Y, Z;
 *   - keys:
 *       UINT Keys;
 * RETUNRS: None.
 */
VOID digl::win::OnMouseWheel( INT X, INT Y, INT Z, UINT Keys )
{
  MouseWheel += Z;
} /* End of 'OnMouseWheel' function */

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
VOID digl::win::OnLButtonDown( BOOL IsDblClick, INT X, INT Y, UINT Keys )
{
} /* End of 'OnLButtonDown' function */

/* Left mouse button raising handle function.
 * ARGUMENTS:
 *   - coords:
 *       INT X, Z;
 *   - keys:
 *       UINT Keys;
 * RETUNRS: None.
 */
VOID digl::win::OnLButtonUp( INT X, INT Y, UINT Keys )
{
} /* End of 'OnLButtonUp' function */

/* Erase background handle function.
 * ARGUMENTS:
 *   - coords:
 *       INT X, Y, Z;
 *   - keys:
 *       UINT Keys;
 * RETUNRS:
 *   (BOOL) erase background result.
 */
BOOL digl::win::OnEraseBackground( HDC hDC )
{
  if (IsInit)
    Erase(hDC);

  return TRUE;
} /* End of 'OnEraseBackground' function */

/* Paint handle function.
 * ARGUMENTS:
 *   - device context:
 *       HDC hDC;
 *   - paint struct:
 *       PAINTSTRUCT *PS;
 * RETUNRS: None.
 */
VOID digl::win::OnPaint( HDC hDC, PAINTSTRUCT *PS )
{
  if (IsInit)
    Paint(hDC);
} /* End of 'OnPaint' function */

/* Close handle function.
 * ARGUMENTS: None.
 * RETUNRS: None.
 */
VOID digl::win::OnClose( VOID )
{
  Close();
} /* End of 'OnClose' function */

/* Destroy handle function.
 * ARGUMENTS: None.
 * RETUNRS: None.
 */
VOID digl::win::OnDestroy( VOID )
{
  if (IsInit)
  {
    Close();
    KillTimer(hWnd, TIMER_ID2);
  }
  else
    KillTimer(hWnd, TIMER_ID1);
} /* End of 'OnDestroy' function */

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
VOID digl::win::OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized )
{
  if (IsInit)
    Activate();
} /* End of 'OnActivate' function */

/* END OF 'winmsg.cpp' FILE */
