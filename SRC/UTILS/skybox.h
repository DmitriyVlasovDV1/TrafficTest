/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : skybox.h
 * PURPOSE     : Skybox header file.
 * PROGRAMMER  : Vlasov Dmitriy.
 * LAST UPDATE : 26.07.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support of 30 Phys-Math Lyceum.
 */

#ifndef __SKYBOX_H_
#define __SKYBOX_H_

/* Includes */
#include "../def.h"
#include "../ANIM/RENDER/prim.h"
#include <vector>

/* Animation project namespace */
namespace digl
{
  /* Skybox system representation type */
  class skybox
  {
  private:
    std::vector<texture *> SkyTexs;
    shader *Shader;
    primitives::prim *Box;

  public:
    /* Skybox constructor function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    skybox( VOID )
    {
    } /* End of 'skybox' function */

    /* Skybox initialization function. 
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Init( VOID );

    /* Add new textureblock function. 
     * ARGUMENTS:
     *   - file name prefix:
     *       const std::string FileNamePrefix;
     *   - images names:
     *       const std::string FNXpos, FNXneg, FNYpos,
     *                         FNYneg, FNZpos, FNZneg;
     * RETURNS: None.
     */
    VOID AddSkyTex( const std::string FileNamePrefix,
                    const std::string FNXpos,
                    const std::string FNXneg,
                    const std::string FNYpos,
                    const std::string FNYneg,
                    const std::string FNZpos,
                    const std::string FNZneg );

    /* Draw skybox function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Draw( VOID );
  }; /* End of 'skybox' class */
} /* end of 'digl' namespace */

#endif /* __SKYBOX_H_ */



/* END OF 'skybox.h' FILE */

