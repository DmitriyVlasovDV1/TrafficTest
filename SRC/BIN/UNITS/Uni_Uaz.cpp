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
#include "../../UTILS/geom.h"
#include "../../UTILS/particles.h"

using namespace digl;

class my_unit : public units::unit
{
  primitives::primitives *Pr4;
  primitives::primitives *Pr3;
  primitives::primitives *Pr2;
  primitives::prim *Pr;
  geom* Car;
  geom* Box;
  geom* Stick;

  emitterWaterDrop *Emitter;


public:
  my_unit( anim *AC )
  {
    vec3 V(0, 0, 0);

    Emitter = AC->EmitterCreate<emitterWaterDrop>();
    Emitter->Init(TRUE, 0.1, 5);
    Emitter->Matr = matr::Translate(V.Set(0, 0, 6.2));
    shader* Sh = AC->ShaderCreate("SRC/BIN/SHADER/DEFAULT2/");

    //Pr4 = new primitives::primitives(AC, (CHAR *)"BIN/MODELS/G3DM/uaz_452.g3dm", Sh, matr::RotateY(-90) * matr::Scale(vec3(0.005)));
    //topology::sphere<vertex::std>Topo(vec3(0), 50, 20, 20);
    //Pr = AC->PrimCreate(Topo);
    topology::cube<digl::vertex::std> Topo(4, 15, 4, 10);
    Pr = AC->PrimCreate(Topo);
    Pr->SetMaterial(AC->MaterialCreate(Sh));

    Pr3 = AC->PrimsCreate();
    *Pr3 << Pr;

    topology::cube<digl::vertex::std> Topo1(0.5, 0.5, 10, 5);
    Pr = AC->PrimCreate(Topo1);
    Pr->SetMaterial(AC->MaterialCreate(Sh));

    Pr2 = AC->PrimsCreate();
    *Pr2 << Pr;

    //Pr3->Transform = matr::Translate(V);
    
    Pr4 = AC->PrimsLoad((const CHAR *)"SRC/BIN/MODELS/G3DM/x6.g3dm", Sh, matr::Scale(vec3(1)) * matr::RotateX(-90));
    //Pr4 = new primitives::primitives((CHAR *)"../SRC/BIN/MODELS/G3DM/uaz_452.g3dm", Sh, matr::Scale(vec3(0.01)) * matr::RotateY(-90));

    Car = AC->GeomCreate();
    Box = AC->GeomCreate();
    Stick = AC->GeomCreate();

    //Car->SetMatrix(matr::Translate(V.Set(0, 100, 0)));
    Box->SetMatrix(matr::Translate(V.Set(0, 10, -20)));

    Car->AddPrims(Pr4);
    Box->AddPrims(Pr3);
    Stick->AddPrims(Pr2);
    Car->AddChild(Box);
    Box->AddChild(Stick);
    Stick->AddEmitter(Emitter);

    Stick->SetMatrix(matr::Translate(V.Set(0, 8, 5)));
    Car->SetMatrix(matr::Translate(V.Set(0, 13, 0)));
  }

  ~my_unit( VOID )
  {
  }

  VOID Response( anim *AC ) override
  {
    static DBL LastTime = AC->Time;
    vec3 V(0, 5, 0);
    V *= sin(AC->Time);

    //Pr4->Transform = Pr4->Transform * matr::RotateY(10 * (AC->Time - LastTime));
    Car->ApplyMatrix(matr::RotateY(10 * (AC->Time - LastTime)));
    Stick->ApplyMatrix(matr::RotateY(-35 * (AC->Time - LastTime)));

    Car->Response();


    LastTime = AC->Time;
  }

  VOID Render( anim *AC ) override
  {

    //AC->DrawPrims(*Pr4, Pr4->Transform);
    //AC->Draw(*Pr, Pr->Transform);
    Car->Draw();
    //Emitter.Draw();


  }

};

static digl::anim::unit_register<my_unit> _("Uaz");
