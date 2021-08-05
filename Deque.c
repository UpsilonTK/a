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

#include "Deque.h"

/*static bool validarMenu ( size_t opc, size_t max )
{
	bool ban = true;
	
	if ( opc < 1 || opc > max )
	{
		printf( "ERROR, opcion no valida\n" );
		system( "pause" );
		ban = false;
	}
	
	return ban;
}

static size_t menu (void)
{
	size_t opc;
	do{
		system ( "cls" );
		printf( "Bienvenido a tu biblioteca de música\n\n" );
		printf( "MENU\n" );
		printf( "1.-REGISTRAR NUEVO ALBUM EN LA LISTA\n" );
		printf( "2.-CARGAR BASE DE DATOS\n" );
		printf( "3.-GUARDAR BASE DE DATOS\n" );
		printf( "4.-IMPRIMIR TODOS LOS ALBUM EN PANTALLA\n" );
		printf( "5.-Salir\n\n" );
		printf( "Por favor seleccione una opcion: " );
		scanf( "%ld", &opc );
	}while( validarMenu( opc, 5 ) );
	
	return opc;
}*/

Deque* Deque_New( void )
{
   Deque* d = (Deque*) malloc( sizeof ( Deque ) );
   
   if( d )
   d->deq = DLL_New();
   
   return d;
}

void Deque_Delete( Deque** this )
{
   if( *this ){
        DLL_Delete( &((*this)->deq) );
        free( *this );
      *this = NULL;
    }
}

void Deque_Enqueue_front( Deque* this, char* artista, char* album, char* comentario, size_t anhio, char* genero, size_t numCanciones, char** nombreCancion, size_t* calificacionCancion, size_t calificacionAlbum, size_t* duracion )
{
   DLL_Push_front( this->deq, artista, album, comentario, anhio, genero, numCanciones, nombreCancion, calificacionCancion, calificacionAlbum, duracion );
}

void Deque_Enqueue_back( Deque* this, char* artista, char* album, char* comentario, size_t anhio, char* genero, size_t numCanciones, char** nombreCancion, size_t* calificacionCancion, size_t calificacionAlbum, size_t* duracion )
{
   DLL_Push_back( this->deq, artista, album, comentario, anhio, genero, numCanciones, nombreCancion, calificacionCancion, calificacionAlbum, duracion );
}
/*
int Deque_Dequeue_front( Deque* this )
{
   assert( !DLL_IsEmpty( this->deq ) );
   
   int retVal = DLL_Front( this->deq );

   DLL_Pop_front( this->deq );
   
   return retVal;
}

int Deque_Dequeue_back( Deque* this )
{
   assert( !DLL_IsEmpty( this->deq ) );
   
   int retVal = DLL_Back( this->deq );

   DLL_Pop_back( this->deq );
   
   return retVal;
}
*/
bool Deque_IsEmpty( Deque* this )
{
   return DLL_IsEmpty( this->deq );
}

size_t Deque_Len( Deque* this )
{
   return DLL_Len( this->deq );
}