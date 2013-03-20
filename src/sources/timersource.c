#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "timersource.h"

unsigned counter = 0;
unsigned char bit_count = 0;
unsigned char random_bits = 0;
unsigned bytes_out = 0;

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
    FILE* fp = fopen("binary_output.dat", "w");
    size_t bytes_to_count = (size_t)data;
    while (running) {
        usleep(1);
        random_bits = (random_bits << 1) + lowest_bit(counter);
        bit_count++;
        if (bit_count == 8) {
            printf("%X", random_bits);
            fprintf(fp, "%c", random_bits);
            random_bits = 0;
            bit_count = 0;
            if (++bytes_out == bytes_to_count) {
                running = false;
            }
        }
    }
    fclose(fp);
    return NULL;
}

void start_counter_thread(pthread_t* thread) {
    pthread_create(thread, NULL, counter_thread_function, NULL);
}

void start_timer_thread(pthread_t* thread, size_t bytes_to_count) {
    pthread_create(thread, NULL, timer_thread_function, (void*)bytes_to_count);
}
