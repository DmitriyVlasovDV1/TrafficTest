/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : res.h
 * PURPOSE     : Animation system project.
 *             : Render system implementation module.
 *             : Main class declaration file.
 * PROGRAMMER  : Vlasov Dmitriy.
 * LAST UPDATE : 27.07.2020
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support of 30 Phys-Math Lyceum.
 */

#ifndef __RES_H_
#define __RES_H_

#include "../../def.h"
#include "../../stock.h"
#include "prim.h"
#include "resources/shader.h"
#include "resources/fonts.h"
#include "../../UTILS/geom.h"

/* Animation project namnespace */
namespace digl
{
  /* Manager type */
  template<class Type>
    class manager
    {
    public: ////////////////////////////////////////////
      stock<Type*> Stock;

      /* Manager constructor.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      manager( VOID ) : Stock()
      {
      } /* End of 'manager' function */

      /* Destructor */
      ~manager( VOID )
      {
        for (auto el : Stock)
          delete el;
      } /* End of '~manager' function */

      /* Add element to stock function.
       * ARGUMENTS:
       *   - element for adding:
       *       const Type &Element;
       * RETURNS: None.
       */
      VOID Add( Type *Element )
      {
        Stock << Element; 
      } /* End of 'Add' function */

      /* Delete element to stock function.
       * ARGUMENTS:
       *   - element name for delete:
       *       const std::string Name;
       * RETURNS: None.
       */
      VOID Del( const std::string &Name )
      {
        delete Find(Name);
      } /* End of 'Del' function */

      /* Find element in stock function.
       * ARGUMENTS:
       *   - element name for searching:
       *       const std::string Name;
       * RETURNS:
       *   (Type &) Reference to element.
       */
      Type * Find( const std::string &Name )
      {
        for (auto Element : Stock)
          if (Element->Name == Name)
            return Element;
        return nullptr;
      } /* End of 'Find' function */

    }; /* End of 'manager' class */

  /* Primitive manager type */
  class manager_prims : public manager<primitives::primitives>
  {
  public:
    /* Primitive manager constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    manager_prims( VOID ) : manager()
    {
    } /* End of 'manager_prim' function */

    /* Create primitive function
     * ARGUMENTS: None.
     * RETURNS:
     *  (primitives::prim &) New primitive.
     */
    primitives::primitives* PrimsCreate( VOID )
    {
      primitives::primitives* Prs;
      Add(Prs = new primitives::primitives());
      return Prs;
    } /* End of 'PrimCreate' function */

    /* Create primitive function
     * ARGUMENTS: None.
     * RETURNS:
     *  (primitives::prim &) New primitive.
     */
    primitives::primitives* PrimsLoad( const CHAR *FileName, shader *Shd, const matr& LoadTransfrom = matr::Identity())
    {
      primitives::primitives *Prs;

      Add( Prs = new primitives::primitives(FileName, Shd, LoadTransfrom) );
      return Prs;
    } /* End of 'PrimCreate' function */
  }; /* End of 'manager_prims' class */ 


  /* Primitive manager type */
  class manager_prim : public manager<primitives::prim>
  {
  public:
    /* Primitive manager constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    manager_prim(VOID) : manager()
    {
    } /* End of 'manager_prim' function */

    /* Create primitive function
     * ARGUMENTS: None.
     * RETURNS:
     *  (primitives::prim &) New primitive.
     */
    template<class vertex_type>
      primitives::prim* PrimCreate( const topology::base<vertex_type>& Topo )
      {
        primitives::prim* Pr;
        Add(Pr = new primitives::prim(Topo));
        return Pr;
      } /* End of 'PrimCreate' function */

    /* Create primitive function
     * ARGUMENTS: None.
     * RETURNS:
     *  (primitives::prim &) New primitive.
     */
    primitives::prim* PrimLoad(const std::string& FileName)
    {
      primitives::prim* Pr;
      topology::trimesh<vertex::std> Topo;
      Topo.LoadFile(FileName);

      Add(Pr = new primitives::prim(Topo));
      return Pr;
    } /* End of 'PrimCreate' function */

  }; /* End of 'manager_prim' class */


  /* Shader manager type */
  class manager_shader : public manager<shader>
  {
  public:
    /* Shader manager constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    manager_shader( VOID ) : manager()
    {
    } /* End of 'manager_shader' function */

    /* Create shader function.
     * ARGUMENTS: None.
     * RETURNS:
     *  (shader &) New shader.
     */
    shader * ShaderCreate( const std::string &FileNamePrefix )
    {
      shader *Sh;
      Add( Sh = new shader(FileNamePrefix) );
      return Sh;
    } /* End of 'ShaderCreate' function */

  }; /* End of 'shader_prim' class */ 

  /* Material manager type */
  class manager_material : public manager<material>
  {
  public:
    /* Material manager constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    manager_material( VOID ) : manager()
    {
    } /* End of 'manager_material' function */

    /* Create material function.
     * ARGUMENTS: None.
     * RETURNS:
     *  (shader &) New shader.
     */
    material * MaterialCreate( shader *Shader = nullptr, const vec3 &Ka = vec3(1), const vec3 &Kd = vec3(1), 
                               const vec3 &Ks = vec3(1), const FLT Ph = 1, const FLT Trans = 1 )
    {
      material *Mtl;
      Add( Mtl = new material(Shader, Ka, Kd, Ks, Ph, Trans) );
      return Mtl;
    } /* End of 'ShaderCreate' function */

    /* Create material function.
     * ARGUMENTS: None.
     * RETURNS:
     *  (shader &) New shader.
     */
    material * MaterialCreate( const material &InMtl )
    {
      material *Mtl;
      Add( Mtl = new material(InMtl) );
      return Mtl;
    } /* End of 'ShaderCreate' function */


  }; /* End of 'manager_prim' class */ 

  /* Texture manager type */
  class manager_texture : public manager<texture>
  {
  public:
    /* Texture manager constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    manager_texture( VOID ) : manager()
    {
    } /* End of 'manager_texture' function */


    /* Create texture function.
     * ARGUMENTS: None.
     * RETURNS:
     *  (texture &) New texture.
     */
    texture * TextureCreate()
    {
      texture *Tex;
      Add( Tex = new texture() );
      return Tex;
    } /* End of 'TextureCreate' function */

    /* Create texture function.
     * ARGUMENTS:
     *   - width, height:
     *       const INT InW, InH;
     *   - format:
     *       const INT Format;
     *   - name:
     *       const std::string &InName;
     * RETURNS:
     *  (texture &) New texture.
     */
    texture * TextureCreate( const INT InW, const INT InH, const INT Format, const std::string &InName = "" )
    {
      texture *Tex;
      Add( Tex = new texture(InW, InH, Format, InName) );
      return Tex;
    } /* End of 'TextureCreate' function */

    /* Create texture function.
     * ARGUMENTS: None.
     * RETURNS:
     *  (rexture &) New texture.
     */
    texture * TextureCreate( const std::string &InName, const std::string &FileName )
    {
      texture *Tex;
      Add( Tex = new texture(InName, FileName) );
      return Tex;
    } /* End of 'TextureCreate' function */

    /* Create texture function.
     * ARGUMENTS: None.
     * RETURNS:
     *  (rexture &) New texture.
     */
    texture * TextureCreate( const std::string &InName, const INT InW, const INT InH, const DWORD *Img )
    {
      texture *Tex;
      Add( Tex = new texture(InName, InW, InH, Img) );
      return Tex;
    } /* End of 'TextureCreate' function */

    /* Create texture function.
     * ARGUMENTS: None.
     * RETURNS:
     *  (rexture &) New texture.
     */
    texture * TextureCreate( const std::string &InName, const INT InW, const INT InH, const BYTE *Img )
    {
      texture *Tex;
      Add( Tex = new texture(InName, InW, InH, Img) );
      return Tex;
    } /* End of 'TextureCreate' function */

  }; /* End of 'manager_texture' class */ 

  /* Font manager type */
  class manager_font : public manager<font>
  {
  public:
    /* Texture manager constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    manager_font( VOID ) : manager()
    {
    } /* End of 'manager_texture' function */

    /* Create texture function.
     * ARGUMENTS: None.
     * RETURNS:
     *  (rexture &) New texture.
     */
    font * FontCreate( const std::string &FileName )
    {
      font *Fnt;
      Add( Fnt = new font(FileName) );
      return Fnt;
    } /* End of 'FontCreate' function */
  }; /* End of 'manager_font' class */

  /* Geometry manager type */
  class manager_geom : public manager<geom>
  {
  public:
    /* Geometry manager constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    manager_geom( VOID ) : manager()
    {
    } /* End of 'manager_geom' function */

    /* Create geometry function.
     * ARGUMENTS: None.
     * RETURNS:
     *  (geom *) New geometry.
     */
    geom * GeomCreate( VOID )
    {
      geom* Geom;
      Add(Geom = new geom());
      return Geom;
    } /* End of 'GeomCreate' function */
  }; /* End of 'manager_geom' class */

  /* Geometry manager type */
  class manager_emitter : public manager<emitter>
  {
  public:
    /* Emitter manager constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    manager_emitter( VOID ) : manager()
    {
    } /* End of 'manager_emitter' function */

    /* Create emitter function.
     * ARGUMENTS: None.
     * RETURNS:
     *  (emitter *) New emitter.
     */
  template<class EmitterType>
    EmitterType * EmitterCreate( VOID )
    {
      EmitterType *Emitter;
      Add(Emitter = new EmitterType());
      return Emitter;
    } /* End of 'EmitterCreate' function */
  }; /* End of 'manager_emitter' class */

} /* end of 'digl' namespace */


#endif /* __RES_H_ */
