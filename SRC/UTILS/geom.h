/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : geom.h
 * PURPOSE     : geom utils headerfile.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 10.09.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */

#ifndef __GEOM_H_
#define __GEOM_H_

/* Includes */
#include "../def.h"
#include "../ANIM/RENDER/prim.h"
#include "particles.h"
#include <vector>

/* Animation project namespace */
namespace digl
{
  /* Geometry representation class */
  class geom
  {
  private:
    matr ParentMatr;
    matr SelfMatr;
    std::vector<geom *> Childs;
    std::vector<primitives::primitives *> Prims;
    std::vector<emitter *> Emitters;

    /* Reset matrixes for childs function.
     * ARGUMENTS:
     *   - parent matr:
     *     const matr &Matr;
     * RETURNS: None.
     */
    VOID ResetChilds( const matr &Matr );

  public:
    /* Geometry constructor function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    geom( VOID ) : ParentMatr(matr::Identity()),
      SelfMatr(matr::Identity())
    {
    } /* End of 'geom' functon */

    /* Destructor */
    ~geom( VOID )
    {
    } /* End of '~geom' functon */

    /* Get child function.
     * ARGUMENTS:
     *   - index:
     *       const INT i;
     * RETURNS:
     *   (geom &) Child;
     */
    geom & operator[]( const INT i ) const;

    /* Add primitives function. 
     * ARGUMENTS:
     *   - primitives for add:
     *       primitives::primitives Pr;
     * RETURNS: None.
     */
    VOID AddPrims( primitives::primitives *Pr );

    /* Add emitter function. 
     * ARGUMENTS:
     *   - emitter for add:
     *       emitter *Em;
     * RETURNS: None.
     */
    VOID AddEmitter( emitter *Em );

    /* Add child function. 
     * ARGUMENTS:
     *   - child for add:
     *       geom *Ch;
     * RETURNS: None.
     */
    VOID AddChild( geom *Ch );

    /* Set matrix function. 
     * ARGUMENTS:
     *   - new matrix:
     *       const matr Matr;
     * RETURNS: None.
     */
    VOID SetMatrix( const matr &Matr );

    /* Apply matrix function. 
     * ARGUMENTS:
     *   - matrix:
     *       const matr Matr;
     * RETURNS: None.
     */
    VOID ApplyMatrix( const matr &Matr );

    /* Geometry response function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Response( VOID );

    /* Geom draw function.
     * ARGUMENTS: None.
     * RETUNRS: None.
     */
    VOID Draw( VOID );
  };
} /* end of 'digl' namespace */

#endif /* __GEOM_H_ */

/* END OF 'geom.h' FILE */



