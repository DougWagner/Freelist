#include <stdio.h>
#include <stdlib.h>

#include "flheap.h"
#include "fltest.h"

#define HEAP_SIZE 0x100000 // 1 MiB (update comment if you change HEAP_SIZE)

int main() {
    fl_install_heap( HEAP_SIZE );
    size_t allocations[10] = { 20, 50, 400, 80, 128, 256, 88, 4096, 1181, 512 };
    void * ptrs[10];
    for ( size_t i = 0; i < 10; i++ ) {
        ptrs[i] = fl_malloc_p( allocations[i] );
    }

    fl_free( ptrs[7] );
    fl_free( ptrs[4] );
    fl_free( ptrs[0] );
    fl_debug_print();

    void * newptr1 = fl_malloc_p( 200 );
    fl_debug_print();
    void * newptr2 = fl_malloc_p( 128 );
    fl_debug_print();
    void * newptr3 = fl_malloc_p( 10 );
    fl_debug_print();
    void * newptr4 = fl_malloc_p( 10 );
    fl_debug_print();

    run_tests();
    fl_uninstall_heap();
    return 0;
}