// this file is also for you dean
#include <stdio.h>
#include <stdlib.h>

#include "fltest.h"
#include "flist.h"

// The only two functions you will need to use in the tests are fl_malloc and fl_free.
// Those functions will do all free list manipulations.
// Declarations found in flheap.h are as follows:
// void * fl_malloc( size_t size );
// void fl_free( void );

#define NUM_POINTERS_STORED 8192

int run_tests( void )
{
    void ** _pointers_stored = (void**)malloc( sizeof(void*)*NUM_POINTERS_STORED );

    for( i = 0; i < NUM_POINTERS_STORED; ++i )
    {
        _pointers_stored[i] = NULL;
    }

    // same size worst case
    if( 1 )
    {
        size_t i = 0;
        for( i = 0; i < NUM_POINTERS_STORED; ++i )
        {
            _pointers_stored[i] = fl_malloc( (1024*1024) / NUM_POINTERS_STORED - sizeof( memobj_t ) ); // (1024*1024) is the 1MB magic number
        }


        for( i = NUM_POINTERS_STORED - 1; i < NUM_POINTERS_STORED; ++i ) // uses unsigned integer rollover to stop, may break if size_t is signed.
        {
            fl_free( _pointers_stored[i] );
            _pointers_stored[i] = NULL;
        }
    }


    // random size allocation and random order deallocations
    if( 1 )
    {
        size_t numallocatons = 0;
        size_t i = 0;
        for( i = 0; i < 512; ++i )
        {
            _pointers_stored[numallocatons++] = fl_malloc( rand() % 1024 ); // random size is capped at 1024
        }

        // randomize the allocations order
        i = 0;
        while( i < 1024 )
        {
            size_t a = rand()%numallocatons;
            size_t b = rand()%numallocatons;
            void * tmp = _pointers_stored[a];
            _pointers_stored[a] = _pointers_stored[b];
            _pointers_stored[b] = tmp;
            ++i;
        }

        for( i = 0; i < numallocatons; ++i ) // uses unsigned integer rollover to stop, may break if size_t is signed.
        {
            fl_free( _pointers_stored[i] );
            _pointers_stored[i] = NULL;
        }
    }

    // rolling size increase allocation
    if( 1 )
    {
        size_t current_size = 1;

        size_t numallocatons = 0;
        size_t i = 0;

        for( i = 0; i < 12; ++i ) // NOTE: if this number is greater than 12 your code hangs.
        {
            if( _pointers_stored[numallocatons%2] != NULL )
            {
                fl_free( _pointers_stored[numallocatons%2] );

                _pointers_stored[numallocatons%2] = NULL;
            }

            _pointers_stored[numallocatons%2] = fl_malloc( current_size++ ); // random size is capped at 1024

            ++numallocatons;
        }

        for( i = 0; i < NUM_POINTERS_STORED; ++i ) // uses unsigned integer rollover to stop, may break if size_t is signed.
        {
            if( _pointers_stored[i] == NULL )
            {
                continue;
            }
            fl_free( _pointers_stored[i] );
            _pointers_stored[i] = NULL;
        }

    }

    size_t i = 0;
    for( i = 0; i < NUM_POINTERS_STORED; ++i )
    {
        if( _pointers_stored[i] == NULL )
        {
            continue;
        }
        fl_free( _pointers_stored[i] );
        _pointers_stored[i] = NULL;
    }

    free( _pointers_stored );

    return 1;
}
