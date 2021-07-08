/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : physics.cpp
 * PURPOSE     : physics utils file.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 10.09.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */

/* Includes */
#include "../ANIM/anim.h"
#include "physics.h"

/* Animation project namespace */
namespace digl
{
  /* Kinematic constructor function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  kinematics::kinematics( VOID ) :
    IsPauseIgnore(TRUE), TimeLastComputation(anim::GetPtr()->GlobalTime),
    SpeedMin(0), SpeedMax(0), SpeedCur(0), AccelCur(0),
    DeltaValue(0), StartValue(0), Value(0), Accels()
  {
  } /* End of 'kinematic' function */

  /* Kinematics copy constructor function.
   * ARGUMENTS:
   *   - value for copy:
   *       const kinematics &Val;
   * RETURNS: None.
   */
  kinematics::kinematics( const kinematics &Val ) :
    IsPauseIgnore(Val.IsPauseIgnore),
    SpeedMin(Val.SpeedMin),
    SpeedMax(Val.SpeedMax),
    SpeedCur(Val.SpeedCur),
    AccelCur(Val.AccelCur),
    TimeLastComputation(Val.IsPauseIgnore ? anim::GetPtr()->GlobalTime : anim::GetPtr()->Time),
    DeltaValue(0), StartValue(0), Value(0),
    Accels()
    {
      Accels = Val.Accels;
    } /* End of 'kinematics' function */

  /* Kinematics constructor function.
   * ARGUMENTS:
   *   - max and min speed:
   *       (const Type &) InSpeedMax, InSpeedMin;
   * RETURNS: None.
   */
  kinematics::kinematics( const BOOL InIsPauseIgnore, const FLT &InStartValue,
    const FLT &InSpeedMin, const FLT &InSpeedMax,
    const FLT &InSpeedCur, const FLT &InAccelCur ) :
    IsPauseIgnore(InIsPauseIgnore),
    TimeLastComputation(IsPauseIgnore ? anim::GetPtr()->GlobalTime : anim::GetPtr()->Time),
    SpeedMin(InSpeedMin),
    SpeedMax(InSpeedMax),
    SpeedCur(InSpeedCur),
    AccelCur(InAccelCur),
    Accels(),
    StartValue(InStartValue),
    DeltaValue(0),
    Value(InStartValue)
    {
    } /* End of 'kinematics' function */

  /* Initialization */
  VOID kinematics::Init( const BOOL InIsPauseIgnore, const FLT &InStartValue,
    const FLT &InSpeedMin, const FLT &InSpeedMax,
    const FLT &InSpeedCur, const FLT &InAccelCur )
    {
      IsPauseIgnore = InIsPauseIgnore;
      SpeedMin = InSpeedMin;
      SpeedMax = InSpeedMax;
      SpeedCur = InSpeedCur;
      AccelCur = InAccelCur;
      StartValue = InStartValue;
      Value = StartValue;
    } /* End of 'Init' function */

  /* Set current acceleration function.
   * ARGUMENTS:
   *   - acceleration:
   *       const Type &InAccel;
   * RETURNS: None.
   */
  VOID kinematics::SetAccel( const FLT &InAccel )
  {
    AccelCur = InAccel;
  } /* End of 'SetAccel' function */

  /* Add acceleration in list function.
   * ARGUMENTS:
   *   - accleration:
   *       const Type &Accel;
   * RETURNS: None.
   */
  VOID kinematics::AddAccelToList( const FLT &Accel )
  {
    Accels.push_back(Accel);
  } /* End of 'AddAccelToList' function */

  /* Set current acceleration from list function.
   * ARGUMENTS:
   *   - index of accleration:
   *       const INT Ind;
   * RETURNS: None.
   */
  VOID kinematics::SetAccelFromList( const INT Ind )
  {
    AccelCur = Accels[Ind];
  } /* End of 'SetAccelFromList' function */

  /* Compute speed and acceleration function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID kinematics::Compute( VOID )
  {
    anim *AC = anim::GetPtr();
    /* Compute delta time */
    DBL DeltaTime;
    if (IsPauseIgnore)
    {
      DeltaTime = AC->GlobalTime - TimeLastComputation;
      TimeLastComputation = AC->GlobalTime;
    }
    else
    {
      DeltaTime = AC->Time - TimeLastComputation;
      TimeLastComputation = AC->Time;
    }

    /* Compute delta value */
    if (SpeedCur == SpeedMax || SpeedCur == SpeedMin)
      DeltaValue = SpeedCur * DeltaTime;
    else
      DeltaValue = (SpeedCur + AccelCur * 0.5 * DeltaTime) * DeltaTime;
    Value += DeltaValue;

    /* Compute speed */
    SpeedCur = mth::Span<FLT>(SpeedMin, SpeedMax, SpeedCur + AccelCur * DeltaTime);
  } /* End of 'Compute' function */

  /* Kinematic constructor function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  kinematicsVec::kinematicsVec( VOID ) :
    IsPauseIgnore(TRUE), TimeLastComputation(anim::GetPtr()->GlobalTime),
    SpeedMin(0), SpeedMax(0), SpeedCur(0), AccelCur(0),
    DeltaValue(0), StartValue(0), Value(0), Accels()
  {
  } /* End of 'kinematic' function */

  /* Kinematics copy constructor function.
   * ARGUMENTS:
   *   - value for copy:
   *       const kinematics &Val;
   * RETURNS: None.
   */
  kinematicsVec::kinematicsVec( const kinematicsVec &Val ) :
    IsPauseIgnore(Val.IsPauseIgnore),
    SpeedMin(Val.SpeedMin),
    SpeedMax(Val.SpeedMax),
    SpeedCur(Val.SpeedCur),
    AccelCur(Val.AccelCur),
    TimeLastComputation(Val.IsPauseIgnore ? anim::GetPtr()->GlobalTime : anim::GetPtr()->Time),
    DeltaValue(0), StartValue(0), Value(0),
    Accels()
  {
    Accels = Val.Accels;
  } /* End of 'kinematics' function */

  /* Kinematics constructor function.
   * ARGUMENTS:
   *   - max and min speed:
   *       (const Type &) InSpeedMax, InSpeedMin;
   * RETURNS: None.
   */
  kinematicsVec::kinematicsVec( const BOOL InIsPauseIgnore, const vec3 &InStartValue,
    const FLT &InSpeedMin, const FLT &InSpeedMax,
    const vec3 &InSpeedCur, const vec3 &InAccelCur) :
    IsPauseIgnore(InIsPauseIgnore),
    TimeLastComputation(IsPauseIgnore ? anim::GetPtr()->GlobalTime : anim::GetPtr()->Time),
    SpeedMin(InSpeedMin),
    SpeedMax(InSpeedMax),
    SpeedCur(InSpeedCur),
    AccelCur(InAccelCur),
    Accels(),
    StartValue(InStartValue),
    DeltaValue(0),
    Value(InStartValue)
  {
  } /* End of 'kinematics' function */

  /* Initialization */
  VOID kinematicsVec::Init( const BOOL InIsPauseIgnore, const vec3 &InStartValue,
    const FLT &InSpeedMin, const FLT &InSpeedMax,
    const vec3  &InSpeedCur, const vec3 &InAccelCur )
  {
    IsPauseIgnore = InIsPauseIgnore;
    SpeedMin = InSpeedMin;
    SpeedMax = InSpeedMax;
    SpeedCur = InSpeedCur;
    AccelCur = InAccelCur;
    StartValue = InStartValue;
    Value = StartValue;
    TimeLastComputation = IsPauseIgnore ? anim::GetPtr()->GlobalTime : anim::GetPtr()->Time;
  } /* End of 'Init' function */

  /* Set current acceleration function.
   * ARGUMENTS:
   *   - acceleration:
   *       const Type &InAccel;
   * RETURNS: None.
   */
  VOID kinematicsVec::SetAccel( const vec3 &InAccel )
  {
    AccelCur = InAccel;
  } /* End of 'SetAccel' function */

  /* Add acceleration in list function.
   * ARGUMENTS:
   *   - accleration:
   *       const Type &Accel;
   * RETURNS: None.
   */
  VOID kinematicsVec::AddAccelToList( const vec3 &Accel )
  {
    Accels.push_back(Accel);
  } /* End of 'AddAccelToList' function */

  /* Set current acceleration from list function.
   * ARGUMENTS:
   *   - index of accleration:
   *       const INT Ind;
   * RETURNS: None.
   */
  VOID kinematicsVec::SetAccelFromList( const INT Ind )
  {
    AccelCur = Accels[Ind];
  } /* End of 'SetAccelFromList' function */

  /* Compute speed and acceleration function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID kinematicsVec::Compute( VOID )
  {
    anim *AC = anim::GetPtr();
    /* Compute delta time */
    DBL DeltaTime;
    if (IsPauseIgnore)
    {
      DeltaTime = AC->GlobalTime - TimeLastComputation;
      TimeLastComputation = AC->GlobalTime;
    }
    else
    {
      DeltaTime = AC->Time - TimeLastComputation;
      TimeLastComputation = AC->Time;
    }

    /* Compute delta value */
    if (!SpeedCur == SpeedMax || !SpeedCur == SpeedMin)
      DeltaValue = SpeedCur * DeltaTime;
    else
      DeltaValue = (SpeedCur + AccelCur * 0.5 * DeltaTime) * DeltaTime;
    Value += DeltaValue;

    /* Compute speed */
    SpeedCur = SpeedCur + AccelCur * DeltaTime;
    if (!SpeedCur > SpeedMax)
      SpeedCur = SpeedCur.Normalizing() * SpeedMax;
    else if (!SpeedCur < SpeedMin)
      SpeedCur = SpeedCur.Normalizing() * SpeedMin;
  } /* End of 'Compute' function */
} /* end of 'digl' namespace */

/* END OF 'physics.cpp' FILE */


