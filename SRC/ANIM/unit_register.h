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


#ifndef __UNIT_REGISTER_H_
#define __UNIT_REGISTER_H_

#include "anim.h"

namespace digl
{
  template<class UnitType>
    class unit_register
    {
    public:
      /* Unit creation function.
        * ARGUMENTS: None.
        * RETURNS:
        *   (unit *) New unit.
        */
      static anim::units::unit * Create( VOID )
      {
        return new UnitType(&anim::Get());
      } /* End of 'Create' function */

      /* Unit register constructor.
        * ARGUMENTS:
        *   - name:
        *       const std::string &Name;
        * RETURNS: None.
        */
      unit_register( const std::string &Name )
      {
        anim::Get().UnitNames[Name] = this->Create;
      } /* End of 'unit_register' function */
    }; /* End of 'unit_register' class */
}

#endif 