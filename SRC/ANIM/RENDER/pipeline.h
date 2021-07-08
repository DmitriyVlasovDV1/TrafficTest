/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : pipeline.h
 * PURPOSE     : Pipeline header file.
 * PROGRAMMER  : Vlasov Dmitriy.
 * LAST UPDATE : 26.07.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support of 30 Phys-Math Lyceum.
 */

#ifndef __PIPELINE_H_
#define __PIPELINE_H_

/* Includes */
#include "../../def.h"
#include "fbo.h"
#include "RESOURCES/shader.h"
#include "../../UTILS/skybox.h"

#include <vector>

/* Animation project namespace */
namespace digl
{
  /* Pipeline system representation type */
  class pipeline
  {
  private:
    std::vector<frameBufferObject *> FBOs;
    std::vector<shader *> Shaders;
    skybox Skybox;

  public:
    /* Pipeline constructor function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    pipeline ( VOID ) : Skybox()
    {
    } /* End of 'pipeline' function */

    /* Destructor */
    ~pipeline ( VOID )
    {
      for (auto i : FBOs)
        delete i;
    } /* End of '~pipeline' function */


    /* Pipeline initialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Init( VOID );

    /* Start pipeline function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Start( VOID );

    /* Resize pipeline function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Resize( VOID );

    /* End pipeline function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID End( VOID );

  }; /* End of 'pipeline' class */
} /* end of 'digl' namespace */

#endif /* __PIPELINE_H_ */



/* END OF 'pipeline.h' FILE */
