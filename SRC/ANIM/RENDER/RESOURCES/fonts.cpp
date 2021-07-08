/*************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : fonts.h
 * PURPOSE     : Animation project.
 *               Fonts handle implementation module.
 * PROGRAMMER  : CGSG-SummerCamp'2020.
 *               Vitaly A. Galinsky.
 * LAST UPDATE : 29.07.2020.
 * NOTE        : Module namespace 'vigl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <exception>

#include "../../anim.h"
#include "fonts.h"

/* Class construtor.
  * ARGUMENTS:
  *   - font file name:
  *       const std::string &FileName;
  */
digl::font::font( const std::string &FileName, const matr &Transform ) : Transform(Transform)
{
  FILE *F;
  DWORD Sign, W, H;
  vertex::std symbs[256][4];
  render *Rnd = anim::GetPtr();

  if ((F = fopen(FileName.c_str(), "rb")) == nullptr)
    throw std::exception((std::string("Font file ") + FileName + " is not found").c_str());

  fread(&Sign, 4, 1, F);
  if (Sign != *(DWORD *)"G3DF")
  {
    fclose(F);
    throw std::exception("File is not G3DF");
  }
  fread(&LineH, 4, 1, F);
  fread(&BaseH, 4, 1, F);
  fread(AdvanceX, 4, 256, F);
  fread(symbs, sizeof(vertex::std), 4 * 256, F);

  fread(&W, 4, 1, F);
  fread(&H, 4, 1, F);
  std::vector<BYTE> tex;
  tex.resize(W * H * 4);
  fread(&tex[0], 4, W * H, F);

  //Mtl = Rnd->MaterialCreate(FileName);
  Mtl = Rnd->MaterialCreate(Rnd->ShaderCreate("SRC/BIN/SHADER/FONTS/"), vec3(1), vec3(1), vec3(1), 1, 1);
  Mtl->Textures.push_back(Rnd->TextureCreate(FileName, W, H, &tex[0]));

  for (INT i = 0; i < 256; i++)
  {
    topology::base<vertex::std> Topo;
    Topo.PrimType = prim_type::STRIP;
    Topo.Vertex << symbs[i][0] << symbs[i][1] << symbs[i][2] << symbs[i][3];
    Topo.Index << 0 << 1 << 2 << 3;

    Chars[i] = Rnd->PrimCreate(Topo);
    Chars[i]->Material = Mtl;
  }

  fclose(F);
} /* End of 'vigl::font::font' function */

/* Text drawing function.
 * ARGUMENTS:
 *   - text to draw:
 *       const std::string &Txt;
 * RETURNS: None.
 */
VOID digl::font::Draw( const std::string &Txt, const matr &World )
{
  vec3 Pos {0, 0, 0};
  render *Rnd = anim::GetPtr();

  for (auto c : Txt)
  {
    if (c == '\n')
      Pos[0] = 0, Pos[1] -= 1;
    else
    {
      Rnd->Draw( *Chars[(BYTE)c], matr::Translate(Pos) * World);
      Pos[0] += AdvanceX[(BYTE)c];
    }
  }
} /* End of 'digl::font::Draw' function */

/* END OF 'fonts.cpp' FILE */

