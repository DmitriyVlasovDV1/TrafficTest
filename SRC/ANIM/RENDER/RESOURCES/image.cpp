/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : image.cpp
 * PURPOSE     : image functionfile.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 28.07.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */

#include "image.h"
/* Load image from file.
 * ARGUMENTS:
 *   - file name:
 *       const std::string &FileName;
 * RETURNS: None.
 */ 
digl::image::image( const std::string &FileName ) :
  Pixels(), RowsD(), RowsB()
{
  HBITMAP hBm;
  if ((hBm = (HBITMAP)LoadImage(nullptr, FileName.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION)) != nullptr)
  {
    // Case of BMP file
    BITMAP bm;
    GetObject(hBm, sizeof(bm), &bm);

    Width = bm.bmWidth;
    Height = bm.bmHeight;

    Pixels.resize(bm.bmWidth * bm.bmHeight * 4);
    for (INT y = 0; y < bm.bmHeight; y++)
      for (INT x = 0; x < bm.bmWidth; x++)
      {
        Pixels[(y * bm.bmWidth + x) * 4 + 0] =
          *((BYTE *)bm.bmBits + y * bm.bmWidthBytes + x * bm.bmBitsPixel / 8 + 0);
        Pixels[(y * bm.bmWidth + x) * 4 + 1] =
          *((BYTE *)bm.bmBits + y * bm.bmWidthBytes + x * bm.bmBitsPixel / 8 + 1);
        Pixels[(y * bm.bmWidth + x) * 4 + 2] =
          *((BYTE *)bm.bmBits + y * bm.bmWidthBytes + x * bm.bmBitsPixel / 8 + 2);
        Pixels[(y * bm.bmWidth + x) * 4 + 3] = 255;
      }
    DeleteObject(hBm);

    // Make alpha channel
    /*
    for (INT i = 3; i < Width * Height * 4; i += 4)
      Pixels[i] = 255;
    */
  }
  else
  {
    FILE *F;

    if ((F = fopen(FileName.c_str(), "rb")) != nullptr)
    {
      // Case of G24/G32
      INT fw = 0, fh = 0;
      fread(&fw, 2, 1, F);
      fread(&fh, 2, 1, F);
      fseek(F, 0, SEEK_END);
      INT flen = ftell(F);
      if (flen == 4 + fw * fh * 3)
      {
        // G24
        fseek(F, 4, SEEK_SET);
        Pixels.resize(fw * fh * 4);
        Width = fw;
        Height = fh;
        for (INT r = 0, p = 0; r < fh; r++)
          for (INT c = 0; c < fw; c++)
          {
            BYTE rgb[3];
            fread(rgb, 3, 1, F);
            Pixels[p++] = rgb[0];
            Pixels[p++] = rgb[1];
            Pixels[p++] = rgb[2];
            Pixels[p++] = 255;
          }
      }
      else if (flen == 4 + fw * fh * 3)
      {
        // G32
        fseek(F, 4, SEEK_SET);
        Pixels.resize(fw * fh * 4);
        Width = fw;
        fread(&Pixels[0], 4, fw * fh, F);
      }
      fclose(F);
    }
  }
  // Setup row pointers
  INT i;
  RowsD.resize(Height);
  i = 0;
  for (auto &r : RowsD)
    r = (DWORD *)&Pixels[i++ * Width * 4];
  RowsB.resize(Height);
  i = 0;
  for (auto &r : RowsB)
    r = (BYTE (*)[4])&Pixels[i++ * Width * 4];
} /* End of 'digl::image::image' function */

/* END OF 'image.cpp' FILE */