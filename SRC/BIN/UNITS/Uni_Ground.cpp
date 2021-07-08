/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : Uni-Uaz.cpp
 * PURPOSE     : unit uaz file.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 30.07.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */

#include "../../ANIM/anim.h"
#include <vector>
#include <cmath>

using namespace digl;

class ground_unit : public units::unit
{
  primitives::prim *Ground;
  primitives::prim *Water;
  std::vector<primitives::primitives *> Trees;
  std::vector<vec3> TreePositions;
  INT NumOfTrees = 20;
  FLT LandscapeSize = 500;
  shader *TreeSh;

public:
  ground_unit( anim *AC )
  {
    /* Water */
    shader* Sh = AC->ShaderCreate("SRC/BIN/SHADER/WATER/");
    topology::plane<digl::vertex::std> Topo1(vec3(-0.5 * LandscapeSize, 0, -0.5 * LandscapeSize),
                                            vec3(LandscapeSize, 0, 0),
                                            vec3(0, 0, LandscapeSize), 300, 300);
    Water = AC->PrimCreate(Topo1);
    Water->SetMaterial(AC->MaterialCreate(Sh));

    Water->Material->Textures.push_back(
      AC->TextureCreate("", "SRC/BIN/TEXTURES/LANDSCAPE/water.bmp"));
    Water->Transform = matr::Translate(vec3(0, 13, 0));
    /* Ground */
    Sh = AC->ShaderCreate("SRC/BIN/SHADER/LANDSCAPE/");
    topology::plane<digl::vertex::std> Topo(vec3(-0.5 * LandscapeSize, 0, -0.5 * LandscapeSize),
                                            vec3(LandscapeSize, 0, 0),
                                            vec3(0, 0, LandscapeSize), 300, 300);
    Ground = AC->PrimCreate(Topo);

    Ground->SetMaterial(AC->MaterialCreate(Sh));

    texture *Height;
    Ground->Material->Textures.push_back(
      AC->TextureCreate("", "SRC/BIN/TEXTURES/LANDSCAPE/texture_materials2.bmp"));
    Ground->Material->Textures.push_back(
      AC->TextureCreate("", "SRC/BIN/TEXTURES/LANDSCAPE/texture_grass.bmp"));
    Ground->Material->Textures.push_back(
      AC->TextureCreate("", "SRC/BIN/TEXTURES/LANDSCAPE/texture_stone.bmp"));
    Ground->Material->Textures.push_back(
      AC->TextureCreate("", "SRC/BIN/TEXTURES/LANDSCAPE/texture_dirt.bmp"));
    Ground->Material->Textures.push_back(
      AC->TextureCreate("", "SRC/BIN/TEXTURES/LANDSCAPE/texture_sand.bmp"));
    Ground->Material->Textures.push_back(
      Height = AC->TextureCreate("", "SRC/BIN/TEXTURES/LANDSCAPE/texture_height2.bmp"));

    Ground->Transform = matr::Translate(vec3(0, 0, 0));

    /* Trees */
    TreeSh = AC->ShaderCreate("SRC/BIN/SHADER/TREES/");
    primitives::primitives *Source = AC->PrimsLoad((const CHAR *)"SRC/BIN/MODELS/G3DM/ficus.g3dm", TreeSh, matr::Scale(vec3(0.1)));

    for (INT i = 0; i < NumOfTrees; ++i)
    {
      primitives::primitives *Tree = AC->PrimsCreate();
      Tree->Prims = Source->Prims;
      vec3 Pos = vec3(std::cos(i + 16), 0, std::sin(i + 16)) *
                      (LandscapeSize * 0.5 * 0.87  + std::cos(i - 102) * LandscapeSize * 0.5 * 0.05);
      TreePositions.push_back(Pos);
      Tree->Transform = matr::Translate(Pos);

      for (auto el: Tree->Prims)
        el->Material->Textures.push_back(Height);
      Trees.push_back(Tree);
    }
  }

  ~ground_unit( VOID )
  {
  }

  VOID Response( anim *AC ) override
  {
  }

  VOID Render( anim *AC ) override
  {
    AC->Draw(*Ground, Ground->Transform);
    AC->Draw(*Water, Water->Transform);
    glUseProgram(TreeSh->ProgId);
    for (INT i = 0; i < NumOfTrees; ++i)
    {
      INT loc;
      if ((loc = glGetUniformLocation(TreeSh->ProgId, "TreePos")) != -1)
        glUniform3fv(loc, 1, TreePositions[i]);
      AC->DrawPrims(*Trees[i], Trees[i]->Transform);
    }
  }
};

static digl::anim::unit_register<ground_unit> _("Ground");
