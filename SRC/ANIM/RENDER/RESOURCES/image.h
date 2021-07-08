/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : image.h
 * PURPOSE     : iamge file.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 28.07.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */

#ifndef __IMAGE_H_
#define __IMAGE_H_

#include "../../../def.h"
#include <vector>

/* Animation namspace */
namespace digl
{
  /* Image representation class */
  class image
  {
  private:
    // Image size in pixels
    INT Width = 0, Height = 0;
  public:
    // Image pixel data
    std::vector<BYTE> Pixels;
    // Rows access pointer by DWORD
    std::vector<DWORD *> RowsD;
    // Rows access pointer by BYTE quads
    std::vector<BYTE (*)[4]> RowsB;

    // Image size references
    INT &W = Width, &H = Height;

    /* Class default construtor */
    image( VOID );


    /* Class construtor.
     * ARGUMENTS:
     *   - image file name:
     *       const std::string &FileName;
     */
    image( const std::string &FileName );

  }; /* End of image class */
} /* end of 'digl' namespace */

#endif /* __IMAGE_H_ */

/* END OF 'image.h' FILE */