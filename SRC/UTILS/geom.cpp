/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : geom.cpp
 * PURPOSE     : geom utils file.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 10.09.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */


/* Includes */
#include "../def.h"
#include "../ANIM/anim.h"
#include "geom.h"

/* Animation project namespace */
namespace digl
{
  /* Reset matrixes for childs function.
   * ARGUMENTS:
   *   - parent matr:
   *     const matr &Matr;
   * RETURNS: None.
   */
  VOID geom::ResetChilds( const matr &Matr )
  {
    for (auto it = Childs.begin(); it != Childs.end(); ++it)
    {
      (*it)->ParentMatr = Matr;
      (*it)->ResetChilds((*it)->SelfMatr * Matr);
    }
  } /* End of 'geom::ResetChilds' function */

  /* Get child function.
   * ARGUMENTS:
   *   - index:
   *       const INT i;
   * RETURNS:
   *   (geom &) Child;
   */
  geom & geom::operator[]( const INT i ) const
  {
    return *Childs[i];
  } /* End of 'geom::operator[]' function */

  /* Add primitives function. 
   * ARGUMENTS:
   *   - primitives for add:
   *       primitives::primitives Pr;
   * RETURNS: None.
   */
  VOID geom::AddPrims( primitives::primitives *Pr )
  {
    Prims.push_back(Pr);
  } /* End of 'geom::AddPrims' function */

  /* Add emitter function. 
     * ARGUMENTS:
     *   - emitter for add:
     *       emitter *Em;
     * RETURNS: None.
     */
  VOID geom::AddEmitter( emitter *Em )
  {
    Emitters.push_back(Em);
  } /* End of 'geom::AddEmitter' function */

  /* Add child function. 
   * ARGUMENTS:
   *   - child for add:
   *       geom *Ch;
   * RETURNS: None.
   */
  VOID geom::AddChild( geom *Ch )
  {
    Ch->ParentMatr = SelfMatr * ParentMatr;
    Childs.push_back(Ch);
  } /* End of 'geom::AddPrims' function */

  /* Set matrix function. 
   * ARGUMENTS:
   *   - new matrix:
   *       const matr Matr;
   * RETURNS: None.
   */
  VOID geom::SetMatrix( const matr &Matr )
  {
    SelfMatr = Matr;
    ResetChilds(SelfMatr * ParentMatr);
  } /* End of 'geom::SetMatrix' function */

  /* Apply matrix function. 
   * ARGUMENTS:
   *   - matrix:
   *       const matr Matr;
   * RETURNS: None.
   */
  VOID geom::ApplyMatrix( const matr &Matr )
  {
    SelfMatr = SelfMatr * Matr;
    ResetChilds(SelfMatr * ParentMatr);
  } /* End of 'geom::ApplyMatrix' function */

  /* Geometry response function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID geom::Response( VOID )
  {
    anim *AC = anim::GetPtr();
    /* Response emitters */
    for (auto el : Emitters)
      el->Response(SelfMatr * ParentMatr);
    /* Response childs */
    for (auto el : Childs)
      el->Response();
  } /* End of 'geom::Draw' function */

  /* Geom draw function.
   * ARGUMENTS: None.
   * RETUNRS: None.
   */
  VOID geom::Draw( VOID )
  {
    anim *AC = anim::GetPtr();
    /* Draw prims */
    for (auto el : Prims)
      AC->DrawPrims(*el, el->Transform * SelfMatr * ParentMatr);
    /* Draw emitters */
    for (auto el : Emitters)
      el->Draw();
    /* Draw childs */
    for (auto el : Childs)
      el->Draw();
  } /* End of 'geom::Draw' function */
} /* end of 'digl' namespace */

/* END OF 'geom.cpp' FILE */



