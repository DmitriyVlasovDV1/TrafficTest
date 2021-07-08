/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : fbo.cpp
 * PURPOSE     : FBO file.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 20.08.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */

/* Includes */
#include "../../def.h"
#include "../anim.h"
#include "fbo.h"

/* Animation project namespace */
namespace digl
{
  /* FBO create function.
   * ARGUMENTS: None.
   * RETUNRS: None.
   */
  VOID frameBufferObject::Create( const INT InNumOfAttachments, const BOOL InIsDepthTex )
  {
    NumOfAttachments = InNumOfAttachments;
    IsDepthTex = InIsDepthTex;
    anim *AC = anim::GetPtr();

    /* Generate buffer descriptor */
    glGenFramebuffers(1, &FBOId);
    /* Bind this buffer*/
    glBindFramebuffer(GL_FRAMEBUFFER, FBOId);

    /* Create attachmnets*/
    for (INT i = 0; i < NumOfAttachments; i++)
    {
      Attachments.push_back(AC->TextureCreate(AC->FrameW, AC->FrameH, GL_RGBA32F));
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i,
                             GL_TEXTURE_2D, Attachments.at(i)->TexId, 0);
    }

    UINT DrawBuffer[8] = {GL_COLOR_ATTACHMENT0,
                          GL_COLOR_ATTACHMENT1,
                          GL_COLOR_ATTACHMENT2,
                          GL_COLOR_ATTACHMENT3,
                          GL_COLOR_ATTACHMENT4,
                          GL_COLOR_ATTACHMENT5,
                          GL_COLOR_ATTACHMENT6,
                          GL_COLOR_ATTACHMENT7};

    glDrawBuffers(NumOfAttachments, DrawBuffer);

    /* Render buffer */
    if (IsDepthTex)
    {
      DepthTex = AC->TextureCreate();
      glGenTextures(1, &(DepthTex->TexId));
      glBindTexture(GL_TEXTURE_2D, DepthTex->TexId);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, AC->FrameW, AC->FrameH, 0,
                   GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 

      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, DepthTex->TexId, 0);
    }
    else
    {
      glGenRenderbuffers(1, &RBuf);
      glBindRenderbuffer(GL_RENDERBUFFER, RBuf);
      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, AC->FrameW, AC->FrameH);
      glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBuf);
    }

    INT status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
      Free();
  } /* End of 'frameBufferObject::Create' function */

 /* FBO close function.
  * ARGUMENTS: None.
  * RETUNRS: None.
  */
  VOID frameBufferObject::Free( VOID )
  {
    Attachments.clear();
    if (IsDepthTex)
      DepthTex = nullptr;
    else
    {
      glBindRenderbuffer(GL_RENDERBUFFER, RBuf);
      glDeleteRenderbuffers(1, &RBuf);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, FBOId);
    glDeleteFramebuffers(1, &FBOId);
  } /* End of 'frameBufferObject::Close' function */

  /* FBO resize function.
  * ARGUMENTS: None.
  * RETUNRS: None.
  */
  VOID frameBufferObject::Resize( VOID )
  {
    Free();
    Create(NumOfAttachments, IsDepthTex);
  } /* End of 'frameBufferObject::Resize' function */
} /* end of 'digl' namespace */

/* END OF 'fbo.h' FILE */

