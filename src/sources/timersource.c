#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "timersource.h"
#include "../entropy_pool.h"

#define lowest_bit(X) (X & 1)

unsigned counter = 0;
int tug_of_war_counter = 0;
bool running = true;
pthread_t counter_thread;
pthread_t tug_of_war_up_thread, tug_of_war_down_thread;
pthread_t timer_thread;

void* tug_of_war_up_thread_function(void* data) {
    (void)data;
    while (running) {
        tug_of_war_counter++;
    }
    return &counter;
}

void* tug_of_war_down_thread_function(void* data) {
    (void)data;
    while (running) {
        tug_of_war_counter--;
    }
    return &counter;
}

void* counter_thread_function(void* data) {
    (void)data;
    while (running) {
        counter++;
    }

    return &counter;
}

void* timer_thread_function(void* data) {
    (void)data;
    while (running) {
        usleep(1);
        entropy_pool* p = get_global_entropy_pool();
        entropy_pool_insert_bit(p, lowest_bit(counter));
        entropy_pool_insert_bit(p, lowest_bit((unsigned)clock()));
        entropy_pool_insert_bit(p, lowest_bit(tug_of_war_counter));
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

void start_tug_of_war_threads() {
    pthread_create(&tug_of_war_up_thread, NULL, tug_of_war_up_thread_function, NULL);
    pthread_create(&tug_of_war_down_thread, NULL, tug_of_war_down_thread_function, NULL);
}

void start_timer_source() {
    start_counter_thread(&counter_thread);
    start_tug_of_war_threads();
    start_timer_thread(&timer_thread);
}

void wait_for_timer_source() {
    pthread_join(timer_thread, NULL);
    pthread_join(counter_thread, NULL);
    pthread_join(tug_of_war_up_thread, NULL);
    pthread_join(tug_of_war_down_thread, NULL);
}
