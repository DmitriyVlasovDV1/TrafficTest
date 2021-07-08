/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : Uni-Game.cpp
 * PURPOSE     : unit game file.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 30.07.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */

#include "../../ANIM/anim.h"
#include "../../UTILS/physics.h"

using namespace digl;

/* Target representation type */
class target
{
private:
  kinematicsVec Position;
  primitives::primitives *Prims;
  vec3 Center;
  FLT MaxDistance;
  DBL LastTimeChangeAccel, DeltaTimeChangeAccel;
  FLT Accel = 15;

public:
  /* Constructor */
  target( const vec3 &InCenter, const FLT InMaxDistance,
    const DBL InDeltaTimeChangeAccel, shader *InShader,
    primitives::primitives *InModel ) :
    Center(InCenter), MaxDistance(InMaxDistance), Prims(nullptr),
    LastTimeChangeAccel(0), Position(), DeltaTimeChangeAccel(InDeltaTimeChangeAccel)
  {
    anim *AC = anim::GetPtr();
    shader *Sh = InShader;
    Prims = InModel;
    vec3 V = vec3().Rnd1();
    V[1] = 0;
    Position.Init(FALSE, vec3(0, Center[1], 0), 0, 15, V * Accel);
  } /* End of 'target' function */

  /* Response function. */
  VOID Response( VOID )
  {
    anim *AC = anim::GetPtr();

    if (AC->Time - LastTimeChangeAccel > DeltaTimeChangeAccel)
    {
      LastTimeChangeAccel = AC->Time;
      vec3 V = vec3().Rnd1();
      V[1] = 0;
      Position.SetAccel(V * Accel);
    }

    if ( (!(Position.Value - Center) >= MaxDistance) )
    {
      LastTimeChangeAccel = AC->Time;
      vec3 V = (Center - Position.Value).Normalizing();
      V[1] = 0;
      Position.SetAccel(V * Accel);
    }

    Position.Compute();

  } /* End of 'Response' function */

  /* Draw function. */
  VOID Draw( VOID )
  {
    anim *AC = anim::GetPtr();
    vec3 V = Position.SpeedCur.Normalizing();

    AC->DrawPrims(*Prims, Prims->Transform *
        matr::Basis(V % vec3(0, 1, 0), vec3(0, 1, 0), V) *
        matr::Translate(Position.Value));
  } /* End of 'Draw' function */

};

#if 0
/* Player representation type */
class player
{
private:
public:
  player:
}; /* End of 'player' class */
#endif


class game_unit : public units::unit
{
public:
  std::vector<target *> Targets;
  geom *Player;
  INT NumOfTargets = 10;
  FLT PlayerAccel = 20;
  kinematicsVec PlayerPos;

  vec3 Center = vec3(0, 10, 0);
  FLT MaxDist = 70;
  emitterWaterDrop *Emitter;
  geom *Stick;


  game_unit( anim *AC )
  {
    /* Targets */
    shader *Sh = AC->ShaderCreate("SRC/BIN/SHADER/SEAGUL/");
    primitives::primitives *Pr1 = AC->PrimsLoad("SRC/BIN/MODELS/G3DM/SEAGUL.g3dm", Sh);
    for (int i = 0; i < NumOfTargets; i++)
      Targets.push_back(new target(Center + vec3(0, 40, 0), MaxDist, 4 + sin(i) * 1, Sh, Pr1));

    /* Player */
    Sh = AC->ShaderCreate("SRC/BIN/SHADER/DEFAULT2/");
    primitives::primitives *CarPr = AC->PrimsLoad((const CHAR *)"SRC/BIN/MODELS/G3DM/x6.g3dm", Sh, matr::Scale(vec3(10)) * matr::RotateX(-90));

    Player = AC->GeomCreate();
    Player->AddPrims(CarPr);
    PlayerPos.Init(FALSE, vec3(0, Center[1] + 3, 0), 0, 40);

    Emitter = AC->EmitterCreate<emitterWaterDrop>();
    Emitter->Init(TRUE, 0.1, 5);
    Emitter->Matr = matr::Translate(vec3(0, 0, 6.2));

    topology::cube<digl::vertex::std> Topo(4, 15, 4, 10);
    primitives::prim* Pr = AC->PrimCreate(Topo);
    Pr->SetMaterial(AC->MaterialCreate(Sh));

    primitives::primitives *Pr3 = AC->PrimsCreate();
    *Pr3 << Pr;

    topology::cube<digl::vertex::std> Topo1(0.5, 0.5, 10, 5);
    Pr = AC->PrimCreate(Topo1);
    Pr->SetMaterial(AC->MaterialCreate(Sh));

    primitives::primitives *Pr2 = AC->PrimsCreate();
    *Pr2 << Pr;

    //Pr3->Transform = matr::Translate(V);
    
    geom *Box = AC->GeomCreate();
    Stick = AC->GeomCreate();

    Box->SetMatrix(matr::Translate(vec3(0, 10, -20)));

    Box->AddPrims(Pr3);
    Stick->AddPrims(Pr2);
    Player->AddChild(Box);
    Box->AddChild(Stick);
    Stick->AddEmitter(Emitter);

    Stick->SetMatrix(matr::Translate(vec3(0, 8, 5)));

  }

  ~game_unit( VOID )
  {
  }

  VOID Response( anim *AC ) override
  {
    static DBL LastTime = AC->Time;
    /* Targets */
    for (auto el : Targets)
      el->Response();

    /* Player control */
    FLT
      StrideUp = AC->input::keyboard::Keys[87] - AC->input::keyboard::Keys[83],
      StrideRight = AC->input::keyboard::Keys[68] - AC->input::keyboard::Keys[65];

    if ( (!(PlayerPos.Value - Center)) >= MaxDist)
    {
      vec3 V = (Center - PlayerPos.Value).Normalizing();
      V[1] = 0;
      PlayerPos.SetAccel(V * PlayerAccel);
    }
    else if (!(StrideUp || StrideRight))
    {
      PlayerPos.SetAccel(PlayerPos.SpeedCur.Normalizing() * (-PlayerAccel));
    }
    else
    {
      vec3 V1 = vec3(AC->Cam.Dir[0], 0, AC->Cam.Dir[2]).Normalizing();
      vec3 V2 = (vec3(0, 1, 0) % V1).Normalizing();
      PlayerPos.SetAccel((V1 * StrideUp - V2 * StrideRight).Normalizing() * PlayerAccel);
    }

    PlayerPos.Compute();
      /*
    vec3 V = AC->Cam.Dir;
    Player->ApplyMatrix(matr::Translate(vec3(V[0], 0, V[1]) * PlayerSpeed * StrideUp));
    V = vec3(0, 1, 0) % V;
    Player->ApplyMatrix(matr::Translate(vec3(V[0], 0, V[1]) * PlayerSpeed * StrideRight));
    */
    static vec3 OldV(1, 0, 0);
    vec3 V = PlayerPos.SpeedCur.Normalizing();

    if ((!PlayerPos.SpeedCur) > 1)
    {
      Player->SetMatrix(matr::Basis(V % vec3(0, 1, 0), vec3(0, 1, 0), V) * matr::Translate(PlayerPos.Value));
      OldV = V;
    }
    else
    {
      Player->SetMatrix(matr::Basis(OldV % vec3(0, 1, 0), vec3(0, 1, 0), OldV) * matr::Translate(PlayerPos.Value));
    }

    AC->Cam.SetView(AC->Cam.Loc, PlayerPos.Value, vec3(0, 1, 0));

    Stick->ApplyMatrix(matr::RotateY(-35 * (AC->Time - LastTime)));

    Player->Response();
    LastTime = AC->Time;
  }

  VOID Render( anim *AC ) override
  {
    /* Targets */
    for (auto el : Targets)
      el->Draw();
    /* Player */
    Player->Draw();
  }

};

static digl::anim::unit_register<game_unit> _("Game");
