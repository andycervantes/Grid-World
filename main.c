// andy cervantes


#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "gw.h"

int main( int argc, char **argv )
{
//	char *input;
//	int ch;
//	int i;

	srand( time( NULL ) );
	WORLD_DATA *new_world = world_build( 10, 10, 10, 0 );
	int num = world_district_pop( new_world, 0, 0 );
	printf("%d\n", num);
	int num2 = world_total_pop( new_world );
	printf("%d\n", num2);

/*
	printf( "Starting Grid World Program\n" );
	printf( "Enter Command: " );

	while ( ( ch = getNextNWSChar(  ) ) != EOF )
	{
		// Check for the various commands
		if ( 'q' == ch )
		{
			printf( "Quitting Program\n" );
			return ( 0 );
		}
		else if ( 'a' == ch )
		{
			doAdd( head );
		}
		else if ( 'c' == ch )
		{
			doCallAhead( head );
		}
		else if ( 'w' == ch )
		{
			doWaiting( head );
		}
		else if ( 'r' == ch )
		{
			doRetrieve( head );
		}
		else if ( 'l' == ch )
		{
			doList( head );
		}
		else if ( 'd' == ch )
		{
			doDisplay( head );
		}
		else
		{
			printf( "'%c' is not a valid command.\n", ch );
			printf( "For a list of valid commands, type '?'.\n" );
			clearToEoln(  );
		}
		printf( "\nEnter Command: " );
	}
	*/
	printf( "Quitting Program - EOF Reached.\n" );
	return 1;
}
/*
// Read in until the first non-white-space character is read
// The white space characters are: space, tab \t, newline \n, vertical tab \v, form feed \f, and carrigsize return \r
int getNextNWSChar(  )
{
	int ch;

	ch = getc( stdin );
	if ( ch == EOF )
		return ch;

	while ( isspace( ch ) )
	{
		ch = getc( stdin );
		if ( ch == EOF )
			return ch;
	}
	return ch;
}*/
