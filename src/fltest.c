// this file is also for you dean
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    srand( time( NULL ) );
    void ** _pointers_stored = (void**)malloc( sizeof(void*)*NUM_POINTERS_STORED );

    size_t i = 0;
    for( i = 0; i < NUM_POINTERS_STORED; ++i )
    {
        _pointers_stored[i] = NULL;
    }

    // same size worst case
    if( 1 )
    {
        printf( "same size worst case\n" );
        getchar();
        size_t i = 0;
        for( i = 0; i < NUM_POINTERS_STORED; ++i )
        {
            _pointers_stored[i] = fl_malloc( (1024*1024) / NUM_POINTERS_STORED - sizeof( memobj_t ) ); // (1024*1024) is the 1MB magic number
        }


        for( i = NUM_POINTERS_STORED - 1; i < NUM_POINTERS_STORED; --i ) // uses unsigned integer rollover to stop, may break if size_t is signed.
        //for( i = 0; i < NUM_POINTERS_STORED; i++ ) // either loop works
        {
            fl_free( _pointers_stored[i] );
            _pointers_stored[i] = NULL;
        }
        fl_debug_print();
    }

    // random size allocation and random order deallocations
    if( 1 )
    {
        printf( "random size allocation and deallocation\n" );
        getchar();
        size_t numallocatons = 0;
        size_t i = 0;
        for( i = 0; i < 2048; ++i )
        {
            _pointers_stored[numallocatons++] = fl_malloc( rand() % 512 + 1 ); // random size is capped at 1024
        }

        // randomize the allocations order
        i = 0;
        while( i < 8192 )
        {
            size_t a = rand()%numallocatons;
            size_t b = rand()%numallocatons;
            void * tmp = _pointers_stored[a];
            _pointers_stored[a] = _pointers_stored[b];
            _pointers_stored[b] = tmp;
            ++i;
        }

        for( i = 0; i < numallocatons; ++i ) 
        {
            if ( rand() % 2 == 0 && numallocatons < NUM_POINTERS_STORED ) { // dice roll
                _pointers_stored[numallocatons] = fl_malloc( rand() % 512 + 1 ); 
                size_t a = numallocatons;
                size_t b = rand() % ( numallocatons - i );
                void * tmp = _pointers_stored[a];
                _pointers_stored[a] = _pointers_stored[i + b];
                _pointers_stored[i + b] = tmp;
                numallocatons++;
            }
            printf( "number deallocated: %lu\n", i );
            fl_free( _pointers_stored[i] );
            _pointers_stored[i] = NULL;
            /*if ( i % 100 == 0 ) {
                fl_debug_print();
            }*/
        }
        fl_debug_print();
        printf( "total allocated: %lu\n", numallocatons );
        printf( "total deallocated: %lu\n", i );
    }

    // same size random allocation and deallocation
    if ( 1 )
    {
        printf( "same size random allocation and deallocation\n" );
        getchar();
        size_t numallocatons = 0;
        size_t i = 0;
        for( i = 0; i < 2048 ; ++i )
        {
            _pointers_stored[numallocatons++] = fl_malloc( 0x80 ); // random size is capped at 1024
        }

        // randomize the allocations order
        i = 0;
        while( i < 8192 )
        {
            size_t a = rand()%numallocatons;
            size_t b = rand()%numallocatons;
            void * tmp = _pointers_stored[a];
            _pointers_stored[a] = _pointers_stored[b];
            _pointers_stored[b] = tmp;
            ++i;
        }

        for( i = 0; i < numallocatons; ++i ) 
        {
            if ( rand() % 2 == 0 && numallocatons < NUM_POINTERS_STORED ) { // dice roll
                _pointers_stored[numallocatons] = fl_malloc( 0x80 ); 
                size_t a = numallocatons;
                size_t b = rand() % ( numallocatons - i );
                void * tmp = _pointers_stored[a];
                _pointers_stored[a] = _pointers_stored[i + b];
                _pointers_stored[i + b] = tmp;
                numallocatons++;
            }
            printf( "number deallocated: %lu\n", i );
            fl_free( _pointers_stored[i] );
            _pointers_stored[i] = NULL;
            /*if ( i % 100 == 0 ) {
                fl_debug_print();
            }*/
        }
        fl_debug_print();
        printf( "total allocated: %lu\n", numallocatons );
        printf( "total deallocated: %lu\n", i );
    }

    // rolling size increase allocation
    if( 1 )
    {
        printf( "rolling size increase allocation\n" );
        getchar();
        size_t current_size = 1;

        size_t numallocatons = 0;
        size_t i = 0;

        for( i = 0; i < 0x3fff; ++i )
        {
            if( _pointers_stored[numallocatons%2] != NULL )
            {
                fl_free( _pointers_stored[numallocatons%2] );

                _pointers_stored[numallocatons%2] = NULL;
            }

            _pointers_stored[numallocatons%2] = fl_malloc( current_size++ );

            ++numallocatons;
        }

        for( i = 0; i < NUM_POINTERS_STORED; ++i ) 
        {
            if( _pointers_stored[i] == NULL )
            {
                continue;
            }
            fl_free( _pointers_stored[i] );
            _pointers_stored[i] = NULL;
        }

        fl_debug_print();
    }

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
