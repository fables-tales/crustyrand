
#ifndef _timer_source_h_
#define _timer_source_h_
#include <pthread.h>
void start_counter_thread(pthread_t* thread);
void start_timer_thread(pthread_t* thread, size_t bytes_to_count);
int running;
#endif
