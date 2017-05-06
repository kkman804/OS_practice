//
//  practice_cond.c
//  os_practice
//
//  Created by kk on 2017/5/6.
//  Copyright © 2017年 kk. All rights reserved.
//

#include "Header.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t cond_mutex;
pthread_cond_t cond;
/*** other describe ***/
// pthread_mutex_t cond_mutex = PTHREAD_MUTEX_INITIALIZER;
// pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int count = 0;
#define COUNT_DONE 10
#define COUNT_HALT1 3
#define COUNT_HALT2 6

void* function_cond1(void*);
void* function_cond2(void*);
void practice_cond();

void practice_cond() {
    pthread_t thread1,thread2;
    
    pthread_mutex_init(&cond_mutex, NULL);
    pthread_cond_init(&cond,NULL);
    
    pthread_create(&thread1, NULL, function_cond1, (void*)1);
    pthread_create(&thread2, NULL, function_cond2, (void*)2);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("Final count:%d\n",count);
}

void* function_cond1(void *msg){
    for(;;) {
        printf("functionCount1 receive\n");
        pthread_mutex_lock(&cond_mutex);
        pthread_cond_wait(&cond,&cond_mutex); //wait for received pthread_cond_signal
        count++;
        printf("Counter value functionCount1: %d\n",count);
        pthread_mutex_unlock(&cond_mutex);
        if(count>=COUNT_DONE) return NULL;
    }
}

void* function_cond2(void *msg){
    for(;;) {
        printf("functionCount2 receive\n");
        pthread_mutex_lock(&cond_mutex);
        // 3 6
        if(count <COUNT_HALT1 || count >COUNT_HALT2) {
            pthread_cond_signal(&cond);
        } else {
            count++;
            printf("Counter value functionCount2: %d\n",count);
        }
        pthread_mutex_unlock(&cond_mutex);
        if(count>=COUNT_DONE) return NULL;
    }
}
