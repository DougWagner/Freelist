#include <stdio.h>
#include <stdlib.h>

#include "flheap.h"
#include "fltest.h"

#define HEAP_SIZE 0x100000 // 1 MiB (update comment if you change HEAP_SIZE)

int main() {
    fl_install_heap( HEAP_SIZE );
    void * ptr1 = fl_malloc( 20 );
    printf( "fl_malloc returned pointer to %p\n", ptr1 );
    void * ptr2 = fl_malloc( 50 );
    printf( "fl_malloc returned pointer to %p\n", ptr2 );
    void * ptr3 = fl_malloc( 400 );
    printf( "fl_malloc returned pointer to %p\n", ptr3 );
    void * ptr4 = fl_malloc( 80 );
    printf( "fl_malloc returned pointer to %p\n", ptr4 );
    void * ptr5 = fl_malloc( 27 );
    printf( "fl_malloc returned pointer to %p\n", ptr5 );
    void * ptr6 = fl_malloc( 245 );
    printf( "fl_malloc returned pointer to %p\n", ptr6 );
    void * ptr7 = fl_malloc( 63187 );
    printf( "fl_malloc returned pointer to %p\n", ptr7 );
    void * ptr = fl_malloc( 818374758347 );
    //run_tests();
    fl_uninstall_heap();
    return 0;
}