//
//  practice_pthread.c
//  os_practice
//
//  Created by kk on 2017/5/6.
//  Copyright © 2017年 kk. All rights reserved.
//


#include "Header.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *printHello(void*);
void *printHi(void*);
void practice_pthread();

void practice_pthread() {
    int result;
    void *res;
    pthread_t threads[NUM_THREADS];
    for(long i = 0; i< NUM_THREADS; i++){
        printf("In main: creating thread %ld\n",i);
        if(i%2 == 0){
            result = pthread_create(&threads[i], NULL, printHello ,(void*)i);
        } else {
            result = pthread_create(&threads[i], NULL, printHi ,(void*)i);
        }
        if (result) {
            printf("ERROR: return code from pthread_create() is %d\n",result);
            exit(-1);
        }
    }
    
    for(long i = 0; i< NUM_THREADS; i++){
        pthread_join(threads[i], &res);
        printf("Thread #%ld return %d\n",i,res);
    }
}
void *printHello(void *threadId){
    long tid = (long) threadId;
    int i=0;
    printf("Start In Thread #%ld\n",tid);
    for (i = 0;i<10;i++){
        printf("Hello In Thread #%ld time=%d\n",tid,i);
        sleep(1);
    }
    pthread_exit((void*)(tid*10));
}
void *printHi(void *threadId){
    long tid = (long) threadId;
    int i=0;
    printf("Start In Thread #%ld\n",tid);
    for (i = 0;i<5;i++){
        printf("Hi    In Thread #%ld time=%d\n",tid,i);
        sleep(1);
    }
    pthread_exit((void*)(tid*10));
}
