
#include <stdio.h>
// para printf

#include <stdlib.h>
// para malloc and friends y size_t

#include <stdbool.h>
// para bool and friends

#include "Deque.h"

//----------------------------------------------------------------------
//  Driver program
//----------------------------------------------------------------------
int main( void )
{
   Deque* deq = Deque_New();
   DLL_Cargar( deq->deq );

   //DLL_Leer( deq->deq );
   DLL_Imprimir( deq->deq );

   DLL_Guardar( deq->deq );
   Deque_Delete( &deq );

   return 1;
}