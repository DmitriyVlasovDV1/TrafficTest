/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TIMER.H
 * PURPOSE     : Animation header file.
 * PROGRAMMER  : Vlasiv Dmitriy.
 * LAST UPDATE : 24.07.2020.
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef _ANIM_H_
#define _ANIM_H_

#include "../def.h"
#include "input.h"
#include "timer.h"
#include "../win/win.h"
#include "../stock.h"
#include "RENDER/render.h"

namespace digl
{
  class anim;

  /* Unit representation type */
  namespace units
  {
    class unit
    {
    public:
      /* Unit constructor.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      unit( VOID )
      {
      } /* End of 'unit' function */

      /* Response function.
       * ARGUMENTS:
       *   - animation:
       *       anim *Ani;
       * RETURNS: None.
       */
      virtual VOID Response( anim *Ani )
      {
      } /* End of 'Response' function */

      /* Render function.
       * ARGUMENTS:
       *   - animation:
       *       anim *Ani;
       * RETURNS: None.
       */
      virtual VOID Render( anim *Ani )
      {
      } /* End of 'Render' function */

    }; /* End of 'unit' class */

    /* Scene representation type */
    class scene : public unit
    {
    public:
      stock<units::unit *> Units;


      /* Scene constructor
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      scene( VOID ) : unit()
      {

      } /* End of 'scene' function */

      /* Add element to scene function.
       * ARGUMENTS:
       *   - unit for add:
       *       units::unit *Uni;
       * RETUNRNS:
       *   (scene &) this scene.
       */
      scene & operator<<( units::unit *Uni );

      /* Add element to scene function.
       * ARGUMENTS:
       *   - name unit for add:
       *       const std::string &Name;
       * RETUNRNS:
       *   (scene &) this scene.
       */
      scene & operator<<( const std::string &Name );

      /* Response function.
       * ARGUMENTS:
       *   - animation:
       *       anim *Ani;
       * RETURNS: None.
       */
      VOID Response( anim *Ani ) override
      {
        this->Units.Walk([Ani]( units::unit *Uni ){ Uni->Response(Ani); });
      } /* End of 'Response' function */

      /* Render function.
       * ARGUMENTS:
       *   - animation:
       *       anim *Ani;
       * RETURNS: None.
       */
      VOID Render( anim *Ani ) override
      {
        this->Units.Walk([Ani]( units::unit *Uni ){ Uni->Render(Ani); });
      } /* End of 'Render' function */


    }; /* End of 'scene' class */
  } /* end of 'units' namespace */

  /* Animation*/
  class anim : public win, public input, public render, public timer
  {
  private:
    units::unit *Scene;

    /* Anim constructor function */
    anim( VOID ) : win(), render(win::hWnd, win::W, win::H), timer(), input(win::MouseWheel, win::hWnd), Scene(nullptr)
    {
    } /* End of 'anim' function */

    /* Destructor */
    ~anim( VOID )
    {
    } /* End of '~anim' function */

    /* Animation instance */
    static anim Instance;

  public:
    std::map<std::string, units::unit * (*)( VOID )> UnitNames;

    template<class UnitType>
      class unit_register
      {
      public:

        /* Unit creation function.
         * ARGUMENTS: None.
         * RETURNS:
         *   (unit *) New unit.
         */
        static units::unit * Create( VOID )
        {
          return new UnitType(&Instance);
        } /* End of 'Create' function */

        /* Unit register constructor.
         * ARGUMENTS:
         *   - name:
         *       const std::string &Name;
         * RETURNS: None.
         */
        unit_register( const std::string &Name )
        {
          Instance.UnitNames[Name] = this->Create;
        } /* End of 'unit_register' function */
      }; /* End of 'unit_register' class */

    /* Get anim instance function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (anim &) Animation instance.
     */
    static anim & Get( VOID );

    /* Get anim instance function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (anim &) Animation instance.
     */
    static anim * GetPtr( VOID );

    /* Set scene function.
     * ARGUMENTS:
     *   - new scene:
     *       unit *NewScene
     * RETURNS:
     *   (anim &) this animation.
     */
    anim & SetScene( units::unit *NewScene );

    /* Initialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Init( VOID ) override;

    /* Close function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Close( VOID ) override;

    /* Resize function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Resize( VOID ) override;

    /* Timer function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Timer( VOID ) override;

    /* Activate function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Activate( VOID ) override;

    /* Idle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Idle( VOID ) override;

    /* Erase function.
     * ARGUMENTS:
     *   - device context:
     *       HDC hDC;
     * RETURNS: None.
     */
    VOID Erase( HDC hDC ) override;

    /* Paint function.
     * ARGUMENTS:
     *   - device context:
     *       HDC hDC;
     * RETURNS: None.
     */
    VOID Paint( HDC hDC ) override;

    /* Render function.
     * ARGUMENTS: None.
     * RETURNS: None. 
     */
    VOID Render( VOID );

    /* Response function.
     * ARGUMENTS: None.
     * RETURNS: None. 
     */
    VOID Response( VOID );
  };
} /* end of 'digl' namespace */



#endif /* _ANIM_H_ */


/* END OF 'anim.h' FILE */
