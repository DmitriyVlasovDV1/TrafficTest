/*************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : fonts.h
 * PURPOSE     : Animation project.
 *               Fonts handle declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2020.
 *               Vitaly A. Galinsky.
 * LAST UPDATE : 29.07.2020.
 * NOTE        : Module namespace 'vigl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __fonts_h_
#define __fonts_h_

#include <vector>
#include <string>

#include "../../../def.h"
#include "../prim.h"
#include "material.h"

/* Project namespace */
namespace digl
{
  /* Fonts representation class */
  class font
  {
  private:
    DWORD LineH, BaseH; // Font height and base line jeight in pixels
    FLT AdvanceX[256];  // Every letter glyph right offet values
    primitives::prim *Chars[256];   // Every letter primitive
    material *Mtl;
  public:
    matr Transform;

    /* Class construtor.
     * ARGUMENTS:
     *   - font file name:
     *       const std::string &FileName;
     */
    font( const std::string &FileName, const matr &Transform = matr::Identity() );

    /* Text drawing function.
     * ARGUMENTS:
     *   - text to draw:
     *       const std::string &Txt;
     * RETURNS: None.
     */
    VOID Draw( const std::string &Txt, const matr &World = matr::Identity() );
  }; /* End of image class */
} /* end of 'vigl' namespace */

#endif /* __fonts_h_ */

/* END OF 'fonts.h' FILE */

