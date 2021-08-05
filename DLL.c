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

#include "DLL.h"

static Node* new_node( char* artista, char* album, char* comentario, size_t anhio, char* genero, size_t numCanciones, char** nombreCancion, size_t* calificacionCancion, size_t calificacionAlbum, size_t* duracion )
{
   Node* n = (Node*) malloc( sizeof( Node ) );
   if( n != NULL ){
      n->artista = artista;
	   n->album = album;
	   n->comentario = comentario;
	   n->anhio = anhio;
	   n->genero = genero;
	   n->numCanciones = numCanciones;
	   n->nombreCancion = nombreCancion;
	   n->calificacionCancion = calificacionCancion;
	   n->calificacionAlbum = calificacionAlbum;
      n->duracion = duracion;

      n->next = NULL;
      n->prev = NULL;
   }
   return n;
}

static char* estrellas( size_t calificacion )
{
   char* buffer = (char*) malloc( TAM * sizeof( char ) );

   switch ( calificacion ){

      case 0:
         strcpy( buffer, "Pésima" );
      break;

      case 1:
         strcpy( buffer, "Mala" );
      break;

      case 2:
         strcpy( buffer, "Regular" );
      break;

      case 3:
         strcpy( buffer, "Normal" );
      break;

      case 4:
         strcpy( buffer, "Buena" );
      break;

      case 5:
         strcpy( buffer, "Excelente" );
      break;
   }

   return buffer;

   free ( buffer );
   buffer = NULL;
}

static char* ssm_2_hms( size_t ssm )
{
   char* buffer = (char*) malloc( TAM * sizeof( char ) );
   size_t h = ( ssm / 3600 );
   size_t m = ( ssm - ( 3600 * (h) ) ) / 60;
   size_t s = ( ssm - ( 3600 * (h) ) - ( 60 * (m) ) );

   if ( h == 0 ){
      sprintf( buffer, "%02ld:%02ld", m, s );
   } else{
      sprintf( buffer, "%02ld:%02ld:%02ld", h, m, s );
   }

   return buffer;

   free ( buffer );
   buffer = NULL;
}

/**
 * @brief Crea una lista doblemente enlazada
 *
 * @return Una referencia a la nueva lista
 * @post Una lista existente en el heap
 */
DLL* DLL_New()
{
   DLL* list = (DLL*) malloc( sizeof( DLL ) );
   if( list != NULL ){
      list->first = NULL;
      list->last = NULL;
      list->cursor = NULL;
      list->len = 0;
   }

   return list;
}

/**
 * @brief Destruye una lista.
 *
 * @param this Una lista.
 */
void DLL_Delete( DLL** this )
{
   assert( *this );

   // 1. Borramos todos los nodos:
   while( (*this)->first != NULL ){
      DLL_Pop_back( *this );
   }

   // 2. Borramos al objeto DLL:
   free( *this );

   // 3. EviTAMos problemas futuros:
   *this = NULL;
}

/**
 * @brief Devuelve una copia del elemento en el frente de la lista.
 *
 * @param this Una lista.
 *
 * @return La copia del elemento en el frente de la lista.
 *
 * @post Si la lista está vacía se dispara una aserción.
 */
 /*
int DLL_Front( DLL* this )
{
   assert( this->first != NULL );
   // ERR: no se puede leer de una lista vacía

   return this->first->datos;
}
*/
/**
 * @brief Devuelve una copia del elemento en la parte trasera de la lista.
 *
 * @param this Una lista.
 *
 * @return La copia del elemento en la parte trasera de la lista.
 *
 * @post Si la lista está vacía se dispara una aserción.
 */
 /*
int DLL_Back( DLL* this )
{
   assert( this->first != NULL );
   // ERR: no se puede leer de una lista vacía

   return this->last->datos;
}
*/

/**
 * @brief Inserta un elemento a la derecha del cursor.
 *
 * @param lista Una referencia a la lista de trabajo
 * @param item El elemento a insertar
 */
void DLL_Insert( DLL* this, char* artista, char* album, char* comentario, size_t anhio, char* genero, size_t numCanciones, char** nombreCancion, size_t* calificacionCancion, size_t calificacionAlbum, size_t* duracion )
{
   Node* n = new_node( artista, album, comentario, anhio, genero, numCanciones, nombreCancion, calificacionCancion, calificacionAlbum, duracion );
   assert( n );

   if( this->first != NULL ){ // Comprueba que la lista no está vacía

      if( this->cursor->next == NULL ){ // Sí el cursor está al final mejor se usa la función DLL_Push_back
         
         DLL_Push_back( this, artista, album, comentario, anhio, genero, numCanciones, nombreCancion, calificacionCancion, calificacionAlbum, duracion );
      
      } else{ // En caso contrario, entonces se agrega el elemento en medio de dos nodos
                              
         n->prev = this->cursor; // El previo del nuevo nodo apunta a this
         DLL_Cursor_next( this ); // Me voy al siguiente nodo que será el siguiente de n
         n->next = this->cursor; // El siguiente del nuevo nodo apunta a this
         DLL_Cursor_prev( this ); // Me regreso al cursor original
         this->cursor->next = n; // El siguiente lo apunto al nuevo nodo
         DLL_Cursor_next( this ); // Me desplazo al nodo n
         DLL_Cursor_next( this ); // Me desplazo al nodo posterior a n
         this->cursor->prev = n; // El previo de este nodo apunta a n
         DLL_Cursor_prev( this ); // Me regreso a n
      }

   } else{  // Si la lista estaba vacía entonces se agrega un nuevo elemento
      this->first = this->last = this->cursor = n;
   }
   ++this->len;
}

/**
 * @brief Inserta un elemento en el frente de la lista.
 *
 * @param this Una lista.
 * @param item El elemento a insertar
 */
void DLL_Push_front( DLL* this, char* artista, char* album, char* comentario, size_t anhio, char* genero, size_t numCanciones, char** nombreCancion, size_t* calificacionCancion, size_t calificacionAlbum, size_t* duracion )
{
   Node* n = new_node( artista, album, comentario, anhio, genero, numCanciones, nombreCancion, calificacionCancion, calificacionAlbum, duracion );
   assert( n );

   if( this->first != NULL ){

      this->first->prev = n;
      n->next = this->first;
      this->first = n;
   } else{
      this->first = this->last = this->cursor = n;
   }
   ++this->len;
}

/**
 * @brief Inserta un elemento en el fondo de la lista.
 *
 * @param this Una lista.
 * @param item El elemento a insertar
 */
void DLL_Push_back( DLL* this, char* artista, char* album, char* comentario, size_t anhio, char* genero, size_t numCanciones, char** nombreCancion, size_t* calificacionCancion, size_t calificacionAlbum, size_t* duracion )
{
   Node* n = new_node( artista, album, comentario, anhio, genero, numCanciones, nombreCancion, calificacionCancion, calificacionAlbum, duracion );
   assert( n );

   if( this->first != NULL ){

      this->last->next = n;
      n->prev = this->last;
      this->last = n;
   } else{
      this->first = this->last = this->cursor = n;
   }
   ++this->len;
}

/**
 * @brief Elimina el elemento al frente de la lista.
 *
 * @param this Referencia a una lista.
 *
 * @post El cursor se mantiene en la posición en la que estaba cuando entró la
 * función.
 */
void DLL_Pop_front( DLL* this )
{
   assert( this->len );
   // ERR: no se puede borrar nada de una lista vacía

   if( this->last != this->first ){ // TAMbién funciona: if( this->len > 1 ){...}
      Node* x = this->first->next;

      free( this->first->artista );
      this->first->artista = NULL;
      free( this->first->album );
      this->first->album = NULL;
      free( this->first->comentario );
      this->first->comentario = NULL;
      free( this->first->genero );
      this->first->genero = NULL;
      free( this->first->calificacionCancion );
      this->first->calificacionCancion = NULL;
      free( this->first->duracion );
      this->first->duracion = NULL;
      for ( size_t i = 0; i < this->first->numCanciones; i++ ){
         free( (this->first->nombreCancion[i]) );
         this->first->nombreCancion[i] = NULL;
      }
      free( *this->first->nombreCancion );
      *this->first->nombreCancion = NULL;

      free( this->first );

      x->prev = NULL;
      this->first = x;
      --this->len;
   } else{
      free( this->first->artista );
      this->first->artista = NULL;
      free( this->first->album );
      this->first->album = NULL;
      free( this->first->comentario );
      this->first->comentario = NULL;
      free( this->first->genero );
      this->first->genero = NULL;
      free( this->first->calificacionCancion );
      this->first->calificacionCancion = NULL;
      free( this->first->duracion );
      this->first->duracion = NULL;
      for ( size_t i = 0; i < this->first->numCanciones; i++ ){
         free( (this->first->nombreCancion[i]) );
         this->first->nombreCancion[i] = NULL;
      }
      free( *this->first->nombreCancion );
      *this->first->nombreCancion = NULL;

      free( this->last );
      this->first = this->last = this->cursor = NULL; // Había un solo elemento
   }
}

/**
 * @brief Elimina el elemento al fondo de la lista.
 *
 * @param this Referencia a una lista.
 *
 * @post El cursor se mantiene en la posición en la que estaba cuando entró la
 * función.
 */
void DLL_Pop_back( DLL* this )
{
   assert( this->len );
   // ERR: no se puede borrar nada de una lista vacía

   if( this->last != this->first ){ // TAMbién funciona: if( this->len > 1 ){...}
      Node* x = this->last->prev;

      free( this->first->artista );
      this->first->artista = NULL;
      free( this->first->album );
      this->first->album = NULL;
      free( this->first->comentario );
      this->first->comentario = NULL;
      free( this->first->genero );
      this->first->genero = NULL;
      free( this->first->calificacionCancion );
      this->first->calificacionCancion = NULL;
      free( this->first->duracion );
      this->first->duracion = NULL;
      for ( size_t i = 0; i < this->first->numCanciones; i++ ){
         free( (this->first->nombreCancion[i]) );
         this->first->nombreCancion[i] = NULL;
      }
      free( *this->first->nombreCancion );
      *this->first->nombreCancion = NULL;

      free( this->last );
      x->next = NULL;
      this->last = x;
      --this->len;
   } else{
      free( this->first->artista );
      this->first->artista = NULL;
      free( this->first->album );
      this->first->album = NULL;
      free( this->first->comentario );
      this->first->comentario = NULL;
      free( this->first->genero );
      this->first->genero = NULL;
      free( this->first->calificacionCancion );
      this->first->calificacionCancion = NULL;
      free( this->first->duracion );
      this->first->duracion = NULL;
      for ( size_t i = 0; i < this->first->numCanciones; i++ ){
         free( (this->first->nombreCancion[i]) );
         this->first->nombreCancion[i] = NULL;
      }
      free( *this->first->nombreCancion );
      *this->first->nombreCancion = NULL;
      
      free( this->last );
      this->first = this->last = this->cursor = NULL; // Había un solo elemento
   }
}

/**
 * @brief Elimina un elemento.
 *
 * @param this Una lista.
 * @param pos Una posición válida. Éste se puede obtener de las diferentes funciones de movimiento del cursor y de las funciones de búsqueda.
 *
 * @return Una referencia al elemento a la derecha del elemento que se acaba de borrar.
 */
Node* DLL_Erase( DLL* this, Node* pos )
{
   assert( DLL_IsEmpty( this ) == false );
   // ERR: no se puede eliminar nada de una lista vacía

   Node* x = pos->next;

   return x;

}

/**
 * @brief Elimina el primer nodo que coincida con la llave.
 *
 * @param this Referencia a una lista.
 * @param key  Valor buscado
 *
 */
 /*
void DLL_Remove( DLL* this, int key )
{
   assert( DLL_IsEmpty( this ) == false );
   // ERR: no se puede borrar nada de una lista vacía

   Node* it = this->first;
   // |it| es la abreviación de "iterator", o  en español, "iterador"

   while( it != NULL ){

      if( it->datos == key ) DLL_Erase( this, it );

      it = it->next;
   }
}
*/

/**
 * @brief Elimina todos los elementos que den positivo a la función predicado.
 *
 * @param this Una lista.
 * @param cmp Función predicado. El elemento |y| es proporcionado por el argumento |key|, mientras que el valor |x| se obtiene de la lista. Por ejemplo, si la función quiere saber si el valor de la lista es menor que el valor del usuario (list_val < user_val), entonces la función podría ser: less_than( list_val, user_val), la cual se lee en conjunto: "Si el valor de la lista |list_val| es menor que el valor del usuario |user_val|, devuelve verdadero".
 * @param key El valor contra el que se está comparando.
 */
 /*
void DLL_Remove_if( DLL* this, bool (*cmp)( int x, int y ), int key )
{
   assert( DLL_IsEmpty( this ) == false );
   // ERR: no se puede eliminar nada de una lista vacía

   Node* it = this->first;
   // |it| es la abreviación de "iterator", o  en español, "iterador"

   while( it != NULL ){

      if( cmp( it->datos, key ) == true ) DLL_Erase( this, it );

      it = it->next;
   }
}
*/

/**
 * @brief Elimina todos los elementos de la lista sin eliminar la lista.
 *
 * @param this Referencia a una lista.
 */
void DLL_MakeEmpty( DLL* this )
{
   assert( this );

   // 1. Borramos todos los nodos:
   while( this->first != NULL ){
      DLL_Pop_back( this );
   }
}

/**
 * @brief Coloca al cursor al inicio de la lista.
 *
 * @param this Una referencia a la lista de trabajo
 */
void DLL_Cursor_front( DLL* this )
{
   this->cursor = this->first;
}

/**
 * @brief Coloca al cursor al final de la lista.
 *
 * @param this Una referencia a la lista de trabajo
 */
void DLL_Cursor_back( DLL* this )
{
   this->cursor = this->last;
}

/**
 * @brief Mueve al cursor al siguiente elemento a la derecha.
 *
 * @param this Una lista.
 */
void DLL_Cursor_next( DLL* this )
{
   assert( this->cursor != NULL );

   Node* right = this->cursor->next;
   this->cursor = right;
}

/**
 * @brief Mueve al cursor al siguiente elemento a la izquierda.
 *
 * @param this Una lista.
 */
void DLL_Cursor_prev( DLL* this )
{
   assert( this->cursor != NULL );

   Node* left = this->cursor->prev;
   this->cursor = left;
}

/**
 * @brief Devuelve una copia del valor apuntado por el cursor.
 *
 * @param this Una lista.
 *
 * @return El valor apuntado por el cursor.
 */
/*
int DLL_Cursor_Get( DLL* this )
{
   assert( this->cursor );
   // ERR: no se puede obtener un dato si la lista esta vacia

   return this->cursor->datos;
}
*/

/**
 * @brief Indica si la lista está vacía.
 *
 * @param this Referencia a una lista.
 *
 * @return true si la lista está vacía; false en caso contrario.
 */
bool DLL_IsEmpty( DLL* this )
{
   return this->first == NULL;
}

/**
 * @brief Devuelve el número actual de elementos en la lista.
 *
 * @param this Una lista.
 *
 * @return Devuelve el número actual de elementos en la lista.
 */
size_t DLL_Len( DLL* this )
{

   assert( this );

   return this->len;
}

/**
 * @brief Recorre la lista y hace algo en cada uno de sus elementos
 *
 * @param lista Una referencia a la lista de trabajo
 * @param fn Esta función hace algo con el campo de datos 
 */
 /*
void DLL_Traverse( DLL* this, void (*fn)( int item ) )
{
	if( NULL == this ){ return; }

	Node* t = this->first;
   // ¡NO PODEMOS PERDER A FIRST!  
   
   while( t != NULL ){

		fn( t->datos );

		t = t->next;
   }
}
*/

/**
 * @brief Busca un valor en la lista.
 *
 * @param this Una lista.
 * @param key El valor que se está buscando.
 *
 * @return Un apuntador al nodo donde se haya encontrado la primer coincidencia. Devuelve NULL en caso de no haber encontrado ninguna.
 */
 /*
Node* DLL_Find( DLL* this, int key )
{
   assert( DLL_IsEmpty( this ) == false );
   // ERR: no se puede buscar nada en una lista vacía

   Node* it = this->first;
   // |it| es la abreviación de "iterator", o  en español, "iterador"

   while( it != NULL ){

      if( it->datos == key ) break;

      it = it->next;
   }

   return it;
   // ¡un único punto de salida!
}
*/

/**
 * @brief Busca si algún valor en la lista cumple con la función predicado.
 *
 * @param this Una lista.
 * @param p_fn Función predicado. El elemento |y| es proporcionado por el argumento |key|, mientras que el valor |x| se obtiene de la lista. Por ejemplo, si la función quiere saber si el valor de la lista es menor que el valor del usuario (list_val < user_val), entonces la función podría ser: less_than( list_val, user_val), la cual se lee en conjunto: "Si el valor de la lista |list_val| es menor que el valor del usuario |user_val|, devuelve verdadero".
 * @param key El valor contra el que se está realizando la comparación.
 *
 * @return Un apuntador al nodo donde se haya encontrado la primer coincidencia. Devuelve NULL en caso de no haber encontrado ninguna.
 */
 /*
Node* DLL_Find_if( DLL* this, bool (*cmp)( int, int ), int key )
{
   assert( DLL_IsEmpty( this ) == false );
   // ERR: no se puede buscar nada en una lista vacía

   Node* it = this->first;
   // |it| es la abreviación de "iterator", o  en español, "iterador"

   while( it != NULL ){

      if( cmp( it->datos, key ) == true ) break;

      it = it->next;
   }

   return it;
}
*/

/**
 * @brief Imprime la estructura de la lista. Es para uso de depuración, no de uso general.
 *
 * @param this Una lista.
 */
/* 
void DLL_PrintStructure( DLL* this )
{
   if( DLL_IsEmpty( this ) ){
      fprintf( stderr, "\nEmpty list. Nothing to show.\n" );
   } else{

      Node* it = this->first;

      fprintf( stderr, "\nNil->" );
      while( it != NULL ){

         fprintf( stderr, "(%ld)->", it->duracion );

         it = it->next;
      }
      fprintf( stderr, "Nil\n" );
   }
}
*/

void DLL_Leer( DLL* this )
{
   size_t anhio;
   size_t numCanciones;
   size_t calificacionAlbum;
   char* buffer = (char*) malloc( TAM * sizeof( char ) );

   if( NULL == buffer ){
      printf( "Error asignando memoria\n" );
      exit( 1 );
   }

   printf( "\nIngrese el nombre del artista: " );
	fgets( buffer, TAM, stdin );
   char* artista = (char*) malloc( strlen( buffer ) * sizeof( char ) );
   strcpy( artista, buffer );

   printf( "Ingrese el nombre del álbum: " );
	fgets( buffer, TAM, stdin );
   char* album = (char*) malloc( strlen( buffer ) * sizeof( char ) );
   strcpy( album, buffer );

   printf( "Ingrese la calificación del álbum: " );
	scanf( "%ld", &calificacionAlbum );
   fgets( buffer, TAM, stdin );

   printf( "Ingrese un comentario del álbum: " );
	fgets( buffer, TAM, stdin );
   char* comentario = (char*) malloc( strlen( buffer ) * sizeof( char ) );
   strcpy( comentario, buffer );

	printf( "Ingrese el año de lanzamiento: " );
	scanf( "%ld", &anhio );
   fgets( buffer, TAM, stdin );

   printf( "Ingrese el género del álbum: " );
	fgets( buffer, TAM, stdin );
   char* genero = (char*) malloc( strlen( buffer ) * sizeof( char ) );
   strcpy( genero, buffer );
	
	printf( "Ingrese el número de pistas del álbum: " );
	scanf( "%ld", &numCanciones );
   fgets( buffer, TAM, stdin );
	
   char** nombreCancion = (char**) malloc( numCanciones * sizeof( char* ) );
   size_t* calificacionCancion = (size_t*) malloc( numCanciones * sizeof( size_t ) );
   size_t* duracion = (size_t*) malloc( numCanciones * sizeof( size_t ) );

	for ( size_t i = 0; i < numCanciones; i++ ){
		printf( "\nIngrese el nombre de la canción %ld : ", i+1 );
		fgets( buffer, TAM, stdin );
      nombreCancion[i] = (char*) malloc( strlen( buffer ) * sizeof( char ) );
      strcpy( nombreCancion[i], buffer );

      printf( "Ingrese la calificación de la canción %ld : ", i+1 );
      scanf( "%ld", &calificacionCancion[i] );
      fgets( buffer, TAM, stdin );

      printf( "Ingrese la duración en segundos de la canción %ld : ", i+1 );
      scanf( "%ld", &duracion[i] );
      fgets( buffer, TAM, stdin );
	}

   DLL_Push_back( this, artista, album, comentario, anhio, genero, numCanciones, nombreCancion, calificacionCancion, calificacionAlbum, duracion );

   free ( buffer );
   buffer = NULL;
}

void DLL_Imprimir( DLL* this )
{

   if( DLL_IsEmpty( this ) ){
      fprintf( stderr, "\nEmpty list. Nothing to show.\n" );
   } else{

      Node* it = this->first;

      while( it != NULL ){

         printf( "\nArtista: %s", it->artista );
         printf( "Álbum: %s", it->album );
         printf( "Calificación del álbum: %s", estrellas( it->calificacionAlbum ) );
         printf( "\nComentario: %s", it->comentario );
		   printf( "Año: %ld", it->anhio );
		   printf( "\nGénero: %s", it->genero );
         printf( "Número de pistas: %ld\n", it->numCanciones );
      	
         for ( size_t i = 0; i < it->numCanciones; i++ ){
            printf( "\n" );
            printf( "Nombre de la canción %ld: %s", i+1, it->nombreCancion[i] );
            printf( "Calificación: %s", estrellas( it->calificacionCancion[i] ) );
            printf( "\nDuración: %s", ssm_2_hms( it->duracion[i] ) );
            printf( "\n" );
	      }


         printf( "\n***************************************************\n" );

         it = it->next;
      }
   }

}

void DLL_Guardar ( DLL* this )
{
   FILE* biblioteca;
   Node* it = this->first;

   biblioteca = fopen( "biblioteca.txt", "w+" );
	
	if ( it == NULL ){
      fclose( biblioteca );
   } else{
      while ( it != NULL ){
         fprintf( biblioteca, "%s", it->artista );
         fprintf( biblioteca, "%s", it->album );
         fprintf( biblioteca, "%ld", it->calificacionAlbum );
         fprintf( biblioteca, "%s", "\n" );
         fprintf( biblioteca, "%s", it->comentario );
		   fprintf( biblioteca, "%ld", it->anhio );
         fprintf( biblioteca, "%s", "\n" );
		   fprintf( biblioteca, "%s", it->genero );
         fprintf( biblioteca, "%ld", it->numCanciones );
         fprintf( biblioteca, "%s", "\n" );

         for ( size_t i = 0; i < it->numCanciones; i++ ){
            fprintf( biblioteca, "%s", "\n" );
            fprintf( biblioteca, "%s", it->nombreCancion[i] );
            fprintf( biblioteca, "%ld", it->calificacionCancion[i] );
            fprintf( biblioteca, "%s", "\n" );
            fprintf( biblioteca, "%ld", it->duracion[i] );
            fprintf( biblioteca, "%s", "\n" );
	      }
         fprintf( biblioteca, "%s", "\n" );
		   fprintf( biblioteca, "%s", "***************************************************" );
         fprintf( biblioteca, "%s", "\n" );
         fprintf( biblioteca, "%s", "\n" );
			
			it = it->next;
		}// Fin del while para guardar toda la informacion
		
		fprintf( biblioteca, "%s", "@**FIN**" );
		
		fclose( biblioteca );
	}
}

void DLL_Cargar ( DLL* this )
{
   FILE* biblioteca;
   size_t anhio;
   size_t numCanciones;
   size_t calificacionAlbum;
   char* buffer = (char*) malloc( TAM * sizeof( char ) );
   bool ban = true;

   if( NULL == buffer ){
      printf( "Error asignando memoria\n" );
      exit( 1 );
   }

   biblioteca = fopen( "biblioteca.txt", "r+" );

   fseek( biblioteca, 0, SEEK_END );
   if (ftell( biblioteca ) == 0 ) //El archivo esta vacio
   {
      fclose( biblioteca );
      free ( buffer );
      buffer = NULL;
   } else{
      rewind( biblioteca );
      while ( ban == true ){
         fgets( buffer, TAM, biblioteca );
         if ( buffer[0] == '@' ){ //Llegamos al final del fichero
            fclose( biblioteca );
            free ( buffer );
            buffer = NULL;
            ban = false;
         } else{
            char* artista = (char*) malloc( strlen( buffer ) * sizeof( char ) );
            strcpy( artista, buffer );

            fgets( buffer, TAM, biblioteca );
            char* album = (char*) malloc( strlen( buffer ) * sizeof( char ) );
            strcpy( album, buffer );

            fscanf( biblioteca, "%ld", &calificacionAlbum );
            fgets( buffer, TAM, biblioteca );

            fgets( buffer, TAM, biblioteca );
            char* comentario = (char*) malloc( strlen( buffer ) * sizeof( char ) );
            strcpy( comentario, buffer );
	
            fscanf( biblioteca, "%ld", &anhio );
            fgets( buffer, TAM, biblioteca );
   
            fgets( buffer, TAM, biblioteca );
            char* genero = (char*) malloc( strlen( buffer ) * sizeof( char ) );
            strcpy( genero, buffer );
	
	         fscanf( biblioteca, "%ld", &numCanciones );
            fgets( buffer, TAM, biblioteca );
   
            char** nombreCancion = (char**) malloc( numCanciones * sizeof( char* ) );
            size_t* calificacionCancion = (size_t*) malloc( numCanciones * sizeof( size_t ) );
            size_t* duracion = (size_t*) malloc( numCanciones * sizeof( size_t ) );

	         for ( size_t i = 0; i < numCanciones; i++ ){
               fgets( buffer, TAM, biblioteca );
		         fgets( buffer, TAM, biblioteca );
               nombreCancion[i] = (char*) malloc( strlen( buffer ) * sizeof( char ) );
               strcpy( nombreCancion[i], buffer );

               fscanf( biblioteca, "%ld", &calificacionCancion[i] );
               fgets( buffer, TAM, biblioteca );

               fscanf( biblioteca, "%ld", &duracion[i] );
               fgets( buffer, TAM, biblioteca );
	         }

            fgets( buffer, TAM, biblioteca );
            fgets( buffer, TAM, biblioteca );
            fgets( buffer, TAM, biblioteca );

            DLL_Push_back( this, artista, album, comentario, anhio, genero, numCanciones, nombreCancion, calificacionCancion, calificacionAlbum, duracion );
         }
      }
   }
}