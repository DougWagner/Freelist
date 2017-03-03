#ifndef FLHEAP_H
#define FLHEAP_H

void fl_install_heap( size_t );
void fl_uninstall_heap( void );

void * fl_malloc( size_t );
void fl_free( void * );

#endif