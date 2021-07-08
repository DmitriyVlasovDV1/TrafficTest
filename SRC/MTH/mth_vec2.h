/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : mth_vec.h
 * PURPOSE     : Vectors header file.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 24.07.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */

#ifndef __MTH_VEC2_
#define __MTH_VEC2_

/* Includes */
#include "mthdef.h"

/* Space math namespace */
namespace mth
{
  /* 2D vector representation type */
  template<typename Type>
    class vec2
    {
    template<class Type1>
      friend class matr;

    private:
      Type X, Y;  // Components

    public:
      /* Constructor.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      vec2( VOID ): X(0), Y(0)
      {
      } /* End of 'vec2' function */

      /* Constructor.
       * ARGUMENTS:
       *   - components:
       *       Type x, y;
       * RETURNS: None.
       */
      vec2( Type x, Type y ) : X(x), Y(y)
      {
      } /* End of 'vec2' function */

      /* Constructor.
       * ARGUMENTS:
       *   - component:
       *       Type x;
       * RETURNS: None.
       */
      vec2( Type x ) : X(x), Y(x)
      {
      } /* End of 'vec2' function */

      /* Set vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2 &) this vector.
       */
      vec2 & Set( VOID )
      {
        this->X = 0;
        this->Y = 0;
        return *this;
      } /* End of 'Set' function */

      /* Set vector function.
       * ARGUMENTS:
       *   - components:
       *       const Type x, y;
       * RETURNS:
       *   (vec2 &) this vector.
       */
      vec2 & Set( const Type x, const Type y )
      {
        this->X = x;
        this->Y = y;
        return *this;
      } /* End of 'Set' function */

      /* Set vector function.
       * ARGUMENTS:
       *   - component:
       *       const Type x;
       * RETURNS:
       *   (vec2 &) this vector.
       */
      vec2 & Set( const Type x )
      {
        this->X = x;
        this->Y = x;
        return *this;
      } /* End of 'Set' function */

      /* Get vector length function.
      * ARGUMENTS: None.
      * RETURNS: None.
      */
      Type operator!( VOID ) const
      {
        return sqrt(X * X + Y * Y);
      } /* End of 'operator!' function */

      /* Vector sum function.
       * ARGUMENTS:
       *   - vector:
       *       const vec2 &V;
       * RETURNS:
       *   (vec3) result vector;
       */
      vec2 operator+( const vec2 &V ) const
      {
        return vec2(X + V.X, Y + V.Y);
      } /* End of 'operator+' function */

      /* Vector sum-assign function.
       * ARGUMENTS:
       *   - vector:
       *       const vec2 &V;
       * RETURNS:
       *   (vec3 &) this vector;
       */
      vec2 & operator+=( const vec2 &V )
      {
        X += V.X;
        Y += V.Y;
        return *this;
      } /* End of 'operator+=' function */

      /* Vector sub function.
       * ARGUMENTS:
       *   - vector:
       *       const vec2 &V;
       * RETURNS:
       *   (vec3) result vector;
       */
      vec2 operator-( const vec2 &V ) const
      {
        return vec2(X - V.X, Y - V.Y);
      } /* End of 'operator-' */

      /* Inverse vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2 &) this vector;
       */
      vec2 & operator-( VOID )
      {
        X = -X;
        Y = -Y;
        return *this;
      } /* End of 'operator-' */
      ////////////////////////////////////////////////
      /* Vector sub-assign function.
       * ARGUMENTS:
       *   - vector:
       *       const vec2 &V;
       * RETURNS: (vec2 &) this vector;
       */
      vec2 & operator-=( const vec2 &V )
      {
        X -= V.X;
        Y -= V.Y;
        return *this;
      } /* End of 'operator-=' function */

      /* Component multiplication function.
       * ARGUMENTS:
       *   - vector:
       *       const vec2 &V;
       * RETURNS: (vec2) multiplication result vector.
       */
      vec2 operator*( const vec2 &V ) const
      {
        return vec2(X * V.X, Y * V.Y);
      } /* End of 'operator*' function */

      /* Component mul-assign function.
       * ARGUMENTS:
       *   - vector:
       *       const vec2 &V;
       * RETURNS: (vec2 &) this vector;
       */
      vec2 & operator*=( const vec2 &V )
      {
        X *= V.X;
        Y *= V.Y;
        return *this;
      } /* End of 'operator*=' function */

      /* Vector multiply number function.
       * ARGUMENTS:
       *   - number:
       *       const Type &N;
       * RETURNS: (vec2) multiplication result.
       */
      vec2 operator*( const Type &N ) const
      {
        return vec2(X * N, Y * N);
      } /* End of 'operator*' function */

      /* Vector mul-assign function.
       * ARGUMENTS:
       *   - vector:
       *       const vec2 &V;
       * RETURNS: (vec2 &) this vector;
       */
      vec2 & operator*=( const Type &N )
      {
        X *= N;
        Y *= N;
        return *this;
      } /* End of 'operator*=' function */

      /* Vector divide number function.
       * ARGUMENTS:
       *   - number:
       *       const Type &N;
       * RETURNS: (vec2) multiplication result.
       */
      vec2 operator/( const Type &N ) const
      {
        return vec2(X / N, Y / N);
      } /* End of 'operator/' function */

      /* Vector div-assign function.
       * ARGUMENTS:
       *   - vector:
       *       const vec2 &V;
       * RETURNS: (vec2 &) this vector;
       */
      vec2 & operator/=( const Type &N )
      {
        X /= N;
        Y /= N;
        return *this;
      } /* End of 'operator/=' function */

      /* Scalar multiplication function.
       * ARGUMENTS:
       *   - vector:
       *       const vec2 &V;
       * RETURNS: (Type) multiplication result.
       */
      Type operator&( const vec2 &V ) const
      {
        return X * V.X + Y * V.Y;
      } /* End of 'operator&' function */

      /* Vector multiplication function.
       * ARGUMENTS:
       *   - vector:
       *       const vec2 &V;
       * RETURNS: (vec2) multiplication result.
       */
      vec2 operator%( const vec2 &V ) const
      {
        return vec2(X * V.Y - Y * V.X);
      } /* End of 'operator%' function */

      /* Get component value function.
       * ARGUMENTS:
       *   - index:
       *       INT &i;
       * RETURNS: (Type) component value;
       */
      Type & operator[]( INT i )
      {
        if (i < 0)
          i = 0;
        else if (i > 1)
          i = 1;

        return *(&X + i);
      } /* End of 'operator[]' function */

      /* Get link to component function;
       * ARGUMENTS:
       *   - index:
       *       INT &i;
       * RETURNS: (Type &) component link;
       */
      Type operator[]( INT i ) const
      {
        if (i < 0)
          i = 0;
        else if (i > 1)
          i = 1;

        return *(&X + i);
      } /* End of 'operator[]' function */

      /* Get pointer to first component function;
       * ARGUMENTS: None.
       * RETURNS: (Type &) component link;
       */
      operator Type *( VOID ) const
      {
        return &X;
      } /* End of 'operator Type *' function */

      /* Self normalizing function.
       * ARGUMENTS: None.
       * RETURNS: (vec2 &) this vector.
       */
      vec2 & Normalize( VOID )
      {
        *this /= !*this;
        return *this;
      } /* End of 'Normalize' function */

      /* Vector normalizing function.
       * ARGUMENTS: None.
       * RETURNS: (vec2) normalized vector.
       */
      vec2 Normalizing( VOID ) const
      {
        return *this / !*this;
      } /* End of 'Normalizing' function */

      /* Get square length function.
       * ARGUMENTS: None.
       * RETURNS: (Type) square length.
       */
      Type Length2( VOID ) const
      {
        return (X * X + Y * Y);
      } /* End of 'Length2' function */

      /* Get distace to point function.
       * ARGUMENTS:
       *  - point:
       *      const vec2 &P;
       * RETURNS: (Type) distance.
       */
      Type Distance( const vec2 &P ) const
      {
        Type dX = X - P.X,
             dY = Y - P.Y;

        return sqrt(dX * dX + dY * dY);
      } /* End of 'Distance' function */

      /* Set zero components function.
       * ARGUMENTS: None.
       * RETURNS: (vec2 &) this vector.
       */
      vec2 & Zero( VOID )
      {
        X = 0;
        Y = 0;
        return *this;
      } /* End of 'Zero' function */

      /* Set random range [0; 1] components function.
       * ARGUMENTS: None.
       * RETURNS: (vec2 &) this vector.
       */
      vec2 & Rnd0( VOID )
      {
        X = rand() / RAND_MAX;
        Y = rand() / RAND_MAX;
        return *this;
      } /* End of 'Rnd0' function */

      /* Set random range [-1; 1] components function.
       * ARGUMENTS: None.
       * RETURNS: (vec2 &) this vector.
       */
      vec2 & Rnd1( VOID )
      {
        X = (rand() / RAND_MAX) * 2 - 1;
        Y = (rand() / RAND_MAX) * 2 - 1;
        return *this;
      } /* End of 'Rnd1' function */

    }; /* End of 'vec2' class */


} /* end of 'mth' namespace */

#endif /* __MTH_VEC2_ */
