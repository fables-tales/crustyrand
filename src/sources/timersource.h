
#ifndef _timer_source_h_
#define _timer_source_h_
#include <pthread.h>
void start_counter_thread(pthread_t* thread);
void start_timer_thread(pthread_t* thread);
#endif
