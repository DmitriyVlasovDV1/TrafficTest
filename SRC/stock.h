/***************************************************************
 * Copyright (C) 2020
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : STOCK.H
 * PURPOSE     : Stock header file.
 * PROGRAMMER  : Vlasov Dmitriy.
 * LAST UPDATE : 25.07.2020.
 * NOTE        : Namespace 'digl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __STOCK_H_
#define __STOCK_H_

/* Includes */
#include "def.h"
#include <vector>

/* Animation project namespace */
namespace digl
{
  /* Stock representation type */
  template<typename T>
    class stock : public std::vector<T>
    {
    public:
      /* Add element to stock function.
       * ARGUMENTS:
       *   - element:
       *       const T &X;
       * RETUNRNS:
       *   (stock &) this stock.
       */
      stock & operator<<( const T &X )
      {
        this->push_back(X);
        return *this;
      } /* End of 'operator<<' function */

      /* Stock walk function.
       * ARGUMENTS:
       *   - type of action:
       *       WalkType Walk
       * RETUNRS: None.
       */
      template<class WalkType>
        void Walk( WalkType Walk )
        {
          for (auto &x : *this)
            Walk(x);
        } /* End of 'Walk' function */
    }; /* End of 'stock' class */
} /* end of 'digl' namespace */

#endif /* __STOCK_H_ */

/* END OF 'stock.h' FILE */