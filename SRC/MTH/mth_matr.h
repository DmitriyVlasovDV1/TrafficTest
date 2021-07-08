/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : mth_matr.h
 * PURPOSE     : Matrix header file.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 24.07.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */

#ifndef _math_matr_h_
#define _math_matr_h_

#include "mthdef.h"

/* Space math namespace */
namespace mth
{
  /* 4D matrix representation type */
  template<class Type>
    class matr
    {
    private:
      Type A[4][4];
      mutable Type InvA[4][4];
      mutable bool IsInverseEvaluated;

      /* Get matrix3x3 determinant function.
       * ARGUMENTS:
       *   - matrix components:
       *       (const Type &) A11, A12, ... A33;
       * RETURNS:
       *  (Type) determinant.
       */
      static Type Determ3x3( const Type &A11, const Type &A12, const Type &A13,
                             const Type &A21, const Type &A22, const Type &A23,
                             const Type &A31, const Type &A32, const Type &A33 )
      {
        return A11 * A22 * A33 - A11 * A23 * A32 - A12 * A21 * A33 +
               A12 * A23 * A31 + A13 * A21 * A32 - A13 * A22 * A31;
      } /* End of 'Determ3x3' function */


      /* Calculate inverse matrix function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID EvaluateInverseMatrix( VOID ) const
      {
        if (IsInverseEvaluated)
          return;
        IsInverseEvaluated = true;

        double det = !*this;

        InvA[0][0] =
          Determ3x3(A[1][1], A[1][2], A[1][3],
                    A[2][1], A[2][2], A[2][3],
                    A[3][1], A[3][2], A[3][3]) / det;
        InvA[1][0] =
         -Determ3x3(A[1][0], A[1][2], A[1][3],
                    A[2][0], A[2][2], A[2][3],
                    A[3][0], A[3][2], A[3][3]) / det;
        InvA[2][0] =
          Determ3x3(A[1][0], A[1][1], A[1][3],
                    A[2][0], A[2][1], A[2][3],
                    A[3][0], A[3][1], A[3][3]) / det;
        InvA[3][0] =
         -Determ3x3(A[1][0], A[1][1], A[1][2],
                    A[2][0], A[2][1], A[2][2],
                    A[3][0], A[3][1], A[3][2]) / det;

        InvA[0][1] =
         -Determ3x3(A[0][1], A[0][2], A[0][3],
                    A[2][1], A[2][2], A[2][3],
                    A[3][1], A[3][2], A[3][3]) / det;
        InvA[1][1] =
          Determ3x3(A[0][0], A[0][2], A[0][3],
                    A[2][0], A[2][2], A[2][3],
                    A[3][0], A[3][2], A[3][3]) / det;
        InvA[2][1] =
         -Determ3x3(A[0][0], A[0][1], A[0][3],
                    A[2][0], A[2][1], A[2][3],
                    A[3][0], A[3][1], A[3][3]) / det;
        InvA[3][1] =
          Determ3x3(A[0][0], A[0][1], A[0][2],
                    A[2][0], A[2][1], A[2][2],
                    A[3][0], A[3][1], A[3][2]) / det;

        InvA[0][2] =
          Determ3x3(A[0][1], A[0][2], A[0][3],
                    A[1][1], A[1][2], A[1][3],
                    A[3][1], A[3][2], A[3][3]) / det;
        InvA[1][2] =
         -Determ3x3(A[0][0], A[0][2], A[0][3],
                    A[1][0], A[1][2], A[1][3],
                    A[3][0], A[3][2], A[3][3]) / det;
        InvA[2][2] =
          Determ3x3(A[0][0], A[0][1], A[0][3],
                    A[1][0], A[1][1], A[1][3],
                    A[3][0], A[3][1], A[3][3]) / det;
        InvA[3][2] =
         -Determ3x3(A[0][0], A[0][1], A[0][2],
                    A[1][0], A[1][1], A[1][2],
                    A[3][0], A[3][1], A[3][2]) / det;

        InvA[0][3] =
         -Determ3x3(A[0][1], A[0][2], A[0][3],
                    A[1][1], A[1][2], A[1][3],
                    A[2][1], A[2][2], A[2][3]) / det;
        InvA[1][3] =
          Determ3x3(A[0][0], A[0][2], A[0][3],
                    A[1][0], A[1][2], A[1][3],
                    A[2][0], A[2][2], A[2][3]) / det;
        InvA[2][3] =
         -Determ3x3(A[0][0], A[0][1], A[0][3],
                    A[1][0], A[1][1], A[1][3],
                    A[2][0], A[2][1], A[2][3]) / det;
        InvA[3][3] =
          Determ3x3(A[0][0], A[0][1], A[0][2],
                    A[1][0], A[1][1], A[1][2],
                    A[2][0], A[2][1], A[2][2]) / det;
      } /* End of 'EvaluateInverseMatrix' function */

    public:
      /* Constructor.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      matr( VOID ) : IsInverseEvaluated(false)
      {
      } /* End of 'matr' constructor */

      /* Constructor.
       * ARGUMENTS:
       *   - matrix components:
       *       (const Type &) A11, A12, ... A33;
       * RETURNS: None.
       */
      matr( const Type &A11, const Type &A12, const Type &A13, const Type &A14,
            const Type &A21, const Type &A22, const Type &A23, const Type &A24,
            const Type &A31, const Type &A32, const Type &A33, const Type &A34,
            const Type &A41, const Type &A42, const Type &A43, const Type &A44 )
      {
        IsInverseEvaluated = false;
        A[0][0] = A11, A[0][1] = A12, A[0][2] = A13, A[0][3] = A14;
        A[1][0] = A21, A[1][1] = A22, A[1][2] = A23, A[1][3] = A24;
        A[2][0] = A31, A[2][1] = A32, A[2][2] = A33, A[2][3] = A34;
        A[3][0] = A41, A[3][1] = A42, A[3][2] = A43, A[3][3] = A44;
      } /* End of 'matr' constructor */

      /* Constructor.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      matr( Type M[4][4] ) : IsInverseEvaluated(false)
      {
        A[0][0] = M[0][0], A[0][1] = M[0][1], A[0][2] = M[0][2], A[0][3] = M[0][3];
        A[1][0] = M[1][0], A[1][1] = M[1][1], A[1][2] = M[1][2], A[1][3] = M[1][3];
        A[2][0] = M[2][0], A[2][1] = M[2][1], A[2][2] = M[2][2], A[2][3] = M[2][3];
        A[3][0] = M[3][0], A[3][1] = M[3][1], A[3][2] = M[3][2], A[3][3] = M[3][3];
      } /* End of 'matr' constructor */

      /* Set matrix function.
       * ARGUMENTS:
       *   - matrix components:
       *       (const Type &) A11, A12, ... A33;
       * RETURNS: None.
       */
      VOID Set( const Type &A11, const Type &A12, const Type &A13, const Type &A14,
                const Type &A21, const Type &A22, const Type &A23, const Type &A24,
                const Type &A31, const Type &A32, const Type &A33, const Type &A34,
                const Type &A41, const Type &A42, const Type &A43, const Type &A44 )
      {
        A[0][0] = A11, A[0][1] = A12, A[0][2] = A13, A[0][3] = A14;
        A[1][0] = A21, A[1][1] = A22, A[1][2] = A23, A[1][3] = A24;
        A[2][0] = A31, A[2][1] = A32, A[2][2] = A33, A[2][3] = A34;
        A[3][0] = A41, A[3][1] = A42, A[3][2] = A43, A[3][3] = A44;
      } /* End of 'Set' function */

      /* Transform point function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<Type> &N;
       * RETURNS:
       *   (vec3<Type>) result vector;
       */
      vec3<Type> TransformPoint( const vec3<Type> &N ) const
      {
        return vec3<Type>(N.X * A[0][0] + N.Y * A[1][0] + N.Z * A[2][0] + A[3][0],
                          N.X * A[0][1] + N.Y * A[1][1] + N.Z * A[2][1] + A[3][1],
                          N.X * A[0][2] + N.Y * A[1][2] + N.Z * A[2][2] + A[3][2]);
      } /* End of 'TransformPoint' function */

      /* Transform vector function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<Type> &N;
       * RETURNS:
       *   (vec3<Type>) result vector;
       */
      vec3<Type> TransformVector( const vec3<Type> &N ) const
      {
        return vec3<Type>(N.X * A[0][0] + N.Y * A[1][0] + N.Z * A[2][0],
                          N.X * A[0][1] + N.Y * A[1][1] + N.Z * A[2][1],
                          N.X * A[0][2] + N.Y * A[1][2] + N.Z * A[2][2]);
      } /* End of 'TransformVector' function */

      /* Transform normal function.
       * ARGUMENTS:
       *   - normal:
       *       const vec3<Type> &N;
       * RETURNS:
       *   (vec3<Type>) result normal;
       */
      vec3<Type> TransformNormal( const vec3<Type> &N ) const
      {
        matr M = Transpose(Inverse());

        return vec3<Type>(N.X * M[0][0] + N.Y * M[1][0] + N.Z * M[2][0],
                          N.X * M[0][1] + N.Y * M[1][1] + N.Z * M[2][1],
                          N.X * M[0][2] + N.Y * M[1][2] + N.Z * M[2][2]);
      } /* End of 'TransformNormal' function */

      /* Transform 4x4 function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<Type> &N;
       * RETURNS:
       *   (vec3<Type>) result vector;
       */
      vec3<Type> Transform4x4( const vec3<Type> &N ) const
      {
        return vec3<Type>( N.X * A[0][0] + N.Y * A[1][0] + N.Z * A[2][0] + A[3][0],
                           N.X * A[0][1] + N.Y * A[1][1] + N.Z * A[2][1] + A[3][1],
                           N.X * A[0][2] + N.Y * A[1][2] + N.Z * A[2][2] + A[3][2]) /
                          (N.X * A[0][3] + N.Y * A[1][3] + N.Z * A[2][3] + A[3][3]);
      } /* End of 'Transform4x4' function */

      /* Get matrix determinant function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) determinant.
       */
      Type operator!( VOID ) const
      {
        return
          A[0][0] * Determ3x3(A[1][1], A[1][2], A[1][3],
                              A[2][1], A[2][2], A[2][3],
                              A[3][1], A[3][2], A[3][3]) -
          A[0][1] * Determ3x3(A[1][0], A[1][2], A[1][3],
                              A[2][0], A[2][2], A[2][3],
                              A[3][0], A[3][2], A[3][3]) +
          A[0][2] * Determ3x3(A[1][0], A[1][1], A[1][3],
                              A[2][0], A[2][1], A[2][3],
                              A[3][0], A[3][1], A[3][3]) -
          A[0][3] * Determ3x3(A[1][0], A[1][1], A[1][2],
                              A[2][0], A[2][1], A[2][2],
                              A[3][0], A[3][1], A[3][2]);
      } /* End of 'operator!' function */

      /* Multiplicate matrices function.
       * ARGUMENTS:
       *   - matrix:
       *       (const matr&) M;
       * RETURNS:
       *   (matr) result matrix.
       */
      matr operator*( const matr &M ) const
      {
        return
          matr(
            A[0][0] * M.A[0][0] + A[0][1] * M.A[1][0] + A[0][2] * M.A[2][0] + A[0][3] * M.A[3][0],
            A[0][0] * M.A[0][1] + A[0][1] * M.A[1][1] + A[0][2] * M.A[2][1] + A[0][3] * M.A[3][1],
            A[0][0] * M.A[0][2] + A[0][1] * M.A[1][2] + A[0][2] * M.A[2][2] + A[0][3] * M.A[3][2],
            A[0][0] * M.A[0][3] + A[0][1] * M.A[1][3] + A[0][2] * M.A[2][3] + A[0][3] * M.A[3][3],

            A[1][0] * M.A[0][0] + A[1][1] * M.A[1][0] + A[1][2] * M.A[2][0] + A[1][3] * M.A[3][0],
            A[1][0] * M.A[0][1] + A[1][1] * M.A[1][1] + A[1][2] * M.A[2][1] + A[1][3] * M.A[3][1],
            A[1][0] * M.A[0][2] + A[1][1] * M.A[1][2] + A[1][2] * M.A[2][2] + A[1][3] * M.A[3][2],
            A[1][0] * M.A[0][3] + A[1][1] * M.A[1][3] + A[1][2] * M.A[2][3] + A[1][3] * M.A[3][3],

            A[2][0] * M.A[0][0] + A[2][1] * M.A[1][0] + A[2][2] * M.A[2][0] + A[2][3] * M.A[3][0],
            A[2][0] * M.A[0][1] + A[2][1] * M.A[1][1] + A[2][2] * M.A[2][1] + A[2][3] * M.A[3][1],
            A[2][0] * M.A[0][2] + A[2][1] * M.A[1][2] + A[2][2] * M.A[2][2] + A[2][3] * M.A[3][2],
            A[2][0] * M.A[0][3] + A[2][1] * M.A[1][3] + A[2][2] * M.A[2][3] + A[2][3] * M.A[3][3],

            A[3][0] * M.A[0][0] + A[3][1] * M.A[1][0] + A[3][2] * M.A[2][0] + A[3][3] * M.A[3][0],
            A[3][0] * M.A[0][1] + A[3][1] * M.A[1][1] + A[3][2] * M.A[2][1] + A[3][3] * M.A[3][1],
            A[3][0] * M.A[0][2] + A[3][1] * M.A[1][2] + A[3][2] * M.A[2][2] + A[3][3] * M.A[3][2],
            A[3][0] * M.A[0][3] + A[3][1] * M.A[1][3] + A[3][2] * M.A[2][3] + A[3][3] * M.A[3][3]
          );
      } /* End of 'operator*' function */

      /* Get inverse matrix function.
       * ARGUMENTS: None.
       * RETUNRS:
       *   (matr) result matrix.
       */
      matr Inverse( VOID )
      {
        EvaluateInverseMatrix();

        return matr(InvA);
      } /* End of 'Inverse' function */

      /* Transpose matrix function.
       * ARGUMENTS: None.
       * RETUNRS:
       *   (matr &) this matrix.
       */
      matr & Transpose( VOID )
      {
        Set(A[0][0], A[1][0], A[2][0], A[3][0],
            A[0][1], A[1][1], A[2][1], A[3][1],
            A[0][2], A[1][2], A[2][2], A[3][2],
            A[0][3], A[1][3], A[2][3], A[3][3]);
        return *this;
      } /* End of 'Transpose' function */

      /* Transpose matrix function.
       * ARGUMENTS: None.
       * RETUNRS:
       *   (matr) result matrix.
       */
      static matr Transpose( const matr &M )
      {
        return matr(M[0][0], M[1][0], M[2][0], M[3][0],
                    M[0][1], M[1][1], M[2][1], M[3][1],
                    M[0][2], M[1][2], M[2][2], M[3][2],
                    M[0][3], M[1][3], M[2][3], M[3][3]);
      } /* End of 'Transpose' function */


      /* Get identity matrix function.
       * ARGUMENTS: None.
       * RETURNS:
           (matr) result matrix.
       */
      static matr Identity( VOID )
      {
        return matr(1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1);
      } /* End of 'Identity' function */

      /* Get roatation matrix function.
       * ARGUMENTS:
       *   - roatation axe:
       *       vec3 &V;
       *   - rotation angle in degrees:
       *       Type &Ad;
       * RETURNS:
       *   (matr &) this matrix;
       */
      static matr Rotate( const vec3<Type> &V, const Type &Ad )
      {
        Type Ar = D2R(Ad),
             co = cos(Ar),
             si = sin(Ar);
        return matr(co + V.X * V.X * (1 - co),
                    V.X * V.Y * (1 - co) + V.Z * si,
                    V.X * V.Z * (1 - co) - V.Y * si,
                    0,

                    V.Y * V.X * (1 - co) - V.Z * si,
                    co + V.Y * V.Y * (1 - co),
                    V.Y * V.Z * (1 - co) + V.X * si,
                    0,

                    V.Z * V.X * (1- co) + V.Y * si,
                    V.Z * V.Y * (1 - co) - V.X  * si,
                    co + V.Z * V.Z * (1 - co),
                    0,

                    0, 0, 0, 1);
      } /* End of 'Rotate' function */

      /* Get roatation Z matrix function.
       * ARGUMENTS:
       *   - rotation angle in degrees:
       *       Type &Ad;
       * RETURNS:
       *   (matr) reslt matrix;
       */
      static matr RotateZ( const Type &Ad )
      {
        Type Ar = D2R(Ad),
             co = cos(Ar),
             si = sin(Ar);
        return matr(co, si, 0, 0,
                    -si, co, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1);
      } /* End of 'RotateZ' function */

      /* Get roatation X matrix function.
       * ARGUMENTS:
       *   - rotation angle in degrees:
       *       Type &Ad;
       * RETURNS:
       *   (matr) result matrix;
       */
      static matr RotateX( const Type &Ad )
      {
        Type Ar = D2R(Ad),
             co = cos(Ar),
             si = sin(Ar);
        return matr(1, 0, 0, 0,
                    0, co, si, 0,
                    0, -si, co, 0,
                    0, 0, 0, 1);
      } /* End of 'RotateX' function */

      /* Get roatation Y matrix function.
       * ARGUMENTS:
       *   - rotation angle in degrees:
       *       Type &Ad;
       * RETURNS:
       *   (matr) result matrix;
       */
      static matr RotateY( const Type &Ad )
      {
        Type Ar = D2R(Ad),
             co = cos(Ar),
             si = sin(Ar);
        return matr(co, 0, -si, 0,
                    0, 1, 0, 0,
                    si, 0, co, 0,
                    0, 0, 0, 1);
      } /* End of 'RotateY' function */

      /* Get scale matrix function.
       * ARGUMENTS:
       *   - scale vector:
       *       Type &V;
       * RETURNS:
       *   (matr) result matrix;
       */
      static matr Scale( const vec3<Type> &V )
      {
        return matr(V.X, 0, 0, 0,
                    0, V.Y, 0, 0,
                    0, 0, V.Z, 0,
                    0, 0, 0, 1);
      } /* End of 'Scale' function */

      /* Get translation matrix function.
       * ARGUMENTS:
       *   - translation vector:
       *       Type &V;
       * RETURNS:
       *   (matr) result matrix;
       */
      static matr Translate( const vec3<Type> &V )
      {
        return matr(1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    V.X, V.Y, V.Z, 1);
      } /* End of 'Translate' function */

      /* Change basis matrix function.
       * ARGUMENTS:
       *   - basis vectors:
       *       Type &Vx, &Vy, &Vz;
       * RETURNS:
       *   (matr) result matrix;
       */
      static matr Basis( const vec3<Type> &Vx,
                         const vec3<Type> &Vy,
                         const vec3<Type> &Vz )
      {
        return matr(Vx[0], Vx[1], Vx[2], 0,
                    Vy[0], Vy[1], Vy[2], 0,
                    Vz[0], Vz[1], Vz[2], 0,
                    0,    0,    0,    1);
      } /* End of 'Basis' function */

      /* Get ortho matrix function.
       * ARGUMENTS:
       *   - 3D ortho bound coordinates:
       *       Type Left, Right, Bottom, Top, Near, Far;
       * RETURNS:
       *   (matr) result matrix;
       */
      static matr Ortho( Type L, Type R, Type B, Type T, Type N, Type F )
      {
        return matr(
          2 / (R - L)       , 0                 , 0                 , 0,
          0                 , 2 / (T - B)       , 0                 , 0,
          0                 , 0                 , -2 / (F - N)      , 0,
          -(R + L) / (R - L), -(T + B) / (T - B), -(F + N) / (F - N), 1);
      } /* End of 'Ortho' function */

      /* Get frustum matrix function.
       * ARGUMENTS:
       *   - 3D frustum bound coordinates:
       *       Type Left, Right, Bottom, Top, Near, Far;
       * RETURNS:
       *   (matr) result matrix;
       */
      static matr Frustum( Type L, Type R, Type B, Type T, Type N, Type F )
      {
        return matr(
          2 * N / (R - L)  , 0                , 0                   , 0 ,
          0                , 2 * N / (T - B)  , 0                   , 0 ,
          (R + L) / (R - L), (T + B) / (T - B), -(F + N) / (F - N)  , -1,
          0                , 0                , -2 * N * F / (F - N), 0 );

      } /* End of 'Frustum' function */

      /* Obtain view matrix (by location, look-at and up vectors) function.
       * ARGUMENTS:
       *   - view camera location:
       *       const vec<Type> &Loc;
       *   - look-at point:
       *       const vec<Type> &LookAt;
       *   - approximate up direction:
       *       const vec<Type> &Up1;
       * RETURNS:
       *   (matr) view transformatrion matrix.
       */
      static matr ViewLookAt( const vec3<Type> &Loc, const vec3<Type> &LookAt, const vec3<Type> &Up1 )
      {
        vec3<Type>
          Dir = (LookAt - Loc).Normalizing(),
          Right = (Dir % Up1).Normalizing(),
          Up = Right % Dir;

        return matr(Right.X, Up.X, -Dir.X, 0,
                    Right.Y, Up.Y, -Dir.Y, 0,
                    Right.Z, Up.Z, -Dir.Z, 0,
                    -(Right & Loc), -(Up & Loc), Dir & Loc, 1);
      } /* End of 'ViewLookAt' function */

      /* Cast matrix to forst element pointer function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type *) pointer to first row first column element.
       */
      operator Type *( VOID )
      {
        return A[0];
      } /* End of 'operator Type *' function */
    };
} /* end of 'mth' namespace */

#endif

/* END OF 'math_matr.h' FILE */
