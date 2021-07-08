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

#ifndef _math_vec_h_
#define _math_vec_h_

#include "mthdef.h"

/* Space math namespace */
namespace mth
{
  /* 4D vector representation type */
  template<typename Type>
    class vec4
    {
    template<class Type1>
      friend class matr;

    private:
      Type X, Y, Z, W;

    public:
      /* Constructor.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      vec4( VOID ): X(0), Y(0), Z(0), W(0)
      {
      } /* End of 'vec4' constructor */

      /* Constructor.
       * ARGUMENTS:
       *   - components:
       *       Type x, y, z, w;
       * RETURNS: None.
       */
      vec4( Type x, Type y, Type z, Type w ) : X(x), Y(y), Z(z), W(w)
      {
      } /* End of 'vec4' constructor */

      /* Constructor.
       * ARGUMENTS:
       *   - components:
       *       Type x;
       * RETURNS: None.
       */
      vec4( Type x ) : X(x), Y(x), Z(x), W(x)
      {
      } /* End of 'vec4' constructor */

      /* Get vector length function.
      * ARGUMENTS: None.
      * RETURNS: None.
      */
      Type operator!( VOID ) const
      {
        return sqrt(X * X + Y * Y + Z * Z + W * W);
      } /* End of 'operator!' function */

      /* Compare length function.
       * ARGUMENTS:
       *   - vectors for comaring:
       *     (const Type &) V1, V2.
       * RETURNS:
       *   (BOOL) Comparing result.
       */
      BOOL operator>( const vec4 &V ) const
      {
        return this->Length2() > V.Length2();
      } /* End of 'operator>' function */

     /* Compare length function.
      * ARGUMENTS:
      *   - vectors for comaring:
      *     (const Type &) V1, V2.
      * RETURNS:
      *   (BOOL) Comparing result.
      */
      BOOL operator<( const vec4 &V ) const
      {
        return this->Length2() < V.Length2();
      } /* End of 'operator<' function */

      /* Compare length function.
       * ARGUMENTS:
       *   - vectors for comaring:
       *     (const Type &) V1, V2.
       * RETURNS:
       *   (BOOL) Comparing result.
       */
      BOOL operator==( const vec4 &V ) const
      {
        return !(*this) == !V;
      } /* End of 'operator==' function */

      /* Vector sum function.
       * ARGUMENTS:
       *   - vector:
       *       const vec4 &V;
       * RETURNS: (vec4) result vector;
       */
      vec4 operator+( const vec4 &V ) const
      {
        return vec3(X + V.X, Y + V.Y, Z + V.Z, W + V.W);
      } /* End of 'operator+' function */

      /* Vector sum-assign function.
       * ARGUMENTS:
       *   - vector:
       *       const vec4 &V;
       * RETURNS: (vec4 &) this vector;
       */
      vec4 & operator+=( const vec4 &V )
      {
        X += V.X;
        Y += V.Y;
        Z += V.Z;
        W += V.W;
        return *this;
      } /* End of 'operator+=' function */

      /* Vector sub function.
       * ARGUMENTS:
       *   - vector:
       *       const vec4 &V;
       * RETURNS: (vec4) result vector;
       */
      vec4 operator-( const vec4 &V ) const
      {
        return vec4(X - V.X, Y - V.Y, Z - V.Z, W - V.W);
      } /* End of 'operator-' */

      /* Inverse vector function.
       * ARGUMENTS: None.
       * RETURNS: (vec4 &) this vector;
       */
      vec4 & operator-( VOID )
      {
        X = -X;
        Y = -Y;
        Z = -Z;
        W = -W;
        return *this;
      } /* End of 'operator-' */

      /* Vector sub-assign function.
       * ARGUMENTS:
       *   - vector:
       *       const vec4 &V;
       * RETURNS: (vec4 &) this vector;
       */
      vec4 & operator-=( const vec4 &V )
      {
        X -= V.X;
        Y -= V.Y;
        Z -= V.Z;
        W -= V.W;
        return *this;
      } /* End of 'operator-=' function */

      /* Component multiplication function.
       * ARGUMENTS:
       *   - vector:
       *       const vec4 &V;
       * RETURNS: (vec4) multiplication result vector.
       */
      vec4 operator*( const vec4 &V ) const
      {
        return vec4(X * V.X, Y * V.Y, Z * V.Z + W * V.W);
      } /* End of 'operator*' function */

      /* Component mul-assign function.
       * ARGUMENTS:
       *   - vector:
       *       const vec4 &V;
       * RETURNS: (vec4 &) this vector;
       */
      vec4 & operator*=( const vec4 &V )
      {
        X *= V.X;
        Y *= V.Y;
        Z *= V.Z;
        W *= V.W;
        return *this;
      } /* End of 'operator*=' function */

      /* Vector multiply number function.
       * ARGUMENTS:
       *   - number:
       *       const Type &N;
       * RETURNS: (vec4) multiplication result.
       */
      vec4 operator*( const Type &N ) const
      {
        return vec4(X * N, Y * N, Z * N, W * N);
      } /* End of 'operator*' function */

      /* Vector mul-assign function.
       * ARGUMENTS:
       *   - vector:
       *       const vec4 &V;
       * RETURNS: (vec4 &) this vector;
       */
      vec4 & operator*=( const Type &N )
      {
        X *= N;
        Y *= N;
        Z *= N;
        W *= N;
        return *this;
      } /* End of 'operator*=' function */

      /* Vector divide number function.
       * ARGUMENTS:
       *   - number:
       *       const Type &N;
       * RETURNS: (vec4) multiplication result.
       */
      vec4 operator/( const Type &N ) const
      {
        return vec4(X / N, Y / N, Z / N, W / N);
      } /* End of 'operator/' function */

      /* Vector div-assign function.
       * ARGUMENTS:
       *   - vector:
       *       const vec4 &V;
       * RETURNS: (vec4 &) this vector;
       */
      vec4 & operator/=( const Type &N )
      {
        X /= N;
        Y /= N;
        Z /= N;
        W /= N;
        return *this;
      } /* End of 'operator/=' function */

      /* Scalar multiplication function.
       * ARGUMENTS:
       *   - vector:
       *       const vec4 &V;
       * RETURNS: (Type) multiplication result.
       */
      Type operator&( const vec4 &V ) const
      {
        return X * V.X + Y * V.Y + Z * V.Z + W * V.W;
      } /* End of 'operator&' function */

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
        else if (i > 3)
          i = 3;

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
        else if (i > 3)
          i = 3;

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
       * RETURNS: (vec4 &) this vector.
       */
      vec4 & Normalize( VOID )
      {
        *this /= !*this;
        return *this;
      } /* End of 'Normalize' function */

      /* Vector normalizing function.
       * ARGUMENTS: None.
       * RETURNS: (vec4) normalized vector.
       */
      vec4 Normalizing( VOID ) const
      {
        return *this / !*this;
      } /* End of 'Normalizing' function */

      /* Get square length function.
       * ARGUMENTS: None.
       * RETURNS: (Type) square length.
       */
      Type Length2( VOID ) const
      {
        return (X * X + Y * Y + Z * Z + W * W);
      } /* End of 'Length2' function */

     /* Get distace to point function.
       * ARGUMENTS:
       *  - point:
       *      const vec3 &P;
       * RETURNS: (Type) distance.
       */
      Type Distance( const vec4 &P ) const
      {
        Type dX = X - P.X,
             dY = Y - P.Y,
             dZ = Z - P.Z,
             dW = W - P.W;


        return sqrt(dX * dX + dY * dY + dZ * dZ + dW * dW);
      } /* End of 'Distance' function */

      /* Set zero components function.
       * ARGUMENTS: None.
       * RETURNS: (vec4 &) this vector.
       */
      vec4 & Zero( VOID )
      {
        X = 0;
        Y = 0;
        Z = 0;
        W = 0;
        return *this;
      } /* End of 'Zero' function */

      /* Set random range [0; 1] components function.
       * ARGUMENTS: None.
       * RETURNS: (vec4 &) this vector.
       */
      vec4 & Rnd0( VOID )
      {
        X = rand() / RAND_MAX;
        Y = rand() / RAND_MAX;
        Z = rand() / RAND_MAX;
        W = rand() / RAND_MAX;
        return *this;
      } /* End of 'Rnd0' function */

      /* Set random range [-1; 1] components function.
       * ARGUMENTS: None.
       * RETURNS: (vec4 &) this vector.
       */
      vec4 & Rnd1( VOID )
      {
        X = (rand() / RAND_MAX) * 2 - 1;
        Y = (rand() / RAND_MAX) * 2 - 1;
        Z = (rand() / RAND_MAX) * 2 - 1;
        W = (rand() / RAND_MAX) * 2 - 1;
        return *this;
      } /* End of 'Rnd1' function */
    }; /* End of 'vec4' class */


  /* 3D vector representation type */
  template<typename Type>
    class vec3
    {
    template<class Type1>
      friend class matr;

    private:
      Type X, Y, Z;

    public:
      /* Constructor.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      vec3( VOID ): X(0), Y(0), Z(0)
      {
      } /* End of 'vec3' constructor */

      /* Constructor.
       * ARGUMENTS:
       *   - components:
       *       Type x, y, z;
       * RETURNS: None.
       */
      vec3( Type x, Type y, Type z ) : X(x), Y(y), Z(z)
      {
      } /* End of 'vec3' constructor */

      /* Constructor.
       * ARGUMENTS:
       *   - components:
       *       Type x;
       * RETURNS: None.
       */
      vec3( Type x ) : X(x), Y(x), Z(x)
      {
      } /* End of 'vec3' constructor */

      /* Set vector function.
       * ARGUMENTS:
       *   - components:
       *       const Type x, y, z;
       * RETURNS:
       *   (vec3 &) this vector.
       */
      vec3 & Set( const Type x, const Type y, const Type z )
      {
        this->X = x;
        this->Y = y;
        this->Z = z;
        return *this;
      } /* End of 'Set' function */

      /* Copy vector function.
       * ARGUMENTS:
       *   - vector:
       *       vec3 &V;
       * RETURNS: None.
       */
      vec3 & operator=( const vec3 &V )
      {
        this->X = V.X;
        this->Y = V.Y;
        this->Z = V.Z;
        return *this;
      } /* End of 'operator=' constructor */


      /* Get vector length function.
      * ARGUMENTS: None.
      * RETURNS: None.
      */
      Type operator!( VOID ) const
      {
        return sqrt(X * X + Y * Y + Z * Z);
      } /* End of 'operator!' function */

      /* Compare length function.
       * ARGUMENTS:
       *   - vectors for comaring:
       *     (const Type &) V1, V2.
       * RETURNS:
       *   (BOOL) Comparing result.
       */
      BOOL operator>( const vec3 &V ) const
      {
        return this->Length2() > V.Length2();
      } /* End of 'operator>' function */

     /* Compare length function.
      * ARGUMENTS:
      *   - vectors for comaring:
      *     (const Type &) V1, V2.
      * RETURNS:
      *   (BOOL) Comparing result.
      */
      BOOL operator<( const vec3 &V ) const
      {
        return this->Length2() < V.Length2();
      } /* End of 'operator<' function */

      /* Compare length function.
       * ARGUMENTS:
       *   - vectors for comaring:
       *     (const Type &) V1, V2.
       * RETURNS:
       *   (BOOL) Comparing result.
       */
      BOOL operator==( const vec3 &V ) const
      {
        return !this == !V;
      } /* End of 'operator==' function */



      /* Vector sum function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &V;
       * RETURNS: (vec3) result vector;
       */
      vec3 operator+( const vec3 &V ) const
      {
        return vec3(X + V.X, Y + V.Y, Z + V.Z);
      } /* End of 'operator+' function */

      /* Vector sum-assign function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &V;
       * RETURNS: (vec3 &) this vector;
       */
      vec3 & operator+=( const vec3 &V )
      {
        X += V.X;
        Y += V.Y;
        Z += V.Z;
        return *this;
      } /* End of 'operator+=' function */

      /* Vector sub function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &V;
       * RETURNS: (vec3) result vector;
       */
      vec3 operator-( const vec3 &V ) const
      {
        return vec3(X - V.X, Y - V.Y, Z - V.Z);
      } /* End of 'operator-' */

      /* Inverse vector function.
       * ARGUMENTS: None.
       * RETURNS: (vec3 &) this vector;
       */
      vec3 & operator-( VOID )
      {
        X = -X;
        Y = -Y;
        Z = -Z;
        return *this;
      } /* End of 'operator-' */

      /* Vector sub-assign function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &V;
       * RETURNS: (vec3 &) this vector;
       */
      vec3 & operator-=( const vec3 &V )
      {
        X -= V.X;
        Y -= V.Y;
        Z -= V.Z;
        return *this;
      } /* End of 'operator-=' function */

      /* Component multiplication function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &V;
       * RETURNS: (vec3) multiplication result vector.
       */
      vec3 operator*( const vec3 &V ) const
      {
        return vec3(X * V.X, Y * V.Y, Z * V.Z);
      } /* End of 'operator*' function */

      /* Component mul-assign function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &V;
       * RETURNS: (vec3 &) this vector;
       */
      vec3 & operator*=( const vec3 &V )
      {
        X *= V.X;
        Y *= V.Y;
        Z *= V.Z;
        return *this;
      } /* End of 'operator*=' function */

      /* Vector multiply number function.
       * ARGUMENTS:
       *   - number:
       *       const Type &N;
       * RETURNS: (vec3) multiplication result.
       */
      vec3 operator*( const Type &N ) const
      {
        return vec3(X * N, Y * N, Z * N);
      } /* End of 'operator*' function */

      /* Vector mul-assign function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &V;
       * RETURNS: (vec3 &) this vector;
       */
      vec3 & operator*=( const Type &N )
      {
        X *= N;
        Y *= N;
        Z *= N;
        return *this;
      } /* End of 'operator*=' function */

      /* Vector divide number function.
       * ARGUMENTS:
       *   - number:
       *       const Type &N;
       * RETURNS: (vec3) multiplication result.
       */
      vec3 operator/( const Type &N ) const
      {
        return vec3(X / N, Y / N, Z / N);
      } /* End of 'operator/' function */

      /* Vector div-assign function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &V;
       * RETURNS: (vec3 &) this vector;
       */
      vec3 & operator/=( const Type &N )
      {
        X /= N;
        Y /= N;
        Z /= N;
        return *this;
      } /* End of 'operator/=' function */

      /* Scalar multiplication function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &V;
       * RETURNS: (Type) multiplication result.
       */
      Type operator&( const vec3 &V ) const
      {
        return X * V.X + Y * V.Y + Z * V.Z;
      } /* End of 'operator&' function */

      /* Vector multiplication function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &V;
       * RETURNS: (vec3) multiplication result.
       */
      vec3 operator%( const vec3 &V ) const
      {
        return vec3(Y * V.Z - Z * V.Y,
                    Z * V.X - X * V.Z,
                    X * V.Y - Y * V.X);
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
        else if (i > 2)
          i = 2;

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
        else if (i > 2)
          i = 2;

        return *(&X + i);
      } /* End of 'operator[]' function */

      /* Get pointer to first component function;
       * ARGUMENTS: None.
       * RETURNS: (Type &) component link;
       */
      operator Type *( VOID )
      {
        return &X;
      } /* End of 'operator Type *' function */

      /* Self normalizing function.
       * ARGUMENTS: None.
       * RETURNS: (vec3 &) this vector.
       */
      vec3 & Normalize( VOID )
      {
        *this /= !*this;
        return *this;
      } /* End of 'Normalize' function */

      /* Vector normalizing function.
       * ARGUMENTS: None.
       * RETURNS: (vec3) normalized vector.
       */
      vec3 Normalizing( VOID ) const
      {
        Type Len = !*this;
        if (Len == 0)
          return vec3(0);
        return *this / Len;
      } /* End of 'Normalizing' function */

      /* Get square length function.
       * ARGUMENTS: None.
       * RETURNS: (Type) square length.
       */
      Type Length2( VOID ) const
      {
        return (X * X + Y * Y + Z * Z);
      } /* End of 'Length2' function */

      /* Get distace to point function.
       * ARGUMENTS:
       *  - point:
       *      const vec3 &P;
       * RETURNS: (Type) distance.
       */
      Type Distance( const vec3 &P ) const
      {
        Type dX = X - P.X,
             dY = Y - P.Y,
             dZ = Z - P.Z;

        return sqrt(dX * dX + dY * dY + dZ * dZ);
      } /* End of 'Distance' function */

      /* Set zero components function.
       * ARGUMENTS: None.
       * RETURNS: (vec3 &) this vector.
       */
      vec3 & Zero( VOID )
      {
        X = 0;
        Y = 0;
        Z = 0;
        return *this;
      } /* End of 'Zero' function */

      /* Set random range [0; 1] components function.
       * ARGUMENTS: None.
       * RETURNS: (vec3 &) this vector.
       */
      vec3 & Rnd0( VOID )
      {
        X = rand() / RAND_MAX;
        Y = rand() / RAND_MAX;
        Z = rand() / RAND_MAX;
        return *this;
      } /* End of 'Rnd0' function */

      /* Set random range [-1; 1] components function.
       * ARGUMENTS: None.
       * RETURNS: (vec3 &) this vector.
       */
      vec3 & Rnd1( VOID )
      {
        X = ((Type)rand() / RAND_MAX) * 2 - 1;
        Y = ((Type)rand() / RAND_MAX) * 2 - 1;
        Z = ((Type)rand() / RAND_MAX) * 2 - 1;
        return *this;
      } /* End of 'Rnd1' function */
    }; /* End of 'vec3' class */

  /* 2D vector representation type */
  template<typename Type>
    class vec2
    {
    template<class Type1>
      friend class matr;

    private:
      Type X, Y;

    public:
      /* Constructor.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      vec2( VOID ): X(0), Y(0)
      {
      } /* End of 'vec2' constructor */

      /* Constructor.
       * ARGUMENTS:
       *   - components:
       *       Type x, y;
       * RETURNS: None.
       */
      vec2( Type x, Type y ) : X(x), Y(y)
      {
      } /* End of 'vec2' constructor */

      /* Constructor.
       * ARGUMENTS:
       *   - components:
       *       Type x;
       * RETURNS: None.
       */
      vec2( Type x ) : X(x), Y(x)
      {
      } /* End of 'vec2' constructor */

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

      /* Get vector length function.
      * ARGUMENTS: None.
      * RETURNS: None.
      */
      Type operator!( VOID ) const
      {
        return sqrt(X * X + Y * Y);
      } /* End of 'operator!' function */

      /* Compare length function.
      * ARGUMENTS:
      *   - vectors for comaring:
      *     (const Type &) V1, V2.
      * RETURNS:
      *   (BOOL) Comparing result.
      */
      BOOL operator>( const vec2 &V ) const
      {
        return this->Length2() > V.Length2();
      } /* End of 'operator>' function */

     /* Compare length function.
      * ARGUMENTS:
      *   - vectors for comaring:
      *     (const Type &) V1, V2.
      * RETURNS:
      *   (BOOL) Comparing result.
      */
      BOOL operator<( const vec2 &V ) const
      {
        return this->Length2() < V.Length2();
      } /* End of 'operator<' function */

      /* Compare length function.
       * ARGUMENTS:
       *   - vectors for comaring:
       *     (const Type &) V1, V2.
       * RETURNS:
       *   (BOOL) Comparing result.
       */
      BOOL operator==( const vec2 &V ) const
      {
        return !this == !V;
      } /* End of 'operator==' function */


      /* Vector sum function.
       * ARGUMENTS:
       *   - vector:
       *       const vec2 &V;
       * RETURNS: (vec3) result vector;
       */
      vec2 operator+( const vec2 &V ) const
      {
        return vec2(X + V.X, Y + V.Y);
      } /* End of 'operator+' function */

      /* Vector sum-assign function.
       * ARGUMENTS:
       *   - vector:
       *       const vec2 &V;
       * RETURNS: (vec3 &) this vector;
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
       * RETURNS: (vec3) result vector;
       */
      vec2 operator-( const vec2 &V ) const
      {
        return vec2(X - V.X, Y - V.Y);
      } /* End of 'operator-' */

      /* Inverse vector function.
       * ARGUMENTS: None.
       * RETURNS: (vec2 &) this vector;
       */
      vec2 & operator-( VOID )
      {
        X = -X;
        Y = -Y;
        return *this;
      } /* End of 'operator-' */

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

#endif

/* END OF 'math_vec.h' FILE */


