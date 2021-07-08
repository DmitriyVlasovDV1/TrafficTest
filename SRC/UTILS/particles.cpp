/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : particles.cpp
 * PURPOSE     : particles utils file.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 10.09.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */


/* Includes */
#include "../ANIM/anim.h"
#include "particles.h"

/* Animation project namespace */
namespace digl
{
  /* Draw particle function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */
  VOID particle::Draw( VOID )
  {
    anim *AC = anim::GetPtr();

    /* Shader */
    UINT ProgId = Shader->ProgId;
    glUseProgram(ProgId);

    /* Texture */
    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, Texture->TexId);

    /* Uniforms */
    INT loc;
    if ((loc = glGetUniformLocation(ProgId, "MatrW")) != -1)
      glUniformMatrix4fv(loc, 1, FALSE, Matr);
    if ((loc = glGetUniformLocation(ProgId, "MatrVP")) != -1)
      glUniformMatrix4fv(loc, 1, FALSE, AC->Cam.VP);
    if ((loc = glGetUniformLocation(ProgId, "Trans")) != -1)
      glUniform1f(loc, Trans.Value);
    if ((loc = glGetUniformLocation(ProgId, "Rotation")) != -1)
      glUniform1f(loc, Rotation.Value);
    if ((loc = glGetUniformLocation(ProgId, "Size")) != -1)
      glUniform1f(loc, Size.Value);
    if ((loc = glGetUniformLocation(ProgId, "Position")) != -1)
      glUniform3fv(loc, 1, Position.Value);
    if ((loc = glGetUniformLocation(ProgId, "CamLoc")) != -1)
      glUniform3fv(loc, 1, AC->Cam.Loc);

    /* Draw */
    glDrawArrays(GL_POINTS, 0, 1);
    glUseProgram(0);
  } /* End of 'particle::Draw' function */


  VOID emitter::Response( const matr &WorldMatr )
  {
    anim *AC = anim::GetPtr();

    /* Compute delta time */
    static DBL LastTime = AC->Time;
    DBL DeltaTime = AC->Time - LastTime;
    LastTime = AC->Time;

    /* Self response */
    if (!IsImmortal)
      Age += DeltaTime;

    if (AC->Time - LastTimeEmit > DeltaTimeEmit)
    {
      LastTimeEmit = AC->Time;
      for (INT i = 0; i < NumOfParticles; ++i)
        EmitParticle(Matr * WorldMatr);
    }

    /* Response particles */
    for (INT i = 0; i < Particles.size(); ++i)
    {
      ResponseParticle(Particles[i], DeltaTime);
      if ((Particles[i])->Age >= (Particles[i])->AgeDie)
      {
        delete Particles[i];
        Particles.erase(Particles.begin() + i);
        i--;
      }
    }
  }

  /* Draw particles function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID emitter::Draw( VOID )
  {
    for (auto it = Particles.begin(); it != Particles.end(); ++it)
      (*it)->Draw();
  } /* End of 'emitter::Draw' function */

  /* Water drop emmiter function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */
  VOID emitterWaterDrop::Init( const BOOL InIsImmortal, const DBL InDeltaTimeEmit,
    const INT InNumOfParticles, const DBL InDieAge)
  {
    anim *AC = anim::GetPtr();
    IsImmortal = InIsImmortal;
    DeltaTimeEmit = InDeltaTimeEmit;
    DieAge = InDieAge;
    NumOfParticles = InNumOfParticles;
    Shader = AC->ShaderCreate("SRC/BIN/SHADER/PARTICLES/");
    Texture = AC->TextureCreate("", "SRC/BIN/TEXTURES/waterdrop.bmp");
  } /* End of 'emitterWaterDrop::Init' function */

  /* Emit particle function. 
   * ARGUMENTS: None.
   * RETURNS None.
   */
  VOID emitterWaterDrop::EmitParticle( const matr &WorldMatr )
  {
    anim *AC = anim::GetPtr();
    particle *Prt;
    vec3 V(0);
    V.Rnd1();
    V[2] = fabs(V[1]);

    Prt = new particle(3, Shader, Texture, WorldMatr);
    Prt->Trans.Init(FALSE, 1, -1.5, 0, 0, -0.23);
    Prt->Size.Init(FALSE, 0.5, -0.5, 0, 0, -0.13);
    Prt->Position.Init(FALSE, vec3(0), 0, 20, V * 10, vec3(0, 0, 50));

    Particles.push_back(Prt);
  } /* End of 'emitterWaterDrop::EmitParticle' function */

  /* Response particle function.
   * ARGUMENTS:
   *   - particle for response:
   *       particle *Prt;
   * RETURNS: None.
   */
  VOID emitterWaterDrop::ResponseParticle( particle *Prt, const DBL DeltaTime )
  {
    Prt->Age += DeltaTime;
    Prt->Trans.Compute();
    Prt->Size.Compute();
    Prt->Position.Compute();

    /*
    Prt->Trans.Compute();
    Prt->Rotation.Compute();
    Prt->Position.Compute();
    */
  } /* End of 'emitterWaterDrop::ResponseParticle'*/

} /* end of 'digl' namespace */

/* END OF 'geom.cpp' FILE */


