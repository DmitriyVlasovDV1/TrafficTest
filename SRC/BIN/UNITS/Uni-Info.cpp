#if 0
/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : Uni-Uaz.h
 * PURPOSE     : Unit uaz file.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 30.07.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */

#include "../../SRC/ANIM/anim.h"

using namespace digl;

class unit_info : public units::unit
{
  font *Fnt;
  CHAR Buf[100];

public:
  unit_info( anim *AC )
  {
    Fnt = AC->FontCreate("SRC/BIN/Fonts/Bookman.g3df");
  }

  ~unit_info( VOID )
  {
  }

  VOID Response( anim *AC ) override
  {
  }

  VOID Render( anim *AC ) override
  {
    sprintf(Buf, "FPS: %lf", anim::Get().FPS);
    Fnt->Draw(std::string(Buf), Fnt->Transform);
  }

};


static digl::anim::unit_register<unit_info> _("Info");


/* END OF 'Uni_Info.cpp' FILE */
#endif
