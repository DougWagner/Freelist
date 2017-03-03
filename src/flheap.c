#include <stdio.h>
#include <stdlib.h>

#include "flheap.h"
#include "flist.h"

static void * flheap;
static flnode_t * head;

void fl_install_heap( size_t heapsize ) {
    flheap = malloc( heapsize );
    head = fl_init( flheap, heapsize );
    printf( "flheap installed at %p\n", flheap );
}

void fl_uninstall_heap( void ) {
    free( flheap );
}

void * fl_malloc( size_t size ) {
    flnode_t * tmp = fl_get_next_free( head, size );
    printf( "fl_get_next_free returned flnode_t at %p\n", tmp );
    if ( tmp != NULL ) {
        size_t memsize = sizeof( memobj_t ) + size;
        size_t oldsize = tmp->size;
        if ( tmp == head ) { // block found at head
            if ( head->next == NULL ) {
                void * newhead = ( void * ) head + memsize;
                head = newhead;
                head->next = NULL;
                head->size = oldsize - memsize;
            }
            else {
                head = head->next;
            }
            printf( "head moved to %p\n", head );
        }
        else if ( tmp->next == NULL ) { // block found at list end
            void * newnodeloc = ( void * ) tmp + memsize;
            flnode_t * newnode = newnodeloc;
            newnode->next = NULL;
            newnode->size = oldsize - memsize;
            fl_unlink_node( tmp, head, newnode );
        }
        else { // block found in middle of list
            if ( memsize == tmp->size || memsize + sizeof( flnode_t ) > tmp->size ) {
                // holy crap we found an exact match :O
                fl_unlink_node( tmp, head, tmp->next );
            }
            else {
                void * newnodeloc = ( void * ) tmp + memsize;
                flnode_t * newnode = newnodeloc;
                newnode->next = tmp->next;
                newnode->size = oldsize - memsize;
                fl_unlink_node( tmp, head, newnode );
            }
        }
    }
    memobj_t * obj = fl_allocate_at_node( tmp, size );
    printf( "memory allocated at %p\n", obj );
    return obj != NULL ? ( void * ) obj + sizeof( memobj_t ) : NULL;
}

void fl_free( void * ptr ) {

}