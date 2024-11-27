/*
 * application.c
 *
 *  Created on: Nov 14, 2024
 *      Author: Misi
 */

#include "application.h"
#include "ui_controller.h"

extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim7;
extern ADC_HandleTypeDef hadc1;
extern struct _ui_data ui_data;

uint32_t spectrum[SPECTRUM_SIZE];
uint16_t cpm_data[60] = {0};

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
#if !DUMMY_SPECTRUM
	//HAL_GPIO_TogglePin(DEBUG_1_GPIO_Port,DEBUG_1_Pin);
	delay_us(5);
	uint32_t DET_VALUE = 0;
	for(int i = 0;i < 5;i++){
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1,5);
		DET_VALUE = DET_VALUE + HAL_ADC_GetValue(&hadc1);
		HAL_ADC_Stop(&hadc1);
	//HAL_GPIO_WritePin(PEAK_DET_RST_GPIO_Port, PEAK_DET_RST_Pin,1);
	}
	DET_VALUE = DET_VALUE / 5;
	spectrum[DET_VALUE]++;
	delay_us(5);
	HAL_GPIO_WritePin(PEAK_DET_RST_GPIO_Port, PEAK_DET_RST_Pin,0);
	//HAL_GPIO_TogglePin(DEBUG_1_GPIO_Port,DEBUG_1_Pin);
#endif
}

void updateCPS(){
	ui_data.cps = __HAL_TIM_GET_COUNTER(&htim4);
	__HAL_TIM_SET_COUNTER(&htim4,0);
}
void updateCPM(){
	  for(int i = 0; i < 59;i++){
		  cpm_data[i] = cpm_data[i + 1];
	  }
	  ui_data.cpm = 0;
	  cpm_data[59] = ui_data.cps;
	  for(int i = 0; i < 60;i++){
		  ui_data.cpm = ui_data.cpm + cpm_data[i];
	  }
}

void delay_us (uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&htim7,0);  // set the counter value a 0
	while (__HAL_TIM_GET_COUNTER(&htim7) < us);  // wait for the counter to reach the us input in the parameter
}

double gaussian(int x, int mean, double std_dev) {
    return exp(-0.5 * pow((x - mean) / std_dev, 2.0));
}
void generate_spectrum(uint32_t *spectrum, uint32_t peak_height) {
// Generate background noise
	 for (int i = 0; i < SPECTRUM_SIZE; i++) {
		 spectrum[i] = BACKGROUND_LEVEL + rand() % 3; // Random background noise
	 }

	 // Add Compton continuum
	 for (int i = 0; i < COMPTON_EDGE; i++) {
		 spectrum[i] += (COMPTON_EDGE - i) / 20 + rand() % 2;
	 }

	 // Add Gaussian photopeak around the PEAK_POSITION
	 for (int i = PEAK_POSITION - 4 * PEAK_WIDTH; i < PEAK_POSITION + 4 * PEAK_WIDTH; i++) {
		 if (i >= 0 && i < SPECTRUM_SIZE) {
			 double gaussian_value = peak_height * exp(-0.5 * pow((i - PEAK_POSITION) / (double)PEAK_WIDTH, 2.0));
			 spectrum[i] += (uint16_t)(gaussian_value) + rand() % 3;
		 }
	 }
}



