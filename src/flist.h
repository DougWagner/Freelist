#ifndef FLIST_H
#define FLIST_H

typedef struct _flist_node { // free list node
    size_t size;
    struct _flist_node * next;
} flnode_t;

typedef struct _memobj_header { // allocated memory header
    size_t allocated;
    void * blank;
} memobj_t;

flnode_t * fl_init( void * , size_t );
flnode_t * fl_insert_new_node( flnode_t * , size_t, size_t );
flnode_t * fl_get_next_free( flnode_t * , size_t );
memobj_t * fl_allocate_at_node( flnode_t * , size_t );
void fl_unlink_node( flnode_t * , flnode_t * , flnode_t * );
memobj_t * fl_get_block_memobj( void * );
void fl_merge_contiguous_blocks( flnode_t * );

#endif