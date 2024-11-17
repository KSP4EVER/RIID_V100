// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 8.3.6
// Project name: riid_ui

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
lv_obj_t * ui_Screen1;
lv_obj_t * ui_Spinner1;
lv_obj_t * ui_Image1;
lv_obj_t * ui_Label2;
// CUSTOM VARIABLES


// SCREEN: ui_Screen2
void ui_Screen2_screen_init(void);
void ui_event_Screen2(lv_event_t * e);
lv_obj_t * ui_Screen2;
lv_obj_t * ui_label5;
lv_obj_t * ui_label6;
lv_obj_t * ui_label7;
lv_obj_t * ui_label4;
lv_obj_t * ui_isotope;
lv_obj_t * ui_dose;
lv_obj_t * ui_cps;
lv_obj_t * ui_cpm;
lv_obj_t * ui_Navbar;
lv_obj_t * ui_stateofcharge;
lv_obj_t * ui_time;
lv_obj_t * ui_Image3;
lv_obj_t * ui_chargingico;
// CUSTOM VARIABLES
lv_obj_t * uic_Screen2;


// SCREEN: ui_Screen3
void ui_Screen3_screen_init(void);
lv_obj_t * ui_Screen3;
lv_obj_t * ui_Chart1;
lv_obj_t * ui_savedata;
lv_obj_t * ui_cleardata;
lv_obj_t * ui_Label11;
lv_obj_t * ui_Label12;
// CUSTOM VARIABLES


// SCREEN: ui_Screen4
void ui_Screen4_screen_init(void);
lv_obj_t * ui_Screen4;
lv_obj_t * ui_Label13;
lv_obj_t * ui_lcdbrightnessbar;
lv_obj_t * ui_Label14;
lv_obj_t * ui_Label15;
lv_obj_t * ui_beepvolumebar;
lv_obj_t * ui_detvoltagebar;
lv_obj_t * ui_detvoltage;
// CUSTOM VARIABLES


// SCREEN: ui_Screen5
void ui_Screen5_screen_init(void);
lv_obj_t * ui_Screen5;
lv_obj_t * ui_Label16;
lv_obj_t * ui_Label17;
// CUSTOM VARIABLES

// EVENTS
lv_obj_t * ui____initial_actions0;

// IMAGES AND IMAGE SETS

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_Screen2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_KEY &&  lv_event_get_key(e) == LV_KEY_ENTER) {
        _ui_screen_change(&ui_Screen3, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_Screen3_screen_init);
    }
}

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    ui_Screen2_screen_init();
    ui_Screen3_screen_init();
    ui_Screen4_screen_init();
    ui_Screen5_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_Screen1);
}
