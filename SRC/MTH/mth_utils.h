/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : mth_utils.h
 * PURPOSE     : Math utils headerfile.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 24.07.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */

#ifndef _math_utils_h_
#define _math_utils_h_

#include "mthdef.h"

/* Space math namespace */
namespace mth
{
  /* Get max value function.
   * ARGUMENTS:
   *   - values:
   *       (Type &) A, B;
   * RETURNS:
   *   (Type) Max value.
   */
  template<class Type>
    Type Max( const Type &A, const Type &B )
    {
      return A > B ? A : B;
    }  /* End of 'Max' function */

  /* Get min value function.
   * ARGUMENTS:
   *   - values:
   *       (Type &) A, B;
   * RETURNS:
   *   (Type) Min value.
   */
  template<class Type>
    Type Min( const Type &A, const Type &B )
    {
      return A < B ? A : B;
    }  /* End of 'Min' function */

  /* Get value in range function.
   * ARGUMENTS:
   *   - range values:
   *       (Type &) A;
   *   -
   * RETURNS:
   *   (Type) value.
   */
  template<class Type>
    Type Span( const Type &MinV, const Type &MaxV, const Type &V )
    {
      return Min(Max(V, MinV), MaxV);
    }  /* End of 'Span' function */


} /* end of 'mth' namespace */

#endif /* _utils_h_ */

/* END OF 'utils.h' FILE */

