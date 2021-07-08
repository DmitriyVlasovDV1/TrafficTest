/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TIMER.H
 * PURPOSE     : Animation functions.
 * PROGRAMMER  : Vlasiv Dmitriy.
 * LAST UPDATE : 24.07.2020.
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "../def.h"
#include "anim.h"

/* Single tone */
digl::anim digl::anim::Instance;

/* Initialization function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
VOID digl::anim::Init( VOID )
{
} /* End of 'digl::anim::Init' function */

/* Close function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
VOID digl::anim::Close( VOID )
{
} /* End of 'digl::anim::Close' function */

/* Resize function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
VOID digl::anim::Resize( VOID )
{
  render::Resize();
  Render();
} /* End of 'digl::anim::Resize' function */

/* Timer function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
VOID digl::anim::Timer( VOID )
{
  Render();
} /* End of 'digl::anim::Timer' function */

/* Activate function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
VOID digl::anim::Activate( VOID )
{
  Render();
} /* end of 'digl::anim::Activate' function */

/* Idle function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
VOID digl::anim::Idle( VOID )
{
  Render();
} /* End of 'digl::anim::Idle' funcnion */

/* Erase function.
  * ARGUMENTS:
  *   - device context:
  *       HDC hDC;
  * RETURNS: None.
  */
VOID digl::anim::Erase( HDC hDC )
{
  Render();
} /* End of 'digl::anim::Erase' function */

/* Paint function.
  * ARGUMENTS:
  *   - device context:
  *       HDC hDC;
  * RETURNS: None.
  */
VOID digl::anim::Paint( HDC hDC )
{
  Render();
} /* End of 'digl::anim::Paint' function */

/* Render function.
 * ARGUMENTS: None.
 * RETURNS: None. 
 */
VOID digl::anim::Render( VOID )
{
  static DBL timeUpdateShaders = timer::Time;

  /* Responses */
  timer::Response();
  input::Response();
  FPS;

  /* Render */
  if (timer::Time - timeUpdateShaders > 5)
  {
    timeUpdateShaders = timer::Time;
    render::manager_shader::Stock.Walk([this]( shader *Sh )
      {
        Sh->Reload();
      });

  }

  render::FrameStart();

  render::pipeline::Start();
  if (Scene != nullptr)
  {
    (dynamic_cast<units::scene *>(Scene))->Response(this);
    (dynamic_cast<units::scene *>(Scene))->Render(this);
  }
  render::pipeline::End();
 
  render::FrameEnd();
  render::FrameCopy();

} /* End of 'Render' function */

/* Set scene function.
  * ARGUMENTS:
  *   - new scene:
  *       unit *NewScene
  * RETURNS:
  *   (anim &) this animation.
  */
digl::anim & digl::anim::SetScene( digl::units::unit *NewScene )
{
  Scene = NewScene;
  return *this;
} /* */

/* Get anim instance function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (anim &) Animation instance.
 */
digl::anim & digl::anim::Get( VOID )
{
  return Instance;
} /* End of 'Get' function */

/* Get anim instance function.
  * ARGUMENTS: None.
  * RETURNS:
  *   (anim &) Animation instance.
  */
digl::anim * digl::anim::GetPtr( VOID )
{
  return &Instance;
} /* End of 'GetPtr' function */

/* Add element to scene function.
 * ARGUMENTS:
 *   - unit for add:
 *       units::unit *Uni;
 * RETUNRNS:
 *   (scene &) this scene.
 */
digl::units::scene & digl::units::scene::operator<<( digl::units::unit *Uni )
{
  Units << Uni;
  return *this;
} /* End of 'operator<<' function */

/* Add element to scene function.
 * ARGUMENTS:
 *   - name unit for add:
 *       const std::string &Name;
 * RETUNRNS:
 *   (scene &) this scene.
 */
digl::units::scene & digl::units::scene::operator<<( const std::string &Name )
{
  anim &Ani = anim::Get();

  if (Ani.UnitNames.find(Name) != Ani.UnitNames.end())
  {
    unit *uni = Ani.UnitNames[Name]();

    return *this << uni;
  }
  return *this;
} /* End of 'operator<<' function */

/* END OF 'anim.cpp' FILE */
