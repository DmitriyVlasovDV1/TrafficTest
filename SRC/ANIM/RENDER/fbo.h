/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : fbo.h
 * PURPOSE     : FBO header file.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 20.08.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */

#ifndef __FBO_H_
#define __FBO_H_

/* Includes */
#include "../../def.h"
#include "RESOURCES/texture.h"
#include <vector>

/* Animation project namespace */
namespace digl
{
  /* FBO representation type */
  class frameBufferObject
  {
  public:
    INT NumOfAttachments;
    std::vector<texture *> Attachments;
    UINT FBOId;
    UINT RBuf;
    BOOL IsDepthTex;
    texture *DepthTex;

    /* FBO constructor function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    frameBufferObject( const INT InNumOfAttachments = 1, const BOOL InIsDepthTex = FALSE ) :
      NumOfAttachments(InNumOfAttachments), IsDepthTex(InIsDepthTex),
      FBOId(0), RBuf(0), Attachments(), DepthTex(nullptr)
    {
      Create(InNumOfAttachments, InIsDepthTex);
    } /* End of 'frameBufferObject' function */

    /* Destructor */
    ~frameBufferObject( VOID )
    {
      Free();
    } /* End of 'frameBufferObject' function */

    /* FBO create function.
     * ARGUMENTS: None.
     * RETUNRS: None.
     */
    VOID Create( const INT InNumOfAttachments, const BOOL IsDepthTex );

    /* FBO close function.
     * ARGUMENTS: None.
     * RETUNRS: None.
     */
    VOID Free( VOID );

    /* Resize function.
     * ARGUMENTS: None.
     * RETUNRS: None.
     */
    VOID Resize( VOID );

  }; /* End of 'FrameBufferObject' class */
} /* end of 'digl' namespace */

#endif /* __FBO_H_*/

/* END OF 'fbo.h' FILE */

