/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : physics.h
 * PURPOSE     : physics utils headerfile.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 10.09.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */

#ifndef __PHYSICS_H_
#define __PHYSICS_H_

/* Includes */
#include "../def.h"
#include <vector>

/* Animation project namespace */
namespace digl
{
  /* Kinematics representation type */
  class kinematics
  {
  private:
    BOOL IsPauseIgnore;
    DBL
      TimeLastComputation;

  public:
    FLT
      SpeedMin,
      SpeedMax,
      SpeedCur,
      AccelCur,
      DeltaValue,
      StartValue,
      Value;

    std::vector<FLT> Accels;

    /* Kinematic constructor function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    kinematics( VOID );

    /* Kinematics copy constructor function.
     * ARGUMENTS:
     *   - value for copy:
     *       const kinematics &Val;
     * RETURNS: None.
     */
    kinematics( const kinematics &Val );

    /* Kinematics constructor function.
     * ARGUMENTS:
     *   - max and min speed:
     *       (const Type &) InSpeedMax, InSpeedMin;
     * RETURNS: None.
     */
    kinematics( const BOOL InIsPauseIgnore, const FLT &InStartValue,
      const FLT &InSpeedMin, const FLT &InSpeedMax,
      const FLT &InSpeedCur = 0, const FLT &InAccelCur = 0 );

    /* Initialization */
    VOID Init( const BOOL InIsPauseIgnore, const FLT &InStartValue,
      const FLT &InSpeedMin, const FLT &InSpeedMax,
      const FLT &InSpeedCur = 0, const FLT &InAccelCur = 0 );

    /* Set current acceleration function.
     * ARGUMENTS:
     *   - acceleration:
     *       const Type &InAccel;
     * RETURNS: None.
     */
    VOID SetAccel( const FLT &InAccel );

    /* Add acceleration in list function.
     * ARGUMENTS:
     *   - accleration:
     *       const Type &Accel;
     * RETURNS: None.
     */
    VOID AddAccelToList( const FLT &Accel );

    /* Set current acceleration from list function.
     * ARGUMENTS:
     *   - index of accleration:
     *       const INT Ind;
     * RETURNS: None.
     */
    VOID SetAccelFromList( const INT Ind );

    /* Compute speed and acceleration function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Compute( VOID );
  }; /* End of 'kinematics' class */

  /*Vector kinematics representation type */
  class kinematicsVec
  {
  private:
    BOOL IsPauseIgnore;
    DBL
      TimeLastComputation;

  public:
    FLT
      SpeedMin,
      SpeedMax;

    vec3
      SpeedCur,
      AccelCur,
      DeltaValue,
      StartValue,
      Value;

    std::vector<vec3> Accels;

    /* Kinematic constructor function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    kinematicsVec( VOID );

    /* Kinematics copy constructor function.
     * ARGUMENTS:
     *   - value for copy:
     *       const kinematics &Val;
     * RETURNS: None.
     */
    kinematicsVec( const kinematicsVec &Val );

    /* Kinematics constructor function.
     * ARGUMENTS:
     *   - max and min speed:
     *       (const Type &) InSpeedMax, InSpeedMin;
     * RETURNS: None.
     */
    kinematicsVec( const BOOL InIsPauseIgnore, const vec3 &InStartValue,
      const FLT &InSpeedMin, const FLT &InSpeedMax,
      const vec3 &InSpeedCur = vec3(0), const vec3 &InAccelCur = vec3(0) );

    /* Initialization */
    VOID Init( const BOOL InIsPauseIgnore, const vec3 &InStartValue,
      const FLT &InSpeedMin, const FLT &InSpeedMax,
      const vec3 &InSpeedCur = vec3(0), const vec3 &InAccelCur = vec3(0) );

    /* Set current acceleration function.
     * ARGUMENTS:
     *   - acceleration:
     *       const Type &InAccel;
     * RETURNS: None.
     */
    VOID SetAccel( const vec3 &InAccel );

    /* Add acceleration in list function.
     * ARGUMENTS:
     *   - accleration:
     *       const Type &Accel;
     * RETURNS: None.
     */
    VOID AddAccelToList( const vec3 &Accel );

    /* Set current acceleration from list function.
     * ARGUMENTS:
     *   - index of accleration:
     *       const INT Ind;
     * RETURNS: None.
     */
    VOID SetAccelFromList( const INT Ind );

    /* Compute speed and acceleration function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Compute( VOID );
  }; /* End of 'kinematicsVec' class */
} /* end of 'digl' namespace */

#endif /* __PHYSICS_H_ */
/* END OF 'physics.h' FILE */


