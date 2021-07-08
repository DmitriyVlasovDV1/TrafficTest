/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : main.cpp
 * PURPOSE     : main file.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 28.07.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */


#ifndef __MATERIAL_H_
#define __MATERIAL_H_

#include "../../../def.h"

#include "shader.h"
#include "texture.h"
#include <vector>

/* Animation project namespace */
namespace digl
{
  /* Material type */
  class material
  {
  public:
    vec3 Ka, Kd, Ks;
    FLT Ph, Trans;

    shader *Shader;
    std::vector<texture*> Textures;

    /* Material constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    material( VOID ) :
      Ka(0), Kd(0), Ks(0), Ph(0), Trans(0), Shader()
    {
    } /* End of 'material' function */

    /* Material constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    material( const material &Mtl )
    {
      this->Ka = Mtl.Ka;
      this->Kd = Mtl.Kd;
      this->Ks = Mtl.Ks;
      this->Ph = Mtl.Ph;
      this->Trans = Mtl.Trans;
      this->Shader = Mtl.Shader;
      memcpy(&this->Textures[0], &Mtl.Textures[0], Mtl.Textures.size() * sizeof(texture));
    } /* End of 'material' function */


    /* Material constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    material( shader *Shader = nullptr, const vec3 &Ka = vec3(1), const vec3 &Kd = vec3(1), 
              const vec3 &Ks = vec3(1), const FLT Ph = 1, const FLT Trans = 1 ) :
      Ka(Ka), Kd(Kd), Ks(Ks), Ph(Ph), Trans(Trans), Shader(Shader)
    {
    } /* End of 'material' function */

    /* Destructor */
    ~material( VOID )
    {
    } /* End of '~material' function */

    /* Apply  material function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (INT) Program id.
     */
    INT Apply( VOID )
    {
      /* Shader */
      if (Shader == nullptr)
        return -1;

      INT prg = Shader->ProgId;
      glUseProgram(prg);

      /* Textures */
      BOOL IsTexture = (Textures.size() != 0);

      for (INT i = 0; i < Textures.size(); i++)
      {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, Textures[i]->TexId);
      }

      /* Uniforms */
      INT loc;
      if ((loc = glGetUniformLocation(prg, "Ka")) != -1)
        glUniform3fv(loc, 1, Ka);
      if ((loc = glGetUniformLocation(prg, "Kd")) != -1)
        glUniform3fv(loc, 1, Kd);
      if ((loc = glGetUniformLocation(prg, "Ks")) != -1)
        glUniform3fv(loc, 1, Ks);
      if ((loc = glGetUniformLocation(prg, "Ph")) != -1)
        glUniform1f(loc, Ph);
      if ((loc = glGetUniformLocation(prg, "Trans")) != -1)
        glUniform1f(loc, Trans);
      if ((loc = glGetUniformLocation(prg, "IsTexture")) != -1)
        glUniform1i(loc, IsTexture);

      return prg;
    } /* End of 'Apply' function */

    /* Set coefficients function.
     * ARGUMENTS:
     *   - vector coefficients:
     *       (const vec3 &) NewKa, NewKd, NewKs;
     *   - scalar coefficients:
     *       (const FLT) NewPh, NewTrans;
     * RETURNS: None.
     */
    VOID SetCoefs( const vec3 &NewKa, const vec3 &NewKd, 
                  const vec3 &NewKs, const FLT NewPh, const FLT NewTrans)
    {
      Ka = NewKa;
      Kd = NewKd;
      Ks = NewKs;
      Ph = NewPh;
      Trans = NewTrans;
    } /* End of 'SetCoefs' function */
  }; /* End of 'material' class */
}




#endif /* __MATERIAL_H_ */





/* END OF 'material.h' FILE */