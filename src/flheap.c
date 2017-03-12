#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "flheap.h"
#include "flist.h"

static void * flheap;
static flnode_t * head;
static int debug;

void fl_install_heap( size_t heapsize, int debug_state ) {
    debug = debug_state;
    flheap = malloc( heapsize );
    head = fl_init( flheap, heapsize );
    printf( "flheap installed at %p\n\n", flheap );
}

void fl_uninstall_heap( void ) {
    free( flheap );
}

void * fl_malloc( size_t size ) {
    if ( debug ) printf( "the size requested is 0x%lx\n", size );
    if ( size == 0 ) {
        return NULL;
    }
    flnode_t * tmp = fl_get_next_free( head, size );
    size_t extra = 0;
    if ( debug ) printf( "fl_get_next_free returned flnode_t at %p\n", tmp );
    if ( tmp != NULL ) {
        size_t memsize = sizeof( memobj_t ) + size;
        size_t oldsize = tmp->size;
        if ( tmp == head ) { // block found at head
            if ( head->next == NULL || head->size >= oldsize - memsize ) {
                head = fl_insert_new_node( head, memsize, oldsize );
            }
            else {
                head = head->next;
            }
            if ( debug ) printf( "head moved to %p\n", head );
        }
        else if ( tmp->next == NULL ) { // block found at list end
            flnode_t * newnode = fl_insert_new_node( tmp, memsize, oldsize );
            fl_unlink_node( tmp, head, newnode );
        }
        else { // block found in middle of list
            if ( memsize == tmp->size || memsize + sizeof( flnode_t ) > tmp->size ) {
                // holy crap we found an exact match :O
                fl_unlink_node( tmp, head, tmp->next );
            }
            else {
                flnode_t * newnode = fl_insert_new_node( tmp, memsize, oldsize );
                fl_unlink_node( tmp, head, newnode );
            }
        }
        if ( oldsize - memsize <= sizeof( flnode_t ) && tmp->next->next != NULL ) {
            extra = oldsize - memsize;
        }
        if ( debug ) printf( "total memory allocated is 0x%lx\n", memsize + extra );
    }
    memobj_t * obj = fl_allocate_at_node( tmp, size + extra );
    if ( debug ) printf( "memory object allocated at %p\n\n", obj );
    if ( debug ) fl_debug_print();
    return obj != NULL ? ( void * ) obj + sizeof( memobj_t ) : NULL;
}

void * fl_malloc_p( size_t size ) {
    void * ptr = fl_malloc( size );
    printf( "fl_malloc returned pointer to %p\n\n", ptr );
    return ptr;
}

void * fl_calloc( size_t nmemb, size_t size ) {
    void * ptr = fl_malloc( nmemb * size );
    if ( ptr != NULL ) {
        memset( ptr, 0, nmemb * size );
    }
    return ptr;
}

void * fl_calloc_p( size_t nmemb, size_t size ) {
    void * ptr = fl_calloc( nmemb, size );
    printf( "fl_calloc returned pointer to %p\n\n", ptr );
    return ptr;
}

void fl_free( void * ptr ) {
    if ( debug ) printf( "pointer to free: %p\n", ptr );
    uintptr_t ptr_loc = ( uintptr_t ) ptr;
    flnode_t * node;
    for ( node = head; node->next != NULL && ptr_loc > ( uintptr_t ) node->next; node = node->next ); // loop to last node before ptr_loc
    if ( debug ) printf( "node found at %p\n", node );
    memobj_t * obj = fl_get_block_memobj( ptr );
    flnode_t * freenode = ( flnode_t * ) obj; // obj->allocated should be in the same memory location as freenode->size
    if ( ptr_loc < ( uintptr_t ) head ) { // block to free is before head
        freenode->next = head;
        head = freenode;
        if ( debug ) printf( "head moved to %p\n", head );
    }
    else {
        freenode->next = node->next;
        node->next = freenode;
        if ( debug ) printf( "freenode inserted at %p\n", freenode );
    }
    if ( debug ) printf( "checking for contiguous blocks and returning\n\n" );
    //if ( debug ) fl_debug_print();
    while ( fl_merge_contiguous_blocks( head ) );
    if ( debug ) fl_debug_print();
}

void fl_debug_print( void ) {
    printf("printing list\n");
    flnode_t * tmp = head;
    for ( size_t i = 0; tmp != NULL; i++, tmp = tmp->next ) {
        char * node = ( i == 0 ) ? "head" : "node";
        printf("%s: %p - %s->size: %lx - %s->next: %p - %s + %s->size = %p \n", node, tmp, node, tmp->size, node, tmp->next, node, node, ( void * ) tmp + tmp->size );
    }
    printf("\n");
}
