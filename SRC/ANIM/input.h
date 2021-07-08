/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : input.h
 * PURPOSE     : Input module.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 24.07.2020
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */

#ifndef _INPUT_H_
#define _INPUT_H_

#include "../def.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm")

/* Animation project namespace */
namespace digl
{
  #define GET_JOYSTIC_AXIS(A) (2.0 * (ji.dw ## A ## pos - jc.w ## A ## min) \
                              / (jc.w ## A ## max - jc.w ## A ## min) - 1)

  /* Mouse representation type */
  class mouse
  {
  private:
    INT &Wheel, X, Y, Z;
    HWND &hWnd;
  public:
    INT Dx, Dy, Dz;

    /* Mouse constructor.
     * ARGUMENTS:
     *   - mouse wheel value:
     *       INT &WheelRef;
     * RETURNS: None.
     */
    mouse( INT &WheelRef, HWND &hWndRef ) : Wheel(WheelRef), hWnd(hWndRef),
      X(0), Y(0), Z(0), Dx(0), Dy(0), Dz(0)
    {
    } /* End of 'mouse' function */

    /* Mouse response function. 
     * ARGUMJENTS: None.
     * RETURNS: None.
     */
    VOID Response ( VOID )
    {
      POINT pt;

      GetCursorPos(&pt);
      ScreenToClient(hWnd, &pt);

      Dx = pt.x - X;
      Dy = pt.y - Y;
      Dz = Wheel - Z;

      X = pt.x;
      Y = pt.y;
      Z = Wheel;
    }
  }; /* End of 'mouse' class */

  /* Keyboard representation type */
  class keyboard
  {
  public:
    BYTE Keys[256];
    BYTE KeysOld[256];
    BYTE KeysClick[256];

    /* Keyboard constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    keyboard( VOID )
    {
    } /* End of 'keyboard' function */

    /* Keyboard responsefunction.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Response( VOID )
    {
      GetKeyboardState(Keys);

      for (int i = 0; i < 256; i++)
      {
        Keys[i] >>= 7;
        KeysClick[i] = Keys[i] && !KeysOld[i];
      }
      memcpy(KeysOld, Keys, 256);
    } /* End of 'Êesponse' function */
  }; /* End of 'keyboard' class */

  /* Joystick representation type */
  class joystick
  {

    VOID Response ( VOID )
    {
      BYTE But[32],
           ButOld[32],
           ButClick[32];
      INT Pov;
      DBL X, Y, Z, R;

      if (joyGetNumDevs() > 0)
      {
        JOYCAPS jc;

        if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
        {
          JOYINFOEX ji;

          ji.dwSize = sizeof(JOYINFOEX);
          ji.dwFlags = JOY_RETURNALL;
          if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
          {
            /* Buttons */
            for (int i = 0; i < 32; i++)
            {
              But[i] = (ji.dwButtons >> i) & 1;
              ButClick[i] = But[i] && !ButOld[i];
              ButOld[i] = But[i];
            }

            /* Axes */
            X = GET_JOYSTIC_AXIS(X);
            Y = GET_JOYSTIC_AXIS(Y);
            Z = GET_JOYSTIC_AXIS(Z);
            R = GET_JOYSTIC_AXIS(R);

            /* Point of view */
            Pov = ji.dwPOV == 0xFFFF ? -1 : ji.dwPOV / 4500;
          }
        }
      }
    } /* End of 'Response' function */
  }; /* End of 'joystick' class */

  /* Input representation type */
  class input : public keyboard, public mouse, public joystick
  {
  public:
    input( INT &WheelRef, HWND &hWndRef ) : mouse(WheelRef, hWndRef), keyboard(), joystick()
    {
    } /* End of 'input' function */

    VOID Response( VOID )
    {
      keyboard::Response();
      mouse::Response();
    } /* End of 'response' function */

  }; /* End of 'input' class */
} /* end of 'digl' namespace */

#endif /* _INPUT_H_ */

/* END OF 'input.h' FILE */
