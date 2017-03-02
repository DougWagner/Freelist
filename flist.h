#ifndef FLIST_H
#define FLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _flist_node { // free list node
    struct _flist_node * next;
    size_t size;
} flnode_t;

flnode_t * flist_init( void * , size_t );


#endif