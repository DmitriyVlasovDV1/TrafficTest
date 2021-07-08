/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : main.cpp
 * PURPOSE     : Main file.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 20.08.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */

/* Includes */
#include "def.h"
#include "anim\anim.h"

/* Animation project namespace */
using namespace digl;

/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) error level for operation system (0 for success).
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    CHAR *CmdLine, INT ShowCmd )
{
  digl::units::scene Scene;

  Scene << "Control";
  Scene << "Info";
  Scene << "Game";
  Scene << "Ground";
  //Scene << "Uaz";
  
  //Scene << "Skybox";
  anim::Get().SetScene(&Scene).Run();
} /* End of 'WinMain' function */

/* END OF 'main.cpp' */
