/*
 * ui_controller.c
 *
 *  Created on: Nov 9, 2024
 *      Author: Misi
 */
#include "ui_controller.h"

struct _ui_data ui_data;
lv_chart_series_t * ui_Chart1_spectrum;
static lv_coord_t ui_Chart1_spectrum_array[CHART_LENGHT] = {0};
extern uint32_t spectrum[];


uint16_t Scan_Button_input(void){

	if (HAL_GPIO_ReadPin(BUTTON_0_GPIO_Port, BUTTON_0_Pin) == GPIO_PIN_RESET) {
		input_state = RETURN_BTN_CLICKED;
		return DEBOUNCE_INTERVAL_MS;
	}
	else if (HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin) == GPIO_PIN_RESET) {
		input_state = NO_BTN_CLICKED;
		return DEBOUNCE_INTERVAL_MS;
	}
	else if (HAL_GPIO_ReadPin(BUTTON_2_GPIO_Port, BUTTON_2_Pin) == GPIO_PIN_RESET) {
		input_state = DOWN_BTN_CLICKED;
		return DEBOUNCE_INTERVAL_MS;
	}
	else if (HAL_GPIO_ReadPin(BUTTON_3_GPIO_Port, BUTTON_3_Pin) == GPIO_PIN_RESET) {
		input_state = RIGHT_BTN_CLICKED;
		return DEBOUNCE_INTERVAL_MS;
	}
	else if (HAL_GPIO_ReadPin(BUTTON_4_GPIO_Port, BUTTON_4_Pin) == GPIO_PIN_RESET) {
		input_state = LEFT_BTN_CLICKED;
		return DEBOUNCE_INTERVAL_MS;
	}
	else if (HAL_GPIO_ReadPin(BUTTON_5_GPIO_Port, BUTTON_5_Pin) == GPIO_PIN_RESET) {
		input_state = OK_BTN_CLICKED;
		return DEBOUNCE_INTERVAL_MS;
	}
	else if (HAL_GPIO_ReadPin(BUTTON_6_GPIO_Port, BUTTON_6_Pin) == GPIO_PIN_RESET) {
		input_state = UP_BTN_CLICKED;
	}
	else if (HAL_GPIO_ReadPin(BUTTON_7_GPIO_Port, BUTTON_7_Pin) == GPIO_PIN_RESET) {
		input_state = NO_BTN_CLICKED;
	}
	//no button clicked no debounce waiting needed
	else return 0;

}
void Select_Screen(void){

	switch(current_ui_state){

	//screen1 states---------------------------------------------------------------------
	case SCREEN1:
		current_ui_state = SCREEN2;
		break;
	//screen1 states---------------------------------------------------------------------
	//screen2 states---------------------------------------------------------------------
	case SCREEN2:
		if(input_state == LEFT_BTN_CLICKED){
			current_ui_state = SCREEN5;
		}
		if(input_state == RIGHT_BTN_CLICKED){
			current_ui_state = SCREEN3;
		}
		break;
	//screen2 states---------------------------------------------------------------------
	//screen3 states---------------------------------------------------------------------
	case SCREEN3:
		if(input_state == LEFT_BTN_CLICKED){
			current_ui_state = SCREEN2;
		}
		if(input_state == RIGHT_BTN_CLICKED){
			current_ui_state = SCREEN4;
		}

		if(input_state == OK_BTN_CLICKED){
			current_ui_state = SCREEN3_SAVE_DATA_SELECT;
		}
		break;

	case SCREEN3_SAVE_DATA_SELECT:
		if(input_state == OK_BTN_CLICKED){
			//save spectrum here
			MX_FileX_Process();
		}

		if(input_state == DOWN_BTN_CLICKED){
			current_ui_state = SCREEN3_CLEAR_DATA_SELECT;
		}
		if(input_state == RETURN_BTN_CLICKED){
			current_ui_state = SCREEN3;
		}
		break;

	case SCREEN3_CLEAR_DATA_SELECT:
		if(input_state == OK_BTN_CLICKED){
			for (int i = 0; i < 4096;i++) spectrum[i] = 0;
		}
		if(input_state == UP_BTN_CLICKED){
			current_ui_state = SCREEN3_SAVE_DATA_SELECT;
		}
		if(input_state == RETURN_BTN_CLICKED){
			current_ui_state = SCREEN3;
		}
		break;

	//screen3 states-----------------------------------------------
	//screen4 states-----------------------------------------------
	case SCREEN4:
		if(input_state == RIGHT_BTN_CLICKED){
			current_ui_state = SCREEN5;
		}
		if(input_state == LEFT_BTN_CLICKED){
			current_ui_state = SCREEN3;
		}
		if(input_state == OK_BTN_CLICKED){
			current_ui_state = SCREEN4_DET_VOLTAGE_SELECT;
		}
		break;
	//screen4 voltage menu-----------------------------------------
	case SCREEN4_DET_VOLTAGE_SELECT:
		if(input_state == DOWN_BTN_CLICKED){
			current_ui_state = SCREEN4_BRIGHTNESS_SELECT;
		}
		if(input_state == RETURN_BTN_CLICKED){
			current_ui_state = SCREEN4;
		}
		if (input_state == LEFT_BTN_CLICKED){
			if (ui_data.detector_voltage >= MIN_DET_VOLTAGE) ui_data.detector_voltage = ui_data.detector_voltage - DET_VOLTAGE_STEP;
		}
		if (input_state == RIGHT_BTN_CLICKED){
			if (ui_data.detector_voltage < MAX_DET_VOLTAGE) ui_data.detector_voltage = ui_data.detector_voltage + DET_VOLTAGE_STEP;
		}
		break;

	//----------------------------------------------------------------
	//screen4 brightness menu-----------------------------------------
	case SCREEN4_BRIGHTNESS_SELECT:
		if(input_state == DOWN_BTN_CLICKED){
			current_ui_state = SCREEN4_VOLUME_SELECT;
		}
		if(input_state == RETURN_BTN_CLICKED){
			current_ui_state = SCREEN4;
		}
		if(input_state == UP_BTN_CLICKED){
			current_ui_state = SCREEN4_DET_VOLTAGE_SELECT;
		}
		if(input_state == RIGHT_BTN_CLICKED){
			if (ui_data.brightness < MAX_BRIGHTNESS) ui_data.brightness = ui_data.brightness + BRIGHTNESS_STEP;
			htim3.Instance->CCR2 = ui_data.brightness;
		}
		if(input_state == LEFT_BTN_CLICKED){
			if (ui_data.brightness > MIN_BIRGHTNESS) ui_data.brightness = ui_data.brightness - BRIGHTNESS_STEP;
			htim3.Instance->CCR2 = ui_data.brightness;
		}
		break;

	//------------------------------------------------------------
	//screen4 volume menu-----------------------------------------
	case SCREEN4_VOLUME_SELECT:
		if(input_state == RETURN_BTN_CLICKED){
			current_ui_state = SCREEN4;
		}
		if(input_state == UP_BTN_CLICKED){
			current_ui_state = SCREEN4_BRIGHTNESS_SELECT;
		}
		if(input_state == RIGHT_BTN_CLICKED){
			if (ui_data.volume < MAX_VOLUME) ui_data.volume = ui_data.volume + VOLUME_STEP;
		}
		if(input_state == LEFT_BTN_CLICKED){
			if (ui_data.volume > MIN_VOLUME) ui_data.volume = ui_data.volume - VOLUME_STEP;
		}
		break;

	////////////////////////////////////////////////////////
	//screen5 states
	case SCREEN5:
		if(input_state == LEFT_BTN_CLICKED){
			current_ui_state = SCREEN4;
		}
		if(input_state == RIGHT_BTN_CLICKED){
			current_ui_state = SCREEN2;
		}
		break;
	////////////////////////////////////////////////////////
	}
	input_state = NO_BTN_CLICKED;

}
void UpdateScreen(void){
	switch(current_ui_state){
	case SCREEN2:
		//change screen
		_ui_screen_change(&ui_Screen2, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_Screen2_screen_init);
		lv_obj_set_parent(ui_Navbar,ui_Screen2);
		break;

	case SCREEN3:
		_ui_screen_change(&ui_Screen3, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_Screen3_screen_init);
		lv_obj_set_parent(ui_Navbar,ui_Screen3);
		//border managment
		lv_obj_set_style_outline_width(ui_savedata, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_width(ui_cleardata, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		break;
	case SCREEN3_SAVE_DATA_SELECT:
		//borded to button
		lv_obj_set_style_outline_width(ui_savedata, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_width(ui_cleardata, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

		break;
	case SCREEN3_CLEAR_DATA_SELECT:
		//border managment
		lv_obj_set_style_outline_width(ui_savedata, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_width(ui_cleardata, 2, LV_PART_MAIN | LV_STATE_DEFAULT);


		break;
	case SCREEN4:
		_ui_screen_change(&ui_Screen4, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_Screen4_screen_init);
		lv_obj_set_parent(ui_Navbar,ui_Screen4);

		//border managment
		lv_obj_set_style_outline_width(ui_lcdbrightnessbar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_width(ui_beepvolumebar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_width(ui_detvoltagebar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);


		break;
	case SCREEN4_BRIGHTNESS_SELECT:
		//border managment
		lv_obj_set_style_outline_width(ui_lcdbrightnessbar, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_width(ui_beepvolumebar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_width(ui_detvoltagebar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		break;
	case SCREEN4_DET_VOLTAGE_SELECT:
		//border management
		lv_obj_set_style_outline_width(ui_lcdbrightnessbar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_width(ui_beepvolumebar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_width(ui_detvoltagebar, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
		break;
	case SCREEN4_VOLUME_SELECT:
		//border management
		lv_obj_set_style_outline_width(ui_lcdbrightnessbar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_width(ui_beepvolumebar, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_width(ui_detvoltagebar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		break;
	case SCREEN5:
		_ui_screen_change(&ui_Screen5, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_Screen5_screen_init);
		lv_obj_set_parent(ui_Navbar,ui_Screen5);
		break;
	}
}

void UpdateData(void){

	//update battery stat////////////////////////////////////////////////////////////////////////////////////////////
	char soc_text[3] = {0};
	sprintf(soc_text,"%d",ui_data.charge_lvl);
	lv_label_set_text(ui_stateofcharge, soc_text);

	if (ui_data.charge_lvl < 25){
		lv_obj_set_style_bg_color(ui_stateofcharge, lv_color_hex(0xe74c3c), LV_PART_MAIN | LV_STATE_DEFAULT);
	}
	else if((ui_data.charge_lvl > 25)&&(ui_data.charge_lvl < 60)){
		lv_obj_set_style_bg_color(ui_stateofcharge, lv_color_hex(0xf1c40f), LV_PART_MAIN | LV_STATE_DEFAULT);
	}
	else{
		lv_obj_set_style_bg_color(ui_stateofcharge, lv_color_hex(0x2ecc71), LV_PART_MAIN | LV_STATE_DEFAULT);
	}

	if (ui_data.charging == 0)lv_obj_add_flag(ui_chargingico, LV_OBJ_FLAG_HIDDEN);
	else {
		lv_obj_clear_flag(ui_chargingico, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_style_bg_color(ui_stateofcharge, lv_color_hex(0x2ecc71), LV_PART_MAIN | LV_STATE_DEFAULT);
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	lv_label_set_text(ui_time, "22:13");

	//SCREEN2 Update data/////////////////////////////////////////////////////////////////////////////////////////////
	if(current_ui_state == SCREEN2){
		char cps_text[6];
		char cpm_text[6];



		snprintf(cps_text,6, "%d",ui_data.cps);
		sprintf(cpm_text, "%d",ui_data.cpm);

		lv_label_set_text(ui_cps, cps_text);
		lv_label_set_text(ui_cpm, cpm_text);
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//SCREEN3 Update data//////////////////////////////////////////////////////////////////////////////////////////////
	else if((current_ui_state == SCREEN3) || (current_ui_state == SCREEN3_SAVE_DATA_SELECT) || (current_ui_state == SCREEN3_CLEAR_DATA_SELECT)){
		//ui_Chart1_series_1_array


		//set range rounded up to the nearest x000 value example max = 2125 -> range = 3000
		uint32_t max = 0;
		for (int i = 0; i < CHART_LENGHT;i++){
			if(max < (uint32_t)ui_Chart1_spectrum_array[i])max = (uint32_t)ui_Chart1_spectrum_array[i];
		}

		lv_chart_set_range(ui_Chart1, LV_CHART_AXIS_PRIMARY_Y, 0, (1 + (max - max%1000)/1000)*1000);

		lv_chart_set_ext_y_array(ui_Chart1, ui_Chart1_spectrum, ui_Chart1_spectrum_array);
		lv_chart_refresh(ui_Chart1);
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//SCREEN4 Update data//////////////////////////////////////////////////////////////////////////////////////////////
	else if((current_ui_state == SCREEN4)||(current_ui_state == SCREEN4_BRIGHTNESS_SELECT)||(current_ui_state == SCREEN4_DET_VOLTAGE_SELECT) || (current_ui_state == SCREEN4_VOLUME_SELECT)){
		lv_bar_set_value(ui_lcdbrightnessbar, (uint32_t)ui_data.brightness, LV_ANIM_OFF);
		lv_bar_set_value(ui_beepvolumebar, (uint32_t)ui_data.volume, LV_ANIM_OFF);
		lv_bar_set_value(ui_detvoltagebar, (uint32_t)ui_data.detector_voltage, LV_ANIM_OFF);

		char detvoltage_text[8] = {0};
		sprintf(detvoltage_text,"%d mV",ui_data.detector_voltage);
		lv_label_set_text(ui_detvoltage, detvoltage_text);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}



void ui_controller_init(){
	ui_data.brightness = 50;
	ui_data.volume = 50;
	ui_data.cpm = 0;
	ui_data.cps = 0;
	ui_data.detector_voltage = 29000;
	ui_data.dose = 0.0;
	ui_data.charge_lvl = 0;
	ui_data.charging = 0;

	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	htim3.Instance->CCR2 = ui_data.brightness;

	ui_Chart1_spectrum = lv_chart_add_series(ui_Chart1, lv_color_hex(0xFF0000),LV_CHART_AXIS_PRIMARY_Y);

}
void compress_spectrum(const uint32_t *input, uint16_t size){
	for(int i = 0; i < CHART_LENGHT;i++){
		 uint32_t sum = 0;
		 for (int j = 0; j < SEGMENT_SIZE; j++) {
			 sum += input[i * SEGMENT_SIZE + j];
		 }
		 ui_Chart1_spectrum_array[i] = (lv_coord_t)(sum / SEGMENT_SIZE);
	}
}
