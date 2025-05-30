
#include <stdio.h>
#include <string.h>
#include "Bluetooth.h"
#include "motor.h"
#include "stepper.h"

char *demo_string = "Hello, EmbeddedThere\r\n";
uint8_t recv_char;
char receivedCommand;
extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart1;
uint16_t servoPosition = 75;

void init_Bluetooth(void)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)demo_string, strlen(demo_string), 50);
	HAL_UART_Receive_IT(&huart1, &receivedCommand, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
        control_car(receivedCommand);
        HAL_UART_Receive_IT(&huart1, &receivedCommand, 1);
    }
}

void setServoPosition(uint16_t pos) {
    if (pos > 100) pos = 100;
    if (pos < 45) pos = 45;
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pos);
}

void control_car(char command) {
    switch (command) {
        case 'F': forward(); break;
        case 'B': Back(); break;
        case 'L': setServoPosition(servoPosition += 5); break;
        case 'R': setServoPosition(servoPosition -= 5); break;
        case 'S': stop(); break;
        case 'G': forward(); setServoPosition(servoPosition += 5); break;
        case 'I': forward(); setServoPosition(servoPosition -= 5); break;
        case 'H': Back(); setServoPosition(servoPosition += 5); break;
        case 'J': Back(); setServoPosition(servoPosition -= 5); break;
    }
}
































/***************************************************************************************************/

/*

#include <stdio.h>
#include <string.h>
#include "Bluetooth.h"
#include "motor.h"
#include "stepper.h"

char *demo_string = "Hello, EmbeddedThere\r\n"; //demo string
uint8_t recv_char;
uint8_t recv_str[20];


extern TIM_HandleTypeDef htim1;
//extern TIM_HandleTypeDef htim4;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart1;

char receivedCommand;

int init_Bluetooth(void)  //main // @suppress("No return")
{
	HAL_UART_Transmit(&huart2, (uint8_t*)demo_string, strlen(demo_string),50/* HAL_MAX_DELAY*////); //print to any computer serial monitor (use Putty or any serial monitor software for PC)
	///HAL_UART_Receive_IT(&huart1, &recv_char, 1); //UART1 Interrupt call
///}

/*
void start_Bluetooth(void) ///while
{
	if (HAL_UART_Receive(&huart1, (uint8_t *)&receivedCommand, 1, 50/*HAL_MAX_DELAY*////) == HAL_OK) {
/*		control_car(receivedCommand);
	}
}




uint16_t servoPosition = 75; // Start at 90° (neutral position)

void control_car(char command) {
	if (command == 'F') {
		forward();
	}
	else if (command == 'B') {
		Back();
	}
	else if (command == 'L') {
		servoPosition += 5;
		if (servoPosition > 100) {
			servoPosition = 100;
		}
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, servoPosition);
	}
	else if (command == 'R') {
		servoPosition -= 5;
		if (servoPosition < 45) {
			servoPosition = 45;
		}
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, servoPosition);

	}
	else if (command == 'S') {
		stop();
	}
	else if (command == 'G') {
		forward();
		servoPosition += 5;
		if (servoPosition > 100) {
			servoPosition = 100;
		}
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, servoPosition);

	}
	else if (command == 'I') {
		forward();
		servoPosition -= 5;
		if (servoPosition < 45) {
			servoPosition = 45;
		}
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, servoPosition);

	}
	else if (command == 'H') {
		Back();
		servoPosition += 5;
		if (servoPosition > 100) {
			servoPosition = 100;
		}
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, servoPosition);
	}
	else if (command == 'J') {
		Back();
		servoPosition -= 5;
		if (servoPosition < 45) {
			servoPosition = 45;
		}
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, servoPosition);
	}
}
*/


/***************************************************************************************************/
/*void control_car(char command) {
	if (command == 'F') {
		MOTOR__CW();
	}
	else if (command == 'B') {
		MOTOR__CCW();
	}
	else if (command == 'L') {
		while (HAL_UART_Receive(&huart1, (uint8_t *)&receivedCommand, 1, 50) == HAL_OK && receivedCommand == 'L') {
			stepper_move(5, 0, 10); // خطوة واحدة عكس عقارب الساعة
		}
		stopStepper(); // عند تحرير الزر
	}
	else if (command == 'R') {
		while (HAL_UART_Receive(&huart1, (uint8_t *)&receivedCommand, 1, 50) == HAL_OK && receivedCommand == 'R') {
			stepper_move(5, 1, 10); // خطوة واحدة مع عقارب الساعة
		}
		stopStepper(); // عند تحرير الزر
	}
	else if (command == 'S') {
		MOTOR__Stop();
		stopStepper();
	}
	else if (command == 'I') {
		MOTOR__CW();
		servoPosition += 5;
		if (servoPosition > 125) {
			servoPosition = 125;
		}
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, servoPosition);

	}
	else if (command == 'G') {
		MOTOR__CW();
		servoPosition -= 5;
		if (servoPosition < 25) {
			servoPosition = 25;
		}
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, servoPosition);

	}
	else if (command == 'J') {
		MOTOR__CCW();
		servoPosition += 5;
		if (servoPosition > 125) {
			servoPosition = 125;
		}
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, servoPosition);
	}
	else if (command == 'H') {
		MOTOR__CCW();
		servoPosition -= 5;
		if (servoPosition < 25) {
			servoPosition = 25;
		}
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, servoPosition);
	}
}*/

/*void control_car(char command) {
	switch (command) {
	case 'F':  // Move Forward

		MOTOR__CW();
		//__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, 75); //75 F
		break;

	case 'B':  // Move Backward
		MOTOR__CCW();
		//__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, 75); //75 F
		break;
	case 'L':  // left
		//Stepper_UniPolar_Steps_CW(345);
		//HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1); //PA1 TIM2 CH2
		//__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, 40); //40 left

		servoPosition -= 10; // Decrement position
		if (servoPosition < 25) { // Limit to 0°
			servoPosition = 25;
		}
		break;
	case 'R':  // Right
		//HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1); //PA1 TIM2 CH2
		//__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, 120); //40 left
		servoPosition += 10; // Increment position
		if (servoPosition > 125) { // Limit to 180°
			servoPosition = 125;}
		break;
	case 'S':  // Move Backward
		MOTOR__Stop();

		break;

	default:
		break;
	}
	// Update servo position
	    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, servoPosition);
}*/

/*void control_car(char command) {
	if (command == 'F') {
		MOTOR__CW();
	}
	else if (command == 'B') {
		MOTOR__CCW();
	}
	else if (command == 'L') {
		servoPosition -= 5;
		if (servoPosition < 25) {
			servoPosition = 25;
		}
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, servoPosition);
	}
	else if (command == 'R') {
		servoPosition += 5;
		if (servoPosition > 125) {
			servoPosition = 125;
		}
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, servoPosition);
	}
	else if (command == 'S') {
		MOTOR__Stop();
	}
	else if (command == 'I') {
		MOTOR__CW();
		servoPosition += 5;
		if (servoPosition > 125) {
			servoPosition = 125;
		}
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, servoPosition);

	}
	else if (command == 'G') {
		MOTOR__CW();
		servoPosition -= 5;
		if (servoPosition < 25) {
			servoPosition = 25;
		}
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, servoPosition);

	}
	else if (command == 'J') {
		MOTOR__CCW();
		servoPosition += 5;
		if (servoPosition > 125) {
			servoPosition = 125;
		}
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, servoPosition);
	}
	else if (command == 'H') {
		MOTOR__CCW();
		servoPosition -= 5;
		if (servoPosition < 25) {
			servoPosition = 25;
		}
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, servoPosition);
	}
}*/
