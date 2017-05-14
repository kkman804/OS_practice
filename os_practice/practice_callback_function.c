//
//  practice_callback_function.c
//  os_practice
//
//  Created by kk on 2017/5/13.
//  Copyright © 2017年 kk. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>

typedef struct{
    uint8_t time;
    void (*bsp_callback)(void);
} Display_info_struct;

static Display_info_struct DisplayInfo;
void practice_callback_func();
void showHelloWorld();
void bsp_show(uint8_t ,void (*callback)(void));




void showHelloWorld(){
    printf("Hello world.\n");
}
void practice_callback_func(){
    bsp_show(10, showHelloWorld);
}

void bsp_show(uint8_t time,void (*callback)(void)){
    DisplayInfo.time = time;
    DisplayInfo.bsp_callback = callback;
    
    while (DisplayInfo.time >0) {
        --DisplayInfo.time;
        if(DisplayInfo.time ==0){
            //call callback function
            if(DisplayInfo.bsp_callback) {
                DisplayInfo.bsp_callback();
            }
            //clean callback function
            DisplayInfo.bsp_callback = 0;
        }
        sleep(1);
    }
}
