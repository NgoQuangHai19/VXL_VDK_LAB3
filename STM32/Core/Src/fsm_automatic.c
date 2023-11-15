/*
 * fsm_automatic.c
 *
 *  Created on: Nov 13, 2023
 *      Author: AD
 */

#include "fsm_automatic.h"

void fsm_automatic_run(){
	switch(mode){
		case INIT:
			setValueLocalNormalMode();
			mode=NORMAL;
			setTimer3(1000);
			break;
		case NORMAL:
			if(timer3_flag==1){
				normalMode();
				setTimer3(500);
			}
			if(button_flag[0]==1 || button_pressed_1s_flag[0]==1){
				button_flag[0]=0;
				clear_all_traffic_led=0;
				mode=RED;
				setTimer3(1000);
			}
			break;
		case RED :
			redMode();
			if(button_flag[0]==1 || button_pressed_1s_flag[0]==1){
				button_flag[0]=0;
				clear_all_traffic_led=0;
				mode=GREEN;
				setTimer3(1000);
			}
			if(button_flag[2]==1 || button_pressed_1s_flag[2]==1){
				button_flag[2]=0;
				setTimeRed();
				mode=INIT;
			}
			break;
		case GREEN:
			greenMode();
			if(button_flag[0]==1 || button_pressed_1s_flag[0]==1){
				button_flag[0]=0;
				clear_all_traffic_led=0;
				mode=YELLOW;
				setTimer3(1000);
			}
			if(button_flag[2]==1|| button_pressed_1s_flag[2]==1){
				button_flag[2]=0;
				setTimeGreen();
				mode=INIT;
			}
			break;
		case YELLOW:
			yellowMode();
			if(button_flag[0]==1 || button_pressed_1s_flag[0]==1){
				button_flag[0]=0;
				clear_all_traffic_led=0;
				mode=INIT;
				setTimer3(1000);
			}
			if(button_flag[2]==1|| button_pressed_1s_flag[2]==1){
				button_flag[2]=0;
				setTimeYellow();
				mode=INIT;
			}
			break;
		default:
			break;
		}
}
