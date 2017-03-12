#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "flist.h"
#include "flheap.h"

flnode_t * fl_init( void * ptr, size_t heap_size ) {
    flnode_t * node = ptr;
    node->next = NULL;
    node->size = heap_size;
    return node;
}

flnode_t * fl_insert_new_node( flnode_t * oldnode, size_t memsize, size_t oldsize ) {
    void * newnodeloc = ( void * ) oldnode + memsize;
    flnode_t * newnode = newnodeloc;
    if ( oldsize - memsize <= sizeof( flnode_t ) && oldnode->next != NULL ) {
        return oldnode->next;
    }
    newnode->next = oldnode->next;
    newnode->size = oldsize - memsize;
    return newnode;
}

flnode_t * fl_get_next_free( flnode_t * head, size_t n ) {
    flnode_t * tmp;
    for ( tmp = head; tmp->size < n + sizeof( memobj_t ) && tmp->next != NULL; tmp = tmp->next );
    if ( tmp->next == NULL ) {
        if ( tmp->size < n + sizeof( memobj_t ) ) {
            return NULL;
        }
    }
    return tmp;
}

memobj_t * fl_allocate_at_node( flnode_t * node, size_t n ) {
    if ( node == NULL ) {
        return NULL;
    }
    memobj_t * obj = ( memobj_t * ) node;
    obj->allocated = n + sizeof( memobj_t );
    return obj;
}

void fl_unlink_node( flnode_t * target, flnode_t * head, flnode_t * next ) {
    for ( ; head != NULL && head->next != target; head = head->next );
    if ( head == NULL ) {
        printf( "something very very bad happened and things are definitely broken. good luck.\n" );
    }
    head->next = next;
}

memobj_t * fl_get_block_memobj( void * ptr ) {
    void * memobj_loc = ptr - sizeof( memobj_t );
    return ( memobj_t * ) memobj_loc;
}

int fl_merge_contiguous_blocks( flnode_t * node ) {
    //printf( "debug fl_merge_contiguous_blocks\n" );
    //fl_debug_print();
    int merged = 0;
    for ( ; node != NULL; node = node->next ) {
        uintptr_t nodeloc = ( uintptr_t ) node;
        uintptr_t nextloc = ( uintptr_t ) node->next;
        if ( nodeloc + node->size <= nextloc && nodeloc + node->size > nextloc - sizeof( memobj_t ) ) {
            size_t fragment = nextloc - ( nodeloc + node->size );
            node->size = node->size + node->next->size + fragment;
            node->next = node->next->next;
            merged = 1;
        }
    }
    //fl_debug_print();
    return merged;
}
