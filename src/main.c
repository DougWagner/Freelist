#include <stdio.h>
#include <stdlib.h>

#include "flheap.h"
#include "fltest.h"

#define HEAP_SIZE 0x100000 // 1 MiB (update comment if you change HEAP_SIZE)
#define DEBUG 1 // 1 for enabled, 0 for disabled

int main() {
    fl_install_heap( HEAP_SIZE, DEBUG );
    run_tests();
    fl_uninstall_heap();
    return 0;
}