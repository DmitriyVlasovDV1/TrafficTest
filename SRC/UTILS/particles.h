/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : particles.h
 * PURPOSE     : particles utils headerfile.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 10.09.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */

#ifndef __PARTICLES_H_
#define __PARTICLES_H_

/* Includes */
#include "../def.h"
#include "physics.h"
#include "../ANIM/RENDER/RESOURCES/shader.h"
#include "../ANIM/RENDER/RESOURCES/texture.h"
#include <vector>

/* Animation project namespace */
namespace digl
{
  /* Particles emitter representation class */
  class particle
  {
  public:
    DBL Age;
    DBL AgeDie;
    shader *Shader;
    texture *Texture;
    kinematics Size;
    kinematics Trans;
    kinematics Rotation;
    kinematicsVec Position;
    matr Matr;

    /* Emitter constructor function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    particle( VOID ) :
      Age(0), AgeDie(0), Shader(), Texture(), Size(),
      Trans(), Rotation(), Position(), Matr(matr::Identity())
    {
    } /* End of 'particle' function */

    /* Emitter constructor function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    particle( const FLT InAgeDie, shader *InShader,
      texture *InTexture, const matr InMatr = matr::Identity() ) :
      Age(0), AgeDie(InAgeDie), Shader(InShader), Texture(InTexture), Size(),
      Trans(), Rotation(), Position(), Matr(InMatr)
    {
    } /* End of 'particle' function */

    ~particle( VOID )
    {
    } /* End of '~particle' function */

    /* Draw particle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Draw( VOID );

  }; /* End of 'emitter' function */


  /* Particles emitter representation class */
  class emitter
  {
  protected:
    std::vector<particle *> Particles;
    shader *Shader;
    texture *Texture;

  public:
    DBL Age,
        DieAge,
        DeltaTimeEmit,
        LastTimeEmit;
    INT NumOfParticles;
    BOOL IsImmortal;
    matr Matr;

    /* Emitter constructor function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    emitter( VOID ) : Age(0), DieAge(0), NumOfParticles(0), DeltaTimeEmit(0),
      LastTimeEmit(0), IsImmortal(FALSE), Matr(matr::Identity()), Shader(nullptr),
      Texture(nullptr)
    {
    } /* End of 'emitter' function */

    /* Emitter constructor function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    emitter( const BOOL InIsImmortal, const DBL InDeltaTimeEmit, const INT InNumOfParticles, const DBL InDieAge = 0 ) :
      Age(0), NumOfParticles(InNumOfParticles), DieAge(InDieAge), LastTimeEmit(0), DeltaTimeEmit(InDeltaTimeEmit),
      IsImmortal(InIsImmortal), Matr(matr::Identity()), Shader(nullptr), Texture(nullptr)
    {
    } /* End of 'emitter' function */

    /* Emitter constructor function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    ~emitter( VOID )
    {
      for (auto it = Particles.begin(); it != Particles.end(); ++it)
        delete *it;
    } /* End of '~emitter' function */

    /* Emmiter initialization function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */
    virtual VOID Init(const BOOL InIsImmortal, const DBL InDeltaTimeEmit,
      const INT InNumOfParticles, const DBL InDieAge = 0)
    {
    } /* End of 'Init' function */

    /* Emit particle function. 
     * ARGUMENTS: None.
     * RETURNS None.
     */
    virtual VOID EmitParticle( const matr &WorldMatr = matr::Identity() )
    {
    } /* End of 'EmitParticle' function */

    /* Response particle function.
     * ARGUMENTS:
     *   - particle for response:
     *       particle *Prt;
     * RETURNS: None.
     */
    virtual VOID ResponseParticle( particle *Prt, const DBL DeltaTime )
    {
    } /* End of 'ResponseParticle'*/

    VOID Response( const matr &WorldMatr = matr::Identity() );

    VOID Draw( VOID );
  }; /* End of 'emitter' class */

  /* Water splash emitter representation type */
  class emitterWaterDrop : public emitter
  {
  public:
    /* Water drop emitter constructor function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    emitterWaterDrop( VOID ) : emitter()
    {
    } /* End of 'emitterWaterDrop' function */

    /* Water drop emitter constructor function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    emitterWaterDrop( const BOOL InIsImmortal, const DBL InDeltaTimeEmit, const INT InNumOfParticles,
      const DBL InDieAge = 0) : emitter(InIsImmortal, InDeltaTimeEmit, InNumOfParticles, InDieAge)
    {
    } /* End of 'emitterWaterDrop' function */

    /* Water drop emmiter function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Init(const BOOL InIsImmortal, const DBL InDeltaTimeEmit,
      const INT InNumOfParticles, const DBL InDieAge = 0) override;

    /* Emit particle function. 
     * ARGUMENTS: None.
     * RETURNS None.
     */
    VOID EmitParticle( const matr &WorldMatr = matr::Identity() ) override;

    /* Response particle function.
     * ARGUMENTS:
     *   - particle for response:
     *       particle *Prt;
     * RETURNS: None.
     */
    VOID ResponseParticle( particle *Prt, const DBL DeltaTime ) override;
  }; /* end of 'emitterWaterDrop' class */

} /* end of 'digl' namespace */

#endif /* __GEOM_H_ */

/* END OF 'geom.h' FILE */



