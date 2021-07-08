#if 0
/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : physics.h
 * PURPOSE     : physics utils headerfile.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 11.10.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */

#ifndef __UNIFORMS_H_
#define __UNIFORMS_H_

/* Includes */
#include "../../def.h"

/* Animation project namespace */
namespace digl
{
  /* Uniform system representation type */
  class uniformSystem
  {
  private:

  public:
    VOID SendUniforms( UINT PrgID, CHAR * const Types, CHAR * const Names, CHAR * const Data )
    {
      CHAR *TypesPtr = Types;
      CHAR *NamesPtr = Names;
      CHAR Buf[100];
      while (TypesPtr++ != 0)
      {
        while (*NamesPtr++ != ',')
        {
          Buf
        }
      }
    } /* End of 'SendUniforms' function */

  }; /* End of 'uniformSystem' class */
} /* end of 'digl' namespace */

#endif /* __PHYSICS_H_ */
/* END OF 'physics.h' FILE */


#endif