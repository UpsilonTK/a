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


#ifndef  DLL_INC
#define  DLL_INC
#define TAM 1024

#include <stdlib.h>
// para malloc and friends y size_t

#include <stdbool.h>
// para bool and friends

#include <assert.h>
// para las aserciones: assert()

#include <stdio.h>
// para fprintf()

#include <string.h>
// para string


typedef struct Node
{
	char* artista;
	char* album;
	char* comentario;
	size_t anhio;
	char* genero;
	size_t numCanciones;
	char** nombreCancion;
	size_t* calificacionCancion;
	size_t calificacionAlbum;
	size_t* duracion;

	struct Node* next;
	struct Node* prev;
} Node;

typedef struct
{
	Node* first;
	Node* last;
	Node* cursor;
	size_t len;
} DLL;


DLL* DLL_New();
void DLL_Delete( DLL** this );

//int DLL_Front( DLL* this );
//int DLL_Back( DLL* this );

void DLL_Insert( DLL* this, char* artista, char* album, char* comentario, size_t anhio, char* genero, size_t numCanciones, char** nombreCancion, size_t* calificacionCancion, size_t calificacionAlbum, size_t* duracion );
void DLL_Push_front( DLL* this, char* artista, char* album, char* comentario, size_t anhio, char* genero, size_t numCanciones, char** nombreCancion, size_t* calificacionCancion, size_t calificacionAlbum, size_t* duracion );
void DLL_Push_back( DLL* this, char* artista, char* album, char* comentario, size_t anhio, char* genero, size_t numCanciones, char** nombreCancion, size_t* calificacionCancion, size_t calificacionAlbum, size_t* duracion );

void DLL_Pop_front( DLL* this );
void DLL_Pop_back( DLL* this );
Node* DLL_Erase( DLL* this, Node* pos );
//void DLL_Remove( DLL* this, int key );
//void DLL_Remove_if( DLL* this, bool (*cmp)( int x, int y ), int key );
void DLL_MakeEmpty( DLL* this );

void DLL_Cursor_front( DLL* this );
void DLL_Cursor_back( DLL* this );
void DLL_Cursor_next( DLL* this );
void DLL_Cursor_prev( DLL* this );
//int DLL_Cursor_Get( DLL* this );

bool DLL_IsEmpty( DLL* this );
size_t DLL_Len( DLL* this );

//void DLL_Traverse( DLL* this, void (*fn)( int item ) );

//Node* DLL_Find( DLL* this, int key );
//Node* DLL_Find_if( DLL* this, bool (*p_fn)( int, int ), int key );

//void DLL_PrintStructure( DLL* this );

void DLL_Leer( DLL* this );
void DLL_Imprimir( DLL* this );
void DLL_Guardar ( DLL* this );
void DLL_Cargar ( DLL* this );

#endif   /* ----- #ifndef DLL_INC  ----- */
