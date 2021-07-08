/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : win.cpp
 * PURPOSE     : Window functions.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 20.08.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */

/* Includes */
#include "win.h"

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
LRESULT CALLBACK digl::win::WinFunc( HWND hWnd, UINT Msg,
                                     WPARAM wParam, LPARAM lParam )
{
  win *Win;
  HDC hDC;
  PAINTSTRUCT ps;
  
  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    return 0;
  case WM_CREATE:
    /* Attach 'this' pointer to window class to window */
    SetWindowLong(hWnd, 0, (DWORD)((CREATESTRUCT *)lParam)->lpCreateParams);
  default:
    Win = reinterpret_cast<win *>(GetWindowLong(hWnd, 0));
    if (Win != NULL)
      switch (Msg)
      {
      case WM_CREATE:
        Win->hWnd = hWnd;
        return Win->OnCreate((CREATESTRUCT *)lParam) ? 0 : -1;
      case WM_SIZE:
        Win->OnSize(wParam, LOWORD(lParam), HIWORD(lParam));
        return 0;
      case WM_ERASEBKGND:
        return (LRESULT)Win->OnEraseBackground((HDC)wParam);
      case WM_PAINT:
        hDC = BeginPaint(hWnd, &ps);
        Win->OnPaint(hDC, &ps);
        EndPaint(hWnd, &ps);
        return 0;
      case WM_TIMER:
        Win->OnTimer((UINT)wParam);
        return 0;
      case WM_MOUSEWHEEL:
        Win->OnMouseWheel((INT)(SHORT)LOWORD(lParam),
                          (INT)(SHORT)HIWORD(lParam),
                          (INT)(SHORT)HIWORD(wParam),
                          (UINT)(SHORT)LOWORD(wParam));
        return 0;
      case WM_LBUTTONDOWN:
      case WM_RBUTTONDOWN:
      case WM_MBUTTONDOWN:
        Win->OnLButtonDown(FALSE,
                           (INT)(SHORT)LOWORD(lParam),
                           (INT)(SHORT)HIWORD(lParam),
                           (UINT)(SHORT)LOWORD(wParam));
      case WM_LBUTTONUP:
      case WM_RBUTTONUP:
      case WM_MBUTTONUP:
        Win->OnLButtonUp((INT)(SHORT)LOWORD(lParam),
                           (INT)(SHORT)HIWORD(lParam),
                           (UINT)(SHORT)LOWORD(wParam));
        return 0;
      case WM_DESTROY:
        Win->OnDestroy();
        PostQuitMessage(30);
        return 0;
      }
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'WinFunc' function */

/* END OF 'win.cpp' FILE */