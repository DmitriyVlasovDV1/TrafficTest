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

#include "../../ANIM/anim.h"
#if 0
using namespace digl;

class my_unit1 : public units::unit
{

  primitives::prim *Pr;

public:
  my_unit1 ( anim *AC )
  {
    shader *Sh = AC->ShaderCreate("../SRC/BIN/SHADER/DEFAULT2/default");
    
    topology::plane<digl::vertex::std> Topo(vec3(0, 0, 0), vec3(1, 0, 0), vec3(0, 0, 0.5), 10, 10);
    Pr = AC->PrimCreate(Topo);
    
    Pr->SetMaterial(AC->MaterialCreate(Sh));
  }

  ~my_unit1( VOID )
  {
  }

  VOID Response( anim *AC ) override
  {
    //Pr->Transform = Pr->Transform * matr::RotateX(0.01);
  }

  VOID Render( anim *AC ) override
  {
    AC->Draw(*Pr, Pr->Transform);
  }
};

static digl::anim::unit_register<my_unit1> _("Tor");
#endif