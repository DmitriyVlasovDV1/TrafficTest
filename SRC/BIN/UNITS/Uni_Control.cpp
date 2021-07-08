/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

 /* FILE NAME   : Uni_Control.h
  * PURPOSE     : Control unit file.
  * PROGRAMMER  : Dmitriy Vlasov.
  * LAST UPDATE : 18.08.2020
  * NOTE        : Namespace 'digl'.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
  */

/* Includes */
#include "../../ANIM/anim.h"
#include "../../UTILS/physics.h"

/* Animation project namespace */
using namespace digl;

/* Control unit class */
class control_unit : public units::unit
{
private:
  const FLT MouseRotationCoef = 0.2;
  const FLT RotationCoef = 1;
  const FLT StrideCoef = 10;
  vec3 &Loc, &At, &Dir, &Up, &Right;
  vec2 RotationParams, RotationAngles, StrideParams;
  kinematics Rotation, Stride;

  DBL LastTimeResponse;

public:
  control_unit(anim *AC) :
    RotationParams(0), RotationAngles(0), StrideParams(0),
    Loc(AC->Cam.Loc), At(AC->Cam.At), Dir(AC->Cam.Dir), Up(AC->Cam.Up), Right(AC->Cam.Right),
    LastTimeResponse(AC->GlobalTime), Rotation(), Stride()
  {
    RotationAngles[0] = std::atan2(-Dir.Normalizing() & vec3(1, 0, 0), -Dir.Normalizing() & vec3(0, 0, 1));
    RotationAngles[1] = std::asin(-Dir.Normalizing() & vec3(0, 1, 0));

    Init(3, 5, -5, 5, 20, -100);
  }

  /* Initialization function.
   * ARGUMENTS:
   *   - rotation and stride speed params:
   *       FLT NewRotationSpeed, NewRotationAccelStart, 
   *           NewRotationAccelStop, NewStrideSpeed,
   *           NewStrideAccelStart, NewStrideAccelStop
   * RETURNS: None.
   */
  VOID Init( FLT NewRotationSpeed, FLT NewRotationAccelStart, FLT NewRotationAccelStop,
    FLT NewStrideSpeed, FLT NewStrideAccelStart, FLT NewStrideAccelStop )
  {
    Rotation.Init(TRUE, 0, 0, NewRotationSpeed);
    Rotation.AddAccelToList(NewRotationAccelStart);
    Rotation.AddAccelToList(NewRotationAccelStop);

    Stride.Init(TRUE, 0, 0, NewStrideSpeed);
    Stride.AddAccelToList(NewRotationAccelStart);
    Stride.AddAccelToList(NewRotationAccelStop);
  } /* End of 'Init' function */

  /* Destructor */
  ~control_unit(VOID)
  {
  } /* End of '~control_unit' function */

  /* Response function.
   * ARGUMENTS:
   *   - animation context:
   *       anim *AC;
   * RETURNS: None.
   */
  VOID Response( anim *AC ) override
  {
    /* Pause */
    if (AC->input::keyboard::KeysClick[80])
      AC->timer::IsPause = !AC->timer::IsPause;

    /* Keyboard response */

    /* 'W' and 'S' button */
    FLT StrideUp = AC->input::keyboard::Keys[87] - AC->input::keyboard::Keys[83],
    /* 'A' and 'D' button */
      StrideRight = AC->input::keyboard::Keys[68] - AC->input::keyboard::Keys[65],
    /* Up and Down arrow */
      RotationUp = AC->input::keyboard::Keys[38] - AC->input::keyboard::Keys[40],
    /* Left and Right arrow */
      RotationRight = AC->input::keyboard::Keys[39] - AC->input::keyboard::Keys[37];

    /* Mouse response */
    if (AC->input::keyboard::Keys[1])
    {
      RotationRight = -AC->Dx * MouseRotationCoef;
      RotationUp = AC->Dy * MouseRotationCoef;
    }

    if (AC->Dz)
    {
      vec3 V = Dir.Normalizing() * AC->Dz * 0.0005 * !(Loc - At);

      /* Checking 'shift' */
      AC->Cam.SetView(Loc + V, At, vec3(0, 1, 0));
    }

    /* Set accelration and direction */
    if (RotationUp || RotationRight)
    {
      Rotation.SetAccelFromList(0);
      RotationParams.Set(RotationRight * RotationCoef,
                         RotationUp * RotationCoef);
    }
    else
      Rotation.SetAccelFromList(1);

    if (StrideUp || StrideRight)
    {
      Stride.SetAccelFromList(0);
      StrideParams.Set(StrideRight * StrideCoef,
                       StrideUp * StrideCoef);
    }
    else
      Stride.SetAccelFromList(1);

    /* Compute movement */
    Rotation.Compute();
    Stride.Compute();

    if (Rotation.DeltaValue)
    {
      RotationAngles[0] = RotationAngles[0] + RotationParams[0] * Rotation.DeltaValue;
      RotationAngles[1] = mth::Span<FLT>(-0.49 * PI , 0.49 * PI, RotationAngles[1] + RotationParams[1] * Rotation.DeltaValue);
    }
    vec3 V = (matr::RotateX(-R2D(RotationAngles[1])) *
      matr::RotateY(R2D(RotationAngles[0]))).TransformPoint(vec3(0, 0, 1) * !Dir);
    AC->Cam.SetView(At + V, At, vec3(0, 1, 0));

    if (Stride.DeltaValue && 0)
    {
      vec3 V;

      /* Checking 'shift' */
      if (AC->input::keyboard::Keys[16])
        V = (Right * StrideParams[0] + vec3(0, 1, 0) * StrideParams[1]) * Stride.DeltaValue;
      else
        V = (Right * StrideParams[0] + (vec3(0, 1, 0) % Right) * StrideParams[1]) * Stride.DeltaValue;

      AC->Cam.SetView(Loc + V, At + V, vec3(0, 1, 0));
    }
  }
};

static digl::anim::unit_register<control_unit> _("Control");
