/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : skybox.cpp
 * PURPOSE     : Skybox file.
 * PROGRAMMER  : Vlasov Dmitriy.
 * LAST UPDATE : 26.07.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support of 30 Phys-Math Lyceum.
 */

/* Includes */
#include "../anim.h"
#include "skybox.h"

/* Animation project namespace */
namespace digl
{
  /* Skybox initialization function. 
  * ARGUMENTS: None.
  * RETURNS: None.
  */
  VOID skybox::Init( VOID )
  {
    anim *AC = anim::GetPtr();
    Shader = AC->ShaderCreate("SRC/BIN/SHADER/SKYBOX/");
    topology::cube<digl::vertex::std> Topo(1, 1, 1, 2);
    Box = AC->PrimCreate(Topo);
    Box->SetMaterial(AC->MaterialCreate(Shader));
  } /* End of 'skybox' function */

  /* Add new textureblock function. 
    * ARGUMENTS:
    *   - file name prefix:
    *       const std::string FileNamePrefix;
    *   - images names:
    *       const std::string FNXpos, FNXneg, FNYpos,
    *                         FNYneg, FNZpos, FNZneg;
    * RETURNS: None.
    */
  VOID skybox::AddSkyTex( const std::string FileNamePrefix,
                  const std::string FNXpos,
                  const std::string FNXneg,
                  const std::string FNYpos,
                  const std::string FNYneg,
                  const std::string FNZpos,
                  const std::string FNZneg )
  {
    anim *AC = anim::GetPtr();
    UINT TexId;
    const std::string FileNames[6] = { FNXpos,
                                        FNXneg,
                                        FNYneg,
                                        FNYpos,
                                        FNZpos,
                                        FNZneg };

    glGenTextures(1, &TexId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, TexId);

    for (int i = 0; i < 6; i++)
    {
      const image Img = image(FileNamePrefix + FileNames[i]);

      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                    0, GL_RGBA, Img.W, Img.H, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, &Img.Pixels[0]);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    texture *Tex = AC->TextureCreate();
    Tex->TexId = TexId;
    SkyTexs.push_back(Tex);
  } /* End of 'AddASkyTex' fucntion */

  /* Draw skybox function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */
  VOID skybox::Draw( VOID )
  {
    anim *AC = anim::GetPtr();
    matr WVP = AC->Cam.VP;

    glLoadMatrixf(WVP);

    /* Shader */
    glUseProgram(Shader->ProgId);

    /* Textures */
    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, SkyTexs.at(0)->TexId);

    INT ProgId = Shader->ProgId;

    INT loc;
    if ((loc = glGetUniformLocation(ProgId, "MatrWVP")) != -1)
      glUniformMatrix4fv(loc, 1, FALSE, WVP);
    if ((loc = glGetUniformLocation(ProgId, "Time")) != -1)
      glUniform1f(loc, AC->Time);
    if ((loc = glGetUniformLocation(ProgId, "CamLoc")) != -1)
      glUniform3fv(loc, 1, AC->Cam.Loc);

    glDepthMask(FALSE);
    glBindVertexArray(Box->VA);
    if (Box->NumOfElements != 0)
    {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Box->IBuf);
      glDrawElements(GL_TRIANGLE_STRIP, Box->NumOfElements, GL_UNSIGNED_INT, NULL);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    else
      glDrawArrays(GL_TRIANGLE_STRIP, 0, Box->NumOfElements);
    glBindVertexArray(0);

    glDepthMask(TRUE);

  } /* End of 'Draw' function */
} /* end of 'digl' namespace */

/* END OF 'skybox.cpp' FILE */

