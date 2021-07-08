/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : pipeline.cpp
 * PURPOSE     : Pipeline file.
 * PROGRAMMER  : Vlasov Dmitriy.
 * LAST UPDATE : 19.09.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support of 30 Phys-Math Lyceum.
 */

/* Includes */
#include "pipeline.h"
#include "../anim.h"
#include "res.h"

/* Animation project namespace */
namespace digl
{
  /* Pipeline initialization function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID pipeline::Init( VOID )
  {
    FBOs.push_back(new frameBufferObject(1, TRUE));
    Shaders.push_back(anim::Get().ShaderCreate("SRC/BIN/SHADER/SCREEN/"));
    Skybox.Init();
    Skybox.AddSkyTex("SRC/BIN/SKYBOXES/LIGHT/",
                     "XPOS.bmp",
                     "XNEG.bmp",
                     "YPOS.bmp",
                     "YNEG.bmp",
                     "ZPOS.bmp",
                     "ZNEG.bmp");
  } /* End of 'pipeline::Init' function */

  /* Start pipeline function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */
  VOID pipeline::Start( VOID )
  {
    glBindFramebuffer(GL_FRAMEBUFFER, FBOs.at(0)->FBOId);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Skybox.Draw();
  } /* End of 'Start' function */

  /* End pipeline function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */
  VOID pipeline::End( VOID )
  {
    /* Waiting for drawing in first FBO */
    glFinish();

    /* Bind screen buffer */
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Shader*/
    INT prg = Shaders.at(0)->ProgId;
    glUseProgram(prg);

    /* Textures */
    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, FBOs.at(0)->Attachments.at(0)->TexId);

    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, FBOs.at(0)->DepthTex->TexId);

    /* Uniforms */
    INT loc;
    if ((loc = glGetUniformLocation(prg, "Time")) != -1)
      glUniform1f(loc, anim::Get().Time);

    /* Draw */
    glDrawArrays(GL_POINTS, 0, 1);
    glUseProgram(0);

    /* Waiting for drawing to screen buffer */
    glFinish();

  } /* End of 'End' function */

  /* Resize pipeline function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID pipeline::Resize( VOID )
  {
    for (auto i : FBOs)
      i->Resize();
  } /* End of 'Resize' function */

} /* end of 'digl' namespace */

/* END OF 'pipeline.cpp' FILE */
