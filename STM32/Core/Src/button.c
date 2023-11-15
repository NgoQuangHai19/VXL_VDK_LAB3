#include "button.h"


int KeyReg0[NUMBER_BUTTON] = {NORMAL_STATE,NORMAL_STATE,NORMAL_STATE};
int KeyReg1[NUMBER_BUTTON] = {NORMAL_STATE,NORMAL_STATE,NORMAL_STATE};
int KeyReg2[NUMBER_BUTTON] = {NORMAL_STATE,NORMAL_STATE,NORMAL_STATE};
int KeyReg3[NUMBER_BUTTON] = {NORMAL_STATE,NORMAL_STATE,NORMAL_STATE};

int TimerForKeyPress[NUMBER_BUTTON] =  {100,100,100};
int button_flag[NUMBER_BUTTON] =  {0,0,0};
int button_pressed_1s_flag[NUMBER_BUTTON] =  {0,0,0};

void subKeyProcess(int i){
	button_flag[i] = 1;
}
void getKeyInput(){
	for(int i = 0; i < NUMBER_BUTTON; i++){
			KeyReg0[i] = KeyReg1[i];
			KeyReg1[i] = KeyReg2[i];
			if(i==0) KeyReg2[i] = HAL_GPIO_ReadPin(SELECT_GPIO_Port, SELECT_Pin);
			if(i==1) KeyReg2[i] = HAL_GPIO_ReadPin(MODIFY_GPIO_Port, MODIFY_Pin);
			if(i==2) KeyReg2[i] = HAL_GPIO_ReadPin(SET_GPIO_Port, SET_Pin);
			if((KeyReg0[i] == KeyReg1[i]) && (KeyReg1[i] == KeyReg2[i]))
			{
				if(KeyReg3[i] != KeyReg2[i])
				{
					KeyReg3[i] = KeyReg2[i];
					if(KeyReg2[i] == PRESSED_STATE){
						subKeyProcess(i);
						TimerForKeyPress[i] = 100;
					}
					else button_pressed_1s_flag[i]=0;
				}

				else
				{
					TimerForKeyPress[i]--;
					if(TimerForKeyPress[i] == 0){
						if(KeyReg2[i] == PRESSED_STATE) {
							button_pressed_1s_flag[i]=1;
						}
						else {
							button_pressed_1s_flag[i]=0;
						}
						TimerForKeyPress[i]=100;
					}
				}
			}
	}



}
