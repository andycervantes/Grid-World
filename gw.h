typedef struct people_data PEOPLE_DATA;
typedef struct district_data DISTRICT_DATA;
typedef struct world_data WORLD_DATA;

WORLD_DATA *world_build( int nrows, int ncols, int pop, int rnd );
extern int *world_members( WORLD_DATA * w, int i, int j, int *length );
extern int world_district_pop( WORLD_DATA * w, int i, int j );
extern int world_total_pop( WORLD_DATA * w );
extern int world_move( WORLD_DATA * w, int pin, int i, int j );
extern int world_find( WORLD_DATA * w, int pin, int *r, int *c );
extern int world_kill( WORLD_DATA * w, int pin );
extern int world_create( WORLD_DATA * w, int i, int j );
extern void world_delete( WORLD_DATA * w );

// macro for allocating memory
#define CREATE( result, type, size )								\
do												\
{												\
	if ( !( ( result ) = ( type * ) calloc( ( size ), sizeof( type ) ) ) )			\
	{											\
		perror( "Calloc Failure" );							\
		fprintf( stderr, "Calloc failure: %s @ %d.\n", __FILE__, __LINE__ );		\
		abort( );									\
	}											\
}	while( 0 )

// delete a node in a doubly linked list
#define DELETE_DLL( head, deleting )								\
do												\
{												\
	if ( ( head ) == ( deleting ) )								\
		( head ) = ( deleting )->next;							\
												\
	if ( ( deleting )->next != NULL )							\
		( deleting )->next->prev = ( deleting )->prev;					\
												\
	if ( ( deleting )->prev != NULL )							\
		( deleting )->prev->next = ( deleting )->next;					\
												\
	free( ( deleting ) );									\
}	while( 0 )

// insert a node at the beginning of the doubly linked list
#define INSERT_DLL( head, new_node )								\
do												\
{												\
	( new_node )->prev = NULL;								\
												\
	( new_node )->next = ( head );								\
												\
	if ( ( head ) != NULL )									\
		( head )->prev = ( new_node );							\
												\
	( head ) = ( new_node );								\
}	while ( 0 )

// single list insert
#define INSERT_SLL( head, inserted )								\
do												\
{												\
	( inserted )->next = ( head );								\
	( head ) = ( inserted );								\
}	while ( 0 )
