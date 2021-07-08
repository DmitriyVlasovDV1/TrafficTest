/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TIMER.H
 * PURPOSE     : Timer module.
 * PROGRAMMER  : Vlasiv Dmitriy.
 * LAST UPDATE : 24.07.2020.
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef _TIMER_H_
#define _TIMER_H_

#include "../def.h"

/* Animation project namespace */
namespace digl
{
  /* Timer representation type */
  class timer
  {
  private:
    UINT64
      StartTime,
      OldTime,
      OldTimeFPS,
      PauseTime,
      TimePerSec,
      FrameCounter;
  public:
    DBL GlobalTime,        // Time from program start
        GlobalDeltaTime,   // Time from last frame
        Time,              // Time from program start (with pause)
        DeltaTime,         // Time from last frame (with pause)
        FPS;               // Frames-per-second value
  
    /* Pause flag */
    BOOL IsPause;

    /* Timer constructor.
     * AGUMENTS: None.
     * RETURNS: None.
     */
    timer( VOID ) : StartTime(0), OldTime(0), OldTimeFPS(0), PauseTime(0),
        TimePerSec(0), FrameCounter(0), GlobalTime(0), GlobalDeltaTime(0),
        Time(0), DeltaTime(0), FPS(30.0), IsPause(FALSE)
    {
      LARGE_INTEGER t;
      QueryPerformanceFrequency(&t);
      TimePerSec = t.QuadPart;
      QueryPerformanceCounter(&t);
      StartTime = OldTime = OldTimeFPS = t.QuadPart;
    } /* End of 'timer' constructor */

    /* Response function.
     * AGUMENTS: None.
     * RETURNS: None.
     */  
    VOID Response( VOID )
    {
      LARGE_INTEGER t;

      QueryPerformanceCounter(&t);

      GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
      GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;

      /* Time with pause */
      if (IsPause)
      {
        DeltaTime = 0;
        PauseTime += t.QuadPart - OldTime;
      }
      else
      {
        DeltaTime = GlobalDeltaTime;
        Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
      }

      /* FPS */
      FrameCounter++;

      if (t.QuadPart - OldTimeFPS > TimePerSec)
      {
        FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);
        OldTimeFPS = t.QuadPart;
        FrameCounter = 0;
      }

      OldTime = t.QuadPart;

    } /* End of 'Response' function */
  }; /* End of 'timer' class */
} /* end of 'digl' function */

#endif /* _TIMER_H_ */

/* END OF 'timer.h' FILE */
