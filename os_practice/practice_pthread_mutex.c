//
//  practice_pthread_mutex.c
//  os_practice
//
//  Created by kk on 2017/5/6.
//  Copyright © 2017年 kk. All rights reserved.
//

#include "Header.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function(void*);
int run_row=1;
pthread_mutex_t test_mutex;

void practice_mutex(){
    int result;
    pthread_t a_thread[4];
    
    pthread_mutex_init(&test_mutex, NULL);
    
    for (long i = 0 ; i < NUM_THREADS; i++) {
        printf("In main: creating thread %ld\n",i);
        result = pthread_create(&a_thread[i], NULL, thread_function ,(void*)i);
        if (result) {
            printf("ERROR: return code from pthread_create() is %d\n",result);
            exit(-1);
        }
    }
    
    for(long i = 0 ; i < NUM_THREADS;i++) {
        pthread_join(a_thread[i], NULL);
    }
    pthread_mutex_destroy(&test_mutex);
}

void *thread_function(void*arg)
{
    long tid = (long)arg;
    printf("Start====>In thread #%ld number:%d\n",tid,run_row);
    while(run_row <20) {
        pthread_mutex_lock(&test_mutex);
        printf("In thread #%ld number:%d\n",tid,run_row);
        run_row +=3;
        pthread_mutex_unlock(&test_mutex);
        sleep(1);
    }
    
    pthread_exit(NULL);
}
