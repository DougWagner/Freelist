#ifndef FLHEAP_H
#define FLHEAP_H

void fl_install_heap( size_t );
void fl_uninstall_heap( void );

void * fl_malloc( size_t );
void * fl_malloc_p( size_t ); // fl_malloc that prints return value (only exists because I don't want to run the ternary expression in fl_malloc's return statement twice)
void fl_free( void * );

void fl_debug_print( void );

#endif