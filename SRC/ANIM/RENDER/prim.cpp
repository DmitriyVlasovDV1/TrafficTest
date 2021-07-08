/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : prim.cpp
 * PURPOSE     : primitives function file.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 25.07.2020
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */

#include "prim.h"
#include "../anim.h"

using namespace digl;

struct MaterialG3DM
{
  CHAR Name[300];
  vec3 Ka, Kd, Ks;
  FLT Ph, Trans;
  INT Tex[8];
  CHAR ShaderStr[300];
  INT ShdNo;
};

struct TextureG3DM
{
  CHAR Name[300];
  INT W, H;
  UINT TexId;
};

/* Load topo from file function.
 * ARGUMENTS:
 *   - file name:
 *       const CHAR *FileName;
 * RETUNRNS: None.
 */
primitives::primitives * primitives::primitives::LoadG3DM( const CHAR *FileName, shader *Shd, const matr &LoadTransfrom = matr::Identity() )
{
  anim* AC = anim::GetPtr();
  FILE *F;
  INT flen, NoofP, NoofM, NoofT, p, m, t;
  DWORD Sign;
  BYTE *mem, *ptr;

  /* Load file */
  if ((F = fopen(FileName, "rb")) == nullptr)
    return nullptr;

  /* Get file length */
  fseek(F, 0, SEEK_END);
  flen = ftell(F);
  rewind(F);

  /* Allocate memory */
  if ((mem = new BYTE[flen]) == nullptr)
  {
    fclose(F);
    return nullptr;
  }

  /* Read data */
  fread(mem, 1, flen, F);
  fclose(F);

  ptr = mem;
  Sign = *(DWORD *)ptr;
  ptr += 4;

  if (Sign != *(DWORD *)"G3DM")
  {
    delete[] mem;
    return nullptr;
  }

  NoofP = *(INT *)ptr;
  ptr +=  4;
  NoofM = *(INT *)ptr;
  ptr +=  4;
  NoofT = *(INT *)ptr;
  ptr +=  4;

  std::map<prim *, INT> MtlNoTable;
  for (p = 0; p < NoofP; p++)
  {
    INT i;

    INT NoofV, NoofI, MtlNo;

    NoofV = *(INT *)ptr;
    ptr += 4;
    NoofI = *(INT *)ptr;
    ptr += 4;
    MtlNo = *(INT *)ptr;
    ptr += 4;

    vertex::std *V = (vertex::std *)ptr;
    ptr += sizeof(vertex::std) * NoofV;
    INT *I = (INT *)ptr;
    ptr += sizeof(INT) * NoofI;

    topology::base<vertex::std> Topo;

    /* Transform verticies */
    for (i = 0; i < NoofV; i++)
    {
      V[i].P = LoadTransfrom.TransformPoint(V[i].P);
      V[i].N = LoadTransfrom.TransformVector(V[i].N);
      Topo.Vertex << V[i];
    }
    for (i = 0; i < NoofI; i++)
    {
      Topo.Index << I[i];
    }

    /* Add a new primitive */
    prim *Pr = AC->PrimCreate(Topo);;
    Prims << Pr;
    MtlNoTable[Pr] = MtlNo;
  }

  /* Textures id table */
  std::map<material *, std::vector<INT>> TexIdTable;

  /* Read materials */
  for (m = 0; m < NoofM; m++)
  {
    MaterialG3DM *Mtl = (MaterialG3DM *)ptr;

    for (auto el : MtlNoTable)
      if (el.second == m)
      {
        el.first->Material = AC->MaterialCreate(Shd, Mtl->Ka, Mtl->Kd, Mtl->Ks, Mtl->Ph, Mtl->Trans);

        for (int k = 0; k < 8; k++)
          if (k < 0 || Mtl->Tex[k] != -1)
            TexIdTable[el.first->Material].push_back(Mtl->Tex[k]);
      }

    ptr += sizeof(MaterialG3DM);
  }

  /* Read textures */
  for (t = 0; t < NoofT; t++)
  {
    TextureG3DM *Tex = (TextureG3DM *)ptr;
    ptr += sizeof(TextureG3DM);
    for (auto el : TexIdTable)
      for (int k = 0; k < el.second.size(); k++)
        if (el.second[k] == t)
          el.first->Textures.push_back(AC->TextureCreate( Tex->Name, Tex->W, Tex->H, (DWORD *)ptr ));

    ptr += 4 * Tex->W * Tex->H;
  }

  fclose(F);
  delete[] mem;
  return this;
}


/* END OF 'prim.cpp' FILE */
