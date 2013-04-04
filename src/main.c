#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "sources/timersource.h"
#include "entropy_pool.h"

int main(int argc, char** argv) {
    size_t bits_to_count = 1024*10;

    if (argc == 2) {
        bits_to_count = atoi(argv[1])*1024;
    }

    entropy_pool* pool = get_global_entropy_pool();
    entropy_pool_set_capacity(pool, bits_to_count);

    unsigned long start = time(NULL);

    start_timer_source();
    wait_for_timer_source();

    unsigned long end = time(NULL);

    printf("acquired %u bits in %lu seconds, %f bits per second\n", (unsigned)bits_to_count, end-start, (bits_to_count*1.0)/(end-start));

    entropy_pool_dump_to_file(pool, "binary_dump");


    return 0;
}
