#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "timersource.h"
#include "../entropy_pool.h"

unsigned counter = 0;
bool running = true;

void* counter_thread_function(void* data) {
    (void)data;
    while (running) {
        counter++;
    }

    return &counter;
}

unsigned char lowest_bit(unsigned value) {
    return value & 1;
}

void* timer_thread_function(void* data) {
    (void)data;
    while (running) {
        usleep(1);
        entropy_pool* p = get_global_entropy_pool();
        entropy_pool_insert_bit(p, lowest_bit(counter));
        running = !entropy_pool_is_full(p);
    }
    return NULL;
}

void start_counter_thread(pthread_t* thread) {
    pthread_create(thread, NULL, counter_thread_function, NULL);
}

void start_timer_thread(pthread_t* thread) {
    pthread_create(thread, NULL, timer_thread_function, NULL);
}
