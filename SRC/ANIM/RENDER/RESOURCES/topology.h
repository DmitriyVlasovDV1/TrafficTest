/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : render.h
 * PURPOSE     : render header file.
 * PROGRAMMER  : Dmitriy Vlasov.
 * LAST UPDATE : 25.07.2020
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium.
 */


#ifndef __TOPOLOGY_H_
#define __TOPOLOGY_H_

#include "../../../def.h"
#include "../../../stock.h"

/* Animation project namespace */
namespace digl
{
  /* Primitive representation type */
  enum struct prim_type
  {
    TRIMESH,
    STRIP
    //...
  }; /* End of 'prim_type' enum struct */


  /* Vertex namespace */
  namespace vertex
  {
    /* Standard class */ 
    class std
    {
    public:
      vec3 P;
      vec2 T;
      vec3 N;
      vec4 C;
      static const char *Descr;

      /* Vertex constructor.
       * ARGUMENTS: None.
       * RETURNS: None. 
       */
      std (const vec3 &P = vec3(0), const vec2 &T = vec2(0), const vec3 &N = vec3(0), const vec4 &C = vec4(1)) : 
        P(P), T(T), N(N), C(C)
      {
      } /* End of 'std' function */
    }; /* End of 'std' class */
  } /* end of 'vertex' namespace */


  /* Topology namespace */
  namespace topology
  {
    /* Base topology class */
    template<class VertexType>
      class base
      {
      public:
        prim_type PrimType = prim_type::TRIMESH;
        stock<VertexType> Vertex;
        stock<INT> Index;

        /* Topology constructor.
         * ARGUMENTS: None.
         * RETURNS: None.
         */
        base( VOID ) : Vertex(), Index(), PrimType(prim_type::TRIMESH)
        {
        } /* End of 'base' function */

        /* Topology constructor.
         * ARGUMENTS: /////////////////////////////None.
         * RETURNS: None.
         */
        base( prim_type NewPrimType, const stock<VertexType> &V = {}, const stock<INT> &I = {} ) :
          PrimType(NewPrimType), Vertex(V), Index(I)
        {
        } /* End of 'base' constructor */
#if 0
        /* Load topo from file function .
         * ARGUMENTS:
         *   - file name:
         *       const CHAR *FileName;
         * RETUNRNS: None.
         */
        BOOL LoadFileG3DM( const std::string FileName )
        {
          FILE *F;
          INT flen, NoofP, NoofM, p, m, t, first_mtl_no, first_tex_no;
          DWORD Sign;
          BYTE *mem, *ptr;
          prim *Pr;

          /* Load file */
          if ((F = fopen(FileName, "rb")) == nullptr)
            return FALSE;

          /* Get file length */
          fseek(F, 0, SEEK_END);
          flen = ftell(F);
          rewind(F);

          /* Allocate memory */
          if ((mem = new BYTE(flen)) == nullptr)
          {
            fclose(F);
            return;
          }

          /* Read data */
          fread(mem, 1, flen, F);
          fclose(F);

          ptr = mem;
          Sign = *(DWORD *)ptr;
          ptr += 4;

          if (Sign != *(DWORD *)"G3DM")
          {
            return FALSE;
          }

          NoofP = *(INT *)ptr;
          ptr +=  4;
          NoofI = *(INT *)ptr;
          ptr +=  4;
          NoofT = *(INT *)ptr;
          ptr +=  4;

          if (/* check and create prims */)
          {
            free(mem);
            return FALSE;
          }

          for (p = 0; p < NoofP; p++)
          {
            INT i;

            INT NoofV, NoofI, MtlNo;

            NoofV = *(INT *)ptr;
            ptr += 4;
            NoofI = *(INT *)ptr;
            ptr += 4;
            MtlNo = *(INT *)ptr;
            ptr += 4;

            Vertex << (type *)ptr;
            ptr += sizeof(type) * NoofV;
            I = (INT *)ptr;
            ptr += sizeof(INT) * NoofI;

            PrimCreate(&Prs->Prim[p],,TRIMESH), V, NoofV, I, NoofM);
            Prs->Prims[p].MtlNo = MtlNo;
          }

          first_mt_no = RndMaterilaSize;

          for (INT m = 0; m < NoofM; m++)
          {
            MtlAdd((material *)ptr);
            ptr += sizof(material);
          }

          for (p = 0; p < NoofP; p++)
            Prs->Prims[P].MtlNo += first_mtl_no;

          first_tex_no = TextureSize;

          for (t = 0; t < NoofT; t++)
          {
            *Tex = (tex*)ptr;

            ptr += sizeof(TExture);

            ADDImage(tex->Name, tex->W, tex->H, (DWORD *)ptr);
            ptr += 4 * tex->W * tex->H;
          }


          for (m = 0; m < NoofM; m++)
          {
            INT i;
            MATERIAL *mtl = RndMaterials[first_mtl_no + m];

            for (i = 0; i < 8; i++)
              if (mtl->Tex[i] != -1)
                mtl->Tex[i] += first_tex_no;
          }

          free(mem);

          return TRUE;
        } /* End of 'LoadFile' function */
#endif



      }; /* End of 'base' class */

    /* Trimesh topology class */
    template<class VertexType>
      class trimesh : public base<VertexType>
      {
      public:
        
        /* Topology constructor. 
         * ARGUMENTS: None.
         * RETURNS: None.
         */
        trimesh( VOID ) : base<VertexType>(prim_type::TRIMESH)
        {
        } /* End of 'trimesh' function */

        /* Load topo from file function .
         * ARGUMENTS:
         *   - file name:
         *       const CHAR *FileName;
         * RETUNRNS: None.
         */
        BOOL LoadFile( const std::string FileName )
        {
          FILE *F;
          CHAR Buf[1000];

          if ((F = fopen(FileName.c_str(), "r")) == NULL )
            return FALSE;

          while (fgets(Buf, sizeof(Buf), F) != NULL)
            if (Buf[0] == 'v' && Buf[1] == ' ')
            {
              DBL x, y, z;

              sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
              this->Vertex << vertex::std(vec3(x, y, z));
            }
            else if (Buf[0] == 'f' && Buf[1] == ' ')
            {
              INT n1, n2, n3;

              const CHAR *f1 = "%d %d %d",
                         *f2 = "%d/%*d %d/%*d %d/%*d",
                         *f3 = "%d//%*d %d//%*d %d//%*d",
                         *f4 = "%d/%*d/%*d%d/%*d/%*d%d/%*d/%*d";

              sscanf(Buf + 2, f4, &n1, &n2, &n3) == 3 ||
                sscanf(Buf + 2, f3, &n1, &n2, &n3) == 3 ||
                sscanf(Buf + 2, f2, &n1, &n2, &n3) == 3 ||
                sscanf(Buf + 2, f1, &n1, &n2, &n3) == 3;

              this->Index << n1 - 1;
              this->Index << n2 - 1;
              this->Index << n3 - 1;
            }
          fclose(F);
          return TRUE;
        } /* End of 'LoadFile' function */

      }; /* End of 'trimesh' class */

    /* Grid topology class */
    template<class VertexType>
      class grid : public base<VertexType>
      {
      protected:
        INT W, H;

      public:
        /* Grid constructor.
         * ARGUMENTS: None.
         * RETURNS: None.
         */
        grid ( VOID ) : base<VertexType>(prim_type::STRIP), W(0), H(0)
        {
        } /*End of '~grid' function */

        /* Grid constructor.
         * ARGUMENTS:
         *   - size:
         *       (const INT &)W, H;
         * RETURNS: None.
         */
        grid( const INT &W, const INT &H ) : base<VertexType>(prim_type::STRIP), W(W), H(H)
        {
          this->Vertex.resize(W * H);
          for (INT i = 0, v = 0; i < H - 1; i++)
          {
            for (INT j = 0; j < W; j++)
            {
              this->Index << v + W;
              this->Index << v++;
            }
            if (i < H - 2)
              this->Index << -1;
          } /* End of 'grid' function */
        } /* End of 'grid' functiuon */

        /* Operator[] function
         * ARGUMENTS:
         *   - grid row.
         * RETURNS:
         *  (VertexType *) Row value.
         */
        VertexType * operator[]( INT Row )
        {
          return &(this->Vertex[Row * W]);
        } /* End of 'operator[]' function */

        /* Grid constructor.
         * ARGUMENTS: None.
         * RETURNS: None.
         */
        VOID EvalNormals( VOID )
        {
          this->Vertex.Walk( []( VertexType &V )
            {
              V.N = vec3(0, 0, 0);
            }
          );

          for (INT i = 0; i < H - 1; i++)
            for (INT j = 0; j < W - 1; j++)
            {
              VertexType V00 = (*this)[i][j],
                         V01 = (*this)[i][j + 1],
                         V10 = (*this)[i + 1][j],
                         V11 = (*this)[i + 1][j + 1];

              vec3 N;
              N = ( (V00.P - V10.P) % (V11.P - V10.P) ).Normalizing();
              V00.N += N;
              V10.N += N;
              V11.N += N;

              N = ( (V11.P - V01.P) % (V00.P - V01.P) ).Normalizing();
              V00.N += N;
              V01.N += N;
              V11.N += N;
            }

          this->Vertex.Walk( []( VertexType &V )
            {
              V.N.Normalize();
            }
          );
        } /* End of 'EvalNormals' function */
      }; /* End of 'grid' class */

    /* Sphere topology type */
    template<class VertexType>
      class sphere : public grid<VertexType>
      {
      public:
        /* Sphere constructor
         * ARGUMENTS: None.
         * RETURNS: None.
         */
        sphere( VOID ) : grid<VertexType>()
        {
        } /* End of 'sphere' function */

        /* Sphere constructor
         * ARGUMENTS:
         *   - radius:
         *       FLT R;
         *   - separations:
         *       FLT W, H;
         * RETURNS: None.
         */
        sphere( const FLT R, const FLT W, const FLT H ) : grid<VertexType>(W, H)
        {
          INT ind = 0;
          for (INT i = 0; i < H; i++)
          {
            DBL theta = (H - 1 - i) / (H - 1) * PI,
                sit = sin(theta), cot = cos(theta);

            for (INT j = 0; j < W; j++)
            {
              DBL
                phi = j / (W - 1) * 2 * PI,
                sip = sin(phi), cop = cos(phi);

              FLT x = sit * sip;
              FLT y = cot;
              FLT z = sit * cop;

              vertex::std V(
                vec3(x, y, z),
                vec2(0, 0),
                vec3(x, y, z).Normalize(),
                vec4(1)
              );

              this->Vertex[ind++] = V;
            }
          }
        } /* End of 'sphere' function */
      }; /* End of 'sphere' class */

    /* Cube topology type */
    template<class VertexType>
      class cube : public grid<VertexType>
      {
      public:
        /* Cube constructor
         * ARGUMENTS: None.
         * RETURNS: None.
         */
        cube( VOID ) : grid<VertexType>()
        {
        } /* End of 'cube' function */

        /* Cube constructor.
         * ARGUMENTS:
         *   - side length:
         *       FLT A;
         *   - separations:
         *       FLT W, H;
         * RETURNS: None.
         */
        cube( const FLT LenX, const FLT LenY, const FLT LenZ, const FLT Frag ) : 
          grid<VertexType>()
        {
          FLT i, j, fb;
          INT xyz, v, ind = 0, shift;
          this->Vertex.resize(Frag * Frag * 6);
          for (INT side = 0; side < 6; side++)
          {
            /* Indexes */
            shift = side * Frag * Frag;
            for (i = 0, v = 0; i < Frag - 1; i++)
            {
              for (j = 0; j < Frag; j++)
              {
                this->Index << shift + v + Frag;
                this->Index << shift + v++;
              }
              this->Index << -1;
            }
            /* Vertecies */
            xyz = side / 2;
            fb = (side % 2) * 2 - 1;
            for (i = 0; i < Frag; i++)
              for (j = 0; j < Frag; j++)
              {
                vec3 pos;
                vec2 tex;
                vec3 norm;

                switch (xyz)
                {
                case 0:
                  pos = vec3(LenX * fb * 0.5, LenY * (i / (Frag - 1) - 0.5), LenZ * (j / (Frag - 1) - 0.5));
                  tex = vec2(i / Frag, j / Frag);
                  norm = vec3(fb, 0, 0);
                  break;
                case 1:
                  pos = vec3(LenX * (i / (Frag - 1) - 0.5), LenY * fb * 0.5, LenZ * (j / (Frag - 1) - 0.5));
                  tex = vec2(i / (Frag - 1), j / (Frag - 1));
                  norm = vec3(0, fb, 0);
                  break;
                case 2:
                  pos = vec3(LenX * (i / (Frag - 1) - 0.5), LenY * (j / (Frag - 1) - 0.5), LenZ * fb * 0.5);
                  tex = vec2(i / (Frag - 1), j / (Frag - 1));
                  norm = vec3(0, 0, fb);
                  break;
                }
                vertex::std V(
                  pos,
                  tex,
                  norm,
                  vec4(1)
                );
                this->Vertex[ind++] = V;
              }
          }
        } /* End of 'cube' function */
      }; /* End of 'cube' class */


    /* Plane topology type */
    template<class VertexType>
      class plane : public grid<VertexType>
      {
      public:
        /* Plane constructor
         * ARGUMENTS: None.
         * RETURNS: None.
         */
        plane( VOID ) : grid<VertexType>()
        {
        } /* End of 'plane' function */

        /* Plane constructor
         * ARGUMENTS:
         *   - corner of plane:
         *       vec3 Corner;
         *   - side vectors:
         *       vec3 SideW, SideH;
         *   - separations:
         *       INT W, H;
         * RETURNS: None.
         */
        plane( const vec3 Corner, const vec3 SideW, const vec3 SideH, FLT W, FLT H ) : grid<VertexType>(W, H)
        {
          INT ind = 0;
          vec3 N = (SideW % SideH).Normalize();

          for (INT i = 0; i < H; i++)
          {
            for (INT j = 0; j < W; j++)
            {
              vertex::std V(
                Corner + SideH * (i / H) + SideW * (j / W),
                vec2(i / W, j / W),
                N,
                vec4(1)
              );
              this->Vertex[ind++] = V;
            }
          }
        } /* End of 'plane' function */
      }; /* End of 'plane' class */


  } /* end of 'topology' namespace */

} /* end of 'digl' namespace */

#endif /* __TOPOLOGY_H_ */

/* END OF 'topology.h' FILE */
