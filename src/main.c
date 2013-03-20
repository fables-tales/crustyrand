#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sources/timersource.h"
int main(int argc, char** argv) {
    size_t bytes_to_count = 1024*10;
    if (argc == 2) {
        bytes_to_count = atoi(argv[1])*1024;
    }
    pthread_t counter_thread, timer_thread;
    running = true;

    start_counter_thread(&counter_thread);
    start_timer_thread(&timer_thread, bytes_to_count);
    pthread_join(timer_thread, NULL);
    pthread_join(counter_thread, NULL);

    return 0;
}
