// andy cervantes

#include <stdlib.h>
#include <stdio.h>
#include "gw.h"

typedef struct people_data PEOPLE_DATA;
typedef struct district_data DISTRICT_DATA;
typedef struct world_data WORLD_DATA;

struct world_data
{
	// properties of a single instance of a world
	int world_population;
	int nrows;
	int ncols;

	// link the world_data structure to the district_data structure
	DISTRICT_DATA **district;
	DISTRICT_DATA *deadpool;
	PEOPLE_DATA *people;
};

struct district_data
{
	// create a link of itself as a pointer
//	DISTRICT_DATA * next;
	int district_population;
	PEOPLE_DATA *first_person;
	DISTRICT_DATA *first;
};

struct people_data
{
	// lets make the people structure double linked list
	PEOPLE_DATA *next;
	PEOPLE_DATA *prev;

	int pin;
	int x_cord;
	int y_cord;
};

WORLD_DATA *world_build( int nrows, int ncols, int pop, int rnd )
{
	WORLD_DATA *world = NULL;
	PEOPLE_DATA *citizen = NULL;
	DISTRICT_DATA **districts = NULL;
	int world_size = nrows * ncols;
	int i;

//	PEOPLE_DATA *first_citizen = NULL;

	// create world data
	CREATE( world, WORLD_DATA, 1 );
//	world = ( WORLD_DATA * ) malloc( sizeof( WORLD_DATA ) ); 

	world->nrows = nrows;
	world->ncols = ncols;
	world->world_population = pop;

	// create district data
	CREATE( districts, DISTRICT_DATA *, nrows );
//	CREATE( districts, DISTRICT_DATA, world_size );
	world->district = districts;
//	world->districts = ( DISTRICT_DATA ** ) malloc( ( ncols ) * sizeof( DISTRICT_DATA * ) );

	for ( i = 0; i < nrows; i++ )
	{
		CREATE( districts[i], DISTRICT_DATA, ncols );
//		world->district[i] = ( DISTRICT_DATA * ) malloc( ( nrows ) * sizeof( DISTRICT_DATA ) );
		world->district[i] = districts[i];
	}

	// used to intialize array but we are using calloc now instead of malloc
	int x = 0;
	int y = 0;

	while ( y < ncols )
	{
		world->district[x][y].district_population = 0;
		world->district[x][y].first_person = malloc( sizeof( PEOPLE_DATA ) );
		world->district[x][y].first_person->next = NULL;
		world->district[x][y].first_person->prev = NULL;
		
		if ( !( x = ( x + 1 ) % nrows ) )
			y++;
	}
/*
	for ( x = 0; x < nrows; x++ )
	{
		for ( y = 0; y < ncols; y++ )
		{
			world->district[x][y].district_population = 0;
			world->district[x][y].first_person = malloc( sizeof( PEOPLE_DATA ) );
			world->district[x][y].first_person->next = NULL;
			world->district[x][y].first_person->prev = NULL;
			printf("it works: y: %d x: %d\n", y, x );
		
		}
	}
*/
	// create array of citizens sized to pop value
	CREATE( citizen, PEOPLE_DATA, pop );

	int p;
	int xPos = 0;
	int yPos = 0;

	// intiallize every citizen created
	for ( p = 0; p < pop; p++ )
	{
		// create people data
		citizen[p].pin = p;
		citizen[p].next = NULL;
		citizen[p].prev = NULL;

		// if rnd flag is triggered then we want to randomize the x/y coordinates for each citizen
		if ( rnd )
		{
			xPos = rand(  ) % world_size - 1;
			yPos = rand(  ) % world_size - 1;
		}

		printf( "%d, %d\n", xPos, yPos );

		citizen[p].x_cord = xPos;
		citizen[p].y_cord = yPos;
//		this kills the code
//		world->district[x][y].district_population = 0;
//		world->district[xPos][yPos].district_population;

//		INSERT_SLL( world->district[xPos][yPos], citizen );
		INSERT_SLL( citizen, citizen );
		
//		citizen[p]
	}
//	DISTRICT_DATA *first_dis = NULL;
//	INSERT_DLL( districts, first_dis );
	return world;
}

int *world_members( WORLD_DATA * w, int i, int j, int *length )
{
	int *mArray = NULL;

	if ( i < w->nrows || j < w->ncols || i < 0 || j < 0 )
		return NULL;

	( *length ) = 0;
	CREATE( mArray, int, w->district[i][j].district_population );
	PEOPLE_DATA *occupants = w->district[i][j].first_person->next;

	while ( occupants )
	{
		printf( "%d ", occupants->pin );
		mArray[++i] = occupants->pin;
		( *length )++;
		occupants = occupants->next;
	}
	return mArray;
}

int world_district_pop( WORLD_DATA * w, int i, int j )
{
	if ( i >= w->nrows || j >= w->ncols )
		return 0;

	return w->district[i][j].district_population;
}

int world_total_pop( WORLD_DATA * w )
{
	return w->world_population;
}

int world_move( WORLD_DATA * w, int pin, int i, int j )
{
	if ( pin < 0 || pin > w->world_population || i < w->nrows || j < w->ncols )
		return 0;

	int cx = w->people[pin].x_cord;
	int cy = w->people[pin].y_cord;

	PEOPLE_DATA *person = w->people[pin].prev;
//	PEOPLE_DATA *person = w->people[]

	// unlink code
	DELETE_DLL( person, person[pin].next );

	// change population sizes accordinly
	w->district[cx][cy].district_population--;
	w->district[i][j].district_population++;

	// assign new coordinates to the citizen
	w->people[pin].x_cord = i;
	w->people[pin].y_cord = j;
	return 1;
}

int world_find( WORLD_DATA * w, int pin, int *r, int *c )
{
	// if check is not correct
	if ( w->people[pin].pin )
	{
		*r = w->people[pin].x_cord;
		*c = w->people[pin].y_cord;
		return 1;
	}
	return 0;
}

int world_kill( WORLD_DATA * w, int pin )
{
	// not fully finished; need more checks
	if ( pin < 0 || pin > w->world_population )
		return 0;

	int x = w->people[pin].x_cord;
	int y = w->people[pin].y_cord;

	PEOPLE_DATA *person = w->people[pin].prev;
//	PEOPLE_DATA *person = w->people[]

	// unlink code
	DELETE_DLL( person, person[pin].next );

	w->district[x][y].district_population--;
	w->people[pin].next = NULL;
	w->people[pin].prev = NULL;
	w->world_population--;
	return 1;
}

int world_create( WORLD_DATA * w, int i, int j )
{
//	if ( x < 0 || x >= x_size || y < 0 || y >= y_size )

	if ( i > w->nrows || j > w->ncols || i < 0 || j < 0 )
		return -1;

//  if ( w->deadpool )
//      pin = getID();
	else
	{
		PEOPLE_DATA *reborn = NULL;

		CREATE( reborn, PEOPLE_DATA, 1 );
//      reborn[]
	}
	return 0;
}

void world_delete( WORLD_DATA * w )
{

	return;
}
