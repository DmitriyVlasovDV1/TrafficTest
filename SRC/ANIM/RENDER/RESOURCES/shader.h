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


#ifndef __SHADER_H_
#define __SHADER_H_

#include "../../../def.h"

#include <istream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <fstream>

/* Animation project namespace */
namespace digl
{
  /* Shader type */
  class shader
  {
  private:
    std::string Name;
  public:
    UINT ProgId;

    /* Shader constructor.
     * ARGUMENTS: None.
     * RE
    */
    shader( VOID ) : ProgId(0)
    {
    } /* Endf of 'shader' function */

    /* Shader destructor.
     * ARGUMENTS: None.
     * RE
    */
    ~shader( VOID )
    {
    } /* Endf of '~shader' function */

    /* Shader constructor.
     * ARGUMENTS:
     *   - prefix of shader:
     *       const std::string &FileName;
     * RETURNS: None.
     */
    shader( const std::string &FileNamePrefix )
    {
      ShaderLoad(FileNamePrefix);
    } /* End of 'shader' constructor */

    /* Save text to log file function.
     * ARGUMENTS:
     *    - output text:
     *        const std::string &Text;
     * RETURNS: None.
     */
    static VOID SaveLog( const std::string &Text )
    {
      std::ofstream("{_}SHD{30}.LOG", std::ios_base::app) << Text << std::endl;
    } /* End of 'SaveLog' function */

    /* Load text from file function.
     * ARGUMENTS:
     *   - file name:
     *       const std::string &FileName;
     * RETURNS:
     *   std::string allocated text from file.
     */
    std::string TextLoad( const std::string &FileName )
    {
      std::ifstream f(FileName);
      std::string s((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
      return s;
    } /* End of 'TextLoad' function */


    /* Shader program initialization function
     * ARGUMENTS:
     *    - the prefix of file:
     *        const std::string &FileNamePrefix;
     * RETURNS: None.
     */
    VOID ShaderLoad( const std::string &FileNamePrefix )
    {
      INT res, i, NumShInPrg = 3;
      std::string txt;
      UINT
        Shaders[3] = {0}, Prg = 0,
        ShTypes[3] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER};
      const std::string Suff[3] = 
        {
        "vert",
        "frag",
        "geom"
        };
      BOOL isok = TRUE;
      static CHAR Buf[1000];

      for (i = 0; i < 3; i++)
      {
        std::string fname = FileNamePrefix + Suff[i] + ".glsl";
        if ((Shaders[i] = glCreateShader(ShTypes[i])) == 0)
        {
          isok = FALSE;
          SaveLog("Error create shader <" + Suff[i] + ">");
          break;
        }

        try
        {
          txt = TextLoad(fname);
          if (txt == "")
            NumShInPrg -= 1;
        }
        catch (...)
        {
          isok = FALSE;
          SaveLog("Error load file: ");
          SaveLog(Buf);
          break;
        }

        const CHAR *txtptr = txt.c_str();
        glShaderSource(Shaders[i], 1, &txtptr, NULL);
        glCompileShader(Shaders[i]);
        glGetShaderiv(Shaders[i], GL_COMPILE_STATUS, &res);
        if (res != 1)
        {
          glGetShaderInfoLog(Shaders[i], sizeof(Buf), &res, Buf);
          SaveLog("Error file '" + fname + "' " + "compile error:" + Buf);
          isok = FALSE;
          break;
        }
      }

      if (isok)
        if ((Prg = glCreateProgram()) == 0)
          isok = FALSE;
        else
        {
          for (i = 0; i < NumShInPrg; i++)
            if (Shaders[i] != 0)
              glAttachShader(Prg, Shaders[i]);
          glLinkProgram(Prg);
          glGetProgramiv(Prg, GL_LINK_STATUS, &res);
          if (res != 1)
          {
            glGetProgramInfoLog(Prg, sizeof(Buf), &res, Buf);
            SaveLog(Buf);
            SaveLog("Error files '" + FileNamePrefix + "' " + "link error:" + Buf);
            isok = FALSE;
          }
        }
      if (!isok)
      {
        for (i = 0; i < NumShInPrg; i++)
          if (Shaders[i] != 0)
          {
            if (Prg != 0)
              glDetachShader(Prg, Shaders[i]);
            glDeleteShader(Shaders[i]);
          }
        if (Prg != 0)
          glDeleteProgram(Prg);
        ProgId = 0;
      }

      ProgId = Prg;
      Name = FileNamePrefix;
    } /* End of 'ShaderLoad' function */

    /* Shader program deinitialization function
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID ShaderFree( VOID )
    {
      UINT i, n, shdrs[5];

      if (ProgId == 0)
        return;

      glGetAttachedShaders(ProgId, 5, (GLsizei *)&n, shdrs);

      for (i = 0; i < n; i++)
      {
        glDetachShader(ProgId, shdrs[i]);
        glDeleteShader(shdrs[i]);
      }
      glDeleteProgram(ProgId);
    } /* End of 'vigl::shader::ShaderFree' function */

    /* Reload shader program function
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Reload( VOID )
    {
      ShaderFree();
      ShaderLoad(Name);
    } /* End of 'digl::shader::Reload' function */
  }; /* End of 'shader' class */
} /* end of 'digl' namespace */

#endif