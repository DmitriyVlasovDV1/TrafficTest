/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : prim.h
 * PURPOSE     : primitives header file.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 25.07.2020
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */


#ifndef __PRIM_H_
#define __PRIM_H_

#include "resources/topology.h"
#include "resources/material.h" 
#include "resources/texture.h"
#include <map>
#include <vector>

#include "../../def.h"

/* Animation project namespace */
namespace digl
{
  class anim;
  /* Primitives namespace */
  namespace primitives
  {

    /* Primitive class */
    class prim
    {
    public:
      prim_type Type;
      UINT VA, VBuf, IBuf, NumOfElements;
      matr Transform;
      vec3 Min, Max;
      material *Material;

      /* Primitive constructor.
       * ARGUMENTS: None.
       * RETUNRS: None.
       */
      prim( VOID ): Transform(matr::Identity()), Type(prim_type::TRIMESH),
        VA(0), VBuf(0), IBuf(0), NumOfElements(0), Min(0), Max(0), Material()
      {
      } /* End of 'prim' function */

      /* Primitive constructor.
       * ARGUMENTS:
       *   - topology:
       *       const topology::base<vertex_type> &Topo;
       *   - name:
               const std::string &Name;
       * RETUNRS: None.
       */
    template<class vertex_type>
      prim ( const topology::base<vertex_type> &Topo = topology::base<vertex_type>() ) :
        Transform(matr::Identity()), Type(prim_type::TRIMESH),
        VA(0), VBuf(0), IBuf(0), NumOfElements(0), Min(0), Max(0), Material()
      {
        (*this)(Topo);
      } /* End of 'prim' function */

      /* Set material function.
       * ARGUMENTS:
       *   - material:
       *       material *Mtl;
       * RETUNRS: None.
       */
      VOID SetMaterial( material *Mtl )
      {
        Material = Mtl;
      } /* End of 'SetMaterial' function */

      /* Apply material function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (INT) Shader program id
       */
      INT ApplyMaterial( VOID ) const
      {
        if (Material != nullptr)
          return Material->Apply();
        return -1;
      } /* End of 'ApplyMaterial' function */

      /* Primitive constructor.
       * ARGUMENTS:
       *   - topology:
       *       const topology::base<vertex_type> &Topo;
       * RETUNRS: None.
       */
    template<class vertex_type>
      VOID operator()( const topology::base<vertex_type> &Topo )
      {
        NumOfElements = Topo.Vertex.size() > Topo.Index.size() ? Topo.Vertex.size() : Topo.Index.size();
        Type = Topo.PrimType;

        glGenBuffers(1, &VBuf);
        glGenVertexArrays(1, &VA);
        glBindVertexArray(VA);
        glBindBuffer(GL_ARRAY_BUFFER, VBuf);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_type) * Topo.Vertex.size(), &Topo.Vertex[0], GL_STATIC_DRAW);

        /* Descriptor parser */
        CHAR *ptr = (CHAR *)vertex_type::Descr;
        INT NumComp,
            i = 0,
            Shift = 0;
        while (*ptr != 0)
        {
          if (*ptr++ == 'f')
          {
            NumComp = *ptr++ - '0';
            glVertexAttribPointer(i, NumComp, GL_FLOAT, FALSE, sizeof(vertex_type), (VOID *)Shift);
            glEnableVertexAttribArray(i);
            Shift += sizeof(FLT) * NumComp;
          }
          else if (*ptr++ == 'i')
          {
            NumComp = *ptr++ - '0';
            glVertexAttribPointer(i, NumComp, GL_FLOAT, FALSE, sizeof(vertex_type), (VOID *)Shift);
            glEnableVertexAttribArray(i);
            Shift += sizeof(INT) * NumComp;
          }
          else
            return;
          i++;
        }

        glGenBuffers(1, &IBuf);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * Topo.Index.size(), &Topo.Index[0], GL_STATIC_DRAW);
      } /* End of 'prim' function */

      /* Destructor */
      ~prim()
      {
        glBindVertexArray(VA);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &VBuf);
        glBindVertexArray(0);
        glDeleteVertexArrays(1, &VA);
        glDeleteBuffers(1, &IBuf);
      } /* End of '~prim' function */

    }; /* End of 'prim' class */

    /* Primitives class */
    class primitives
    {
    public:
      stock<prim *> Prims;
      matr Transform;
      vec3 Min, Max;

      /* Primitives constructor function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      primitives ( VOID ) : Transform(matr::Identity()), Min(), Max()
      {
      } /* End of 'primitives' function */

      /* Primitives constructor function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      ~primitives ( VOID )
      {
      } /* End of '~primitives' function */

      /* Primitives constructor function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      primitives ( const CHAR *FileName, shader *Shd, const matr &LoadTransfrom = matr::Identity() ) :
        Transform(matr::Identity())
      {
        LoadG3DM(FileName, Shd, LoadTransfrom);
      } /* End of 'primitives' function */

      /* Add prim in primitives function.
       * ARGUMENTS:
       *   - primitive:
       *       const prim *Pr;
       * RETURNS:
       *   (primitives &) pthis primitives.
       */
      primitives & operator<<( prim *Pr )
      {
        Prims << Pr;
        return *this;
      } /* End of 'operator<<' function */

      /* Load topo from file function.
       * ARGUMENTS:
       *   - file name:
       *       const CHAR *FileName;
       * RETUNRNS: None.
       */
      primitives * LoadG3DM( const CHAR *FileName, shader *Shd, const matr &LoadTransfrom );
   }; /* End of 'primitives' class */
  } /* end of 'primitives' namespace */
} /* end of 'digl' namespace */

#endif /* __PRIM_H_ */



