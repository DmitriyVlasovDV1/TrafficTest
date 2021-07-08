/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : mth_cam.h
 * PURPOSE     : Camera header file.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 27.07.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */

#ifndef __MTH_CAM_H_
#define __MTH_CAM_H_

#include "mthdef.h"

/* Math namespace */
namespace mth
{

  class camera
  {
  public:

    matr<FLT> View; // View matrix.
    matr<FLT> Proj; // Projection matrix.
    matr<FLT> VP;   // Multiply of view and projection matrices.
    const FLT
      Near,     // Near clip plane.
      Far,      // Far clip plane.
      ProjSize; // Projection basic size.

    vec3<FLT> Loc, At, Dir, Up, Right;

    /* Camera constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    camera ( FLT Near = 0.1, FLT Far = 1000, FLT ProjSize = 0.1 ) : 
      View(), Proj(), VP(), Near(Near), Far(Far), ProjSize(ProjSize),
      Loc(0), At(0), Dir(0), Right(0), Up(0)
    {
    } /* End of 'camera' function */

    /* Set projection function.
      * ARGUMENTS:
      *   - window size:
      *       const UINT W, H;
      * RETURNS:
      *   (camera &) camera it self.
      */
    camera & SetProj( const FLT W, const FLT H )
    {
      FLT ratio_x = ProjSize / 2, ratio_y = ratio_x;

      if (W > H)
        ratio_x *= W / H;
      else
        ratio_y *= H / W;

      Proj = matr<FLT>::Frustum(-ratio_x, ratio_x, -ratio_y, ratio_y, Near, Far);
      VP = View * Proj;

      return *this;
    } /* End of 'SetProj' function */

    /* Set view function.
      * ARGUMENTS:
      *   - camera location:
      *       const vec3<type> &Loc;
      *   - camera look to point:
      *       const vec3<type> &At;
      *   - camera up vector:
      *       const vec3<type> &Up1;
      * RETURNS:
      *   (camera &) camera it self.
      */
    camera & SetView( const vec3<FLT> &NewLoc, const vec3<FLT> &NewAt, const vec3<FLT> &Up1 )
    {
      Loc = NewLoc;
      At = NewAt;
      Dir = At - Loc;
      Right = (Dir % Up1).Normalizing();
      Up = (Right % Dir).Normalizing();

      View = matr<FLT>::ViewLookAt(Loc, At, Up1);

      VP = View * Proj;
      return *this;
    } /* End of 'SetView' function */
  };
} /* end of 'mth' namespace */

#endif /* __MTH_CAM_H_ */

/* END OF 'mth_cam.h' file */