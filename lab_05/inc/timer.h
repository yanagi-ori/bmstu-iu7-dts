//
// Created by Ivan Bogatyrev on 1/27/2021.
//

#ifndef LAB_05_TIMER_H
#define LAB_05_TIMER_H

uint64_t tick(void);

#define START_MEASURING() clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time_s);
#define END_MEASURING() clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time_s);

#define SHOW_TIME(msg) printf (msg "%lds %ld ns\n", end_time_s.tv_sec - start_time_s.tv_sec, labs(end_time_s.tv_nsec \
- start_time_s.tv_nsec))

#endif //LAB_05_TIMER_H
