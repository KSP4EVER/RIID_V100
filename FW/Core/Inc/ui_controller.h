/*
 * ui_controller.h
 *
 *  Created on: Nov 9, 2024
 *      Author: Misi
 */

#ifndef INC_UI_CONTROLLER_H_
#define INC_UI_CONTROLLER_H_

#include "main.h"
#include "ui.h"

#define MAX_DET_VOLTAGE 38500
#define MIN_DET_VOLTAGE 20000
#define DET_VOLTAGE_STEP 100
#define MAX_BRIGHTNESS 100
#define MIN_BIRGHTNESS 0
#define BRIGHTNESS_STEP 10
#define MAX_VOLUME 100
#define MIN_VOLUME 0
#define VOLUME_STEP 10
#define CHART_LENGHT 180
#define SEGMENT_SIZE 20

#define DEBOUNCE_INTERVAL_MS 500
#define DISP_REFRESH_INTERVAL_MS 200
#define SOC_REFRESH_INTERVAL_MS 30000

enum button_control{
	NO_BTN_CLICKED,
	LEFT_BTN_CLICKED,
	RIGHT_BTN_CLICKED,
	OK_BTN_CLICKED,
	RETURN_BTN_CLICKED,
	UP_BTN_CLICKED,
	DOWN_BTN_CLICKED
};

enum ui_states{
	SCREEN1,
	SCREEN2,
	SCREEN3,
	SCREEN3_SAVE_DATA_SELECT,
	SCREEN3_CLEAR_DATA_SELECT,
	SCREEN4,
	SCREEN4_DET_VOLTAGE_SELECT,
	SCREEN4_BRIGHTNESS_SELECT,
	SCREEN4_VOLUME_SELECT,
	SCREEN5
};

struct _ui_data{
	uint8_t charge_lvl; //0-100
	uint8_t charging;  //0 = not charging 1 = charging
	char time[5];
	char isotpe[10];
	float dose;
	uint16_t cps;
	uint16_t cpm;
	uint16_t detector_voltage;  //det voltage in mV
	uint8_t brightness;	//0-100
	uint8_t volume;		//0-100
};

extern TIM_HandleTypeDef htim3;

static volatile uint8_t current_ui_state = SCREEN3;
static volatile uint8_t input_state = 0;

uint16_t Scan_Button_input(void);
void Select_Screen(void);
void UpdateScreen(void);
void UpdateData(void);
void ui_controller_init(void);
void compress_spectrum(const uint32_t *input, uint16_t input_size);
#endif /* INC_UI_CONTROLLER_H_ */
