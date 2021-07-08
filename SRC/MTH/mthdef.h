/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : mthdef.h
 * PURPOSE     : Math definitions.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 20.08.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */

#ifndef __MATHDEF_H_
#define __MATHDEF_H_

/* Includes */
#include "commondf.h"
#include <math.h>

/* Types */
typedef DOUBLE DBL;
typedef FLOAT FLT;

/* Constants */
#define PI 3.141592653589793

/* Define-functions */
#define D2R(A) ((A) / 180 * PI)
#define R2D(A) ((A) / PI * 180)

#endif /* __MATHDEF_H_ */

/* END OF 'mathdef.h' FILE */

