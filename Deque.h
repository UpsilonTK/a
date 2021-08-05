/*Copyright (C) 
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 * 2021 - francisco dot rodriguez at ingenieria dot unam dot edu
 */


#ifndef  DEQUE_INC
#define  DEQUE_INC

#include <stdlib.h>
// para malloc and friends y size_t

#include <stdbool.h>
// para bool and friends

#include <assert.h>
// para las aserciones: assert()

#include <stdio.h>
// para fprintf()

#include "DLL.h"

typedef struct
{
   DLL* deq;
} Deque;


Deque* Deque_New( void );
void Deque_Delete( Deque** this );
void Deque_Enqueue_front( Deque* this, char* artista, char* album, char* comentario, size_t anhio, char* genero, size_t numCanciones, char** nombreCancion, size_t* calificacionCancion, size_t calificacionAlbum, size_t* duracion );
void Deque_Enqueue_back( Deque* this, char* artista, char* album, char* comentario, size_t anhio, char* genero, size_t numCanciones, char** nombreCancion, size_t* calificacionCancion, size_t calificacionAlbum, size_t* duracion );
//int Deque_Dequeue_front( Deque* this );
//int Deque_Dequeue_back( Deque* this );
bool Deque_IsEmpty( Deque* this );
size_t Deque_Len( Deque* this );

#endif   /* ----- #ifndef DLL_INC  ----- */
