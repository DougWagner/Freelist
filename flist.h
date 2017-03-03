#ifndef FLIST_H
#define FLIST_H

typedef struct _flist_node { // free list node
    struct _flist_node * next;
    size_t size;
} flnode_t;

typedef struct _memobj_header {
    size_t allocated;
} memhdr_t;

flnode_t * fl_init( void * , size_t );

#endif