/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : Uni_Skybox.cpp
 * PURPOSE     : skybox file.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 30.07.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */

#include "../../ANIM/anim.h"
#include "../../UTILS/skybox.h"

using namespace digl;

//texture( const std::string &InName, const std::string &FileName )
class skybox_unit : public units::unit
{
private:
  skybox Skybox;

public:
  skybox_unit( anim *AC ) : Skybox()
  {
    Skybox.AddSkyTex("SRC/BIN/SKYBOXES/LIGHT/",
                     "XPOS.bmp",
                     "XNEG.bmp",
                     "YPOS.bmp",
                     "YNEG.bmp",
                     "ZPOS.bmp",
                     "ZNEG.bmp");
  }

  ~skybox_unit( VOID )
  {
  }

  VOID Response( anim *AC ) override
  {
  }

  VOID Render( anim *AC ) override
  {
    Skybox.Draw();
  }

};

static digl::anim::unit_register<skybox_unit> _("Skybox");
