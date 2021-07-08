/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : texture.H
 * PURPOSE     : Animation functions.
 * PROGRAMMER  : Vlasov Dmitriy.
 * LAST UPDATE : 29.07.2020.
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __TEXTURE_H_
#define __TEXTURE_H_

#include "../../../def.h"

#include "image.h"

#include <string>

/* Animation project */
namespace  digl
{
  /* Texture representation type */
  class texture
  {
  public:
    UINT TexId;
    INT W, H;
    std::string Name;

    /* Texture constructor. 
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    texture( VOID ) : W(0), H(0), TexId(-1), Name()
    {
    } /* End of 'texture' function */

    /* Texture constructor. 
     * ARGUMENTS:
     *   - width, height:
     *       const INT InW, InH;
     *   - format:
     *       const INT Format;
     *   - name:
     *       const std::string &InName;
     * RETURNS: None.
     */
    texture( const INT InW, const INT InH, const INT Format, const std::string &InName = "" ) :
      W(InW), H(InH), TexId(-1), Name(InName)
    {
      glGenTextures(1, &TexId);
      glBindTexture(GL_TEXTURE_2D, TexId);
      glTexStorage2D(GL_TEXTURE_2D, 1, Format, W, H);
    } /* End of 'texture' function */

    /* Texture constructor. 
     * ARGUMENTS:
     *   - 
     * RETURNS: None.
     */
    texture( const std::string &InName, const std::string &FileName ) : W(0), H(0), TexId(-1), Name(InName)
    {
      image Img(FileName);

      W = Img.W;
      H = Img.H;

      glGenTextures(1, &TexId);
      glBindTexture(GL_TEXTURE_2D, TexId);
      if (Img.RowsD.size() != 0)
      {
        INT levels = log(mth::Max(W, H)) / log(2) + 1;

        glTexStorage2D(GL_TEXTURE_2D, levels, GL_RGBA8, W, H);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, W, H, GL_BGRA_EXT, GL_UNSIGNED_BYTE, Img.RowsD[0]);
        glGenerateMipmap(GL_TEXTURE_2D);
      }
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } /* End of 'texture' function */

    /* Texture constructor. 
     * ARGUMENTS:
     *   - 
     * RETURNS: None.
     */
    texture( const std::string &InName, const INT InW, const INT InH, const DWORD *Img ) :
      W(0), H(0), TexId(-1), Name(InName)
    {
      W = InW;
      H = InH;

      glGenTextures(1, &TexId);
      glBindTexture(GL_TEXTURE_2D, TexId);
      INT levels = log(mth::Max(W, H)) / log(2) + 1;

      glTexStorage2D(GL_TEXTURE_2D, levels, GL_RGBA8, W, H);
      glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, W, H, GL_BGRA_EXT, GL_UNSIGNED_BYTE, Img);
      glGenerateMipmap(GL_TEXTURE_2D);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } /* End of 'texture' function */

    /* Texture constructor. 
     * ARGUMENTS:
     *   - 
     * RETURNS: None.
     */
    texture( const std::string &InName, const INT InW, const INT InH, const BYTE *Img ) :
      W(0), H(0), TexId(-1), Name(InName)
    {
      W = InW;
      H = InH;

      glGenTextures(1, &TexId);
      glBindTexture(GL_TEXTURE_2D, TexId);
      INT levels = log(mth::Max(W, H)) / log(2) + 1;

      glTexStorage2D(GL_TEXTURE_2D, levels, GL_RGBA8, W, H);
      glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, W, H, GL_BGRA_EXT, GL_UNSIGNED_BYTE, Img);
      glGenerateMipmap(GL_TEXTURE_2D);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } /* End of 'texture' function */

    /* Destructor */
    ~texture( VOID )
    {
      glDeleteTextures(1, &TexId);
    } /* End of '~texture' function */
  }; /* End of 'texture' class */
}


#endif /* __TEXTURE_H _ */

/* END OF 'texture.h' FILE */
