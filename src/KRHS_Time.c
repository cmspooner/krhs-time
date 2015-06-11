#include "pebble.h"

#define DAY_KEY 0

int normal_times[] = {460, 510,             //Per 1
                      515, 570,             //Per 2
                      575, 625,             //Per 3
                      630, 680,             //Per 4
                      685, 710, 735, 760,   //Per 5
                      765, 815,             //Per 6
                      820, 870,             //Per 7
                      915};                 //Per 8
char *normal_names[] = {"Before School",
                         "Period 1",
                         "Passing Time",
                         "Period 2",
                         "Passing Time",
                         "Period 3",
                         "Passing Time",
                         "Period 4",
                         "Passing Time",
                         "Period 5,wave 1",
                         "Period 5,wave 2",
                         "Period 5,wave 3",
                         "Passing Time",
                         "Period 6",
                         "Passing Time",
                         "Period 7",
                         "Teacher Time"};
                         
int pt_times[] = {460, 505,                 //Per 1
                      510, 555,             //Per 2
                      560, 605,             //Per 3
                      610, 655,             //Per 4
                      660, 685, 710, 735,   //Per 5
                      740, 785,             //Per 6
                      790, 835,             //Per 7
                      915};                 //Per 8
char *pt_names[] = {"Before School",
                         "Period 1",
                         "Passing Time",
                         "Period 2",
                         "Passing Time",
                         "Period 3",
                         "Passing Time",
                         "Period 4",
                         "Passing Time",
                         "Period 5,wave 1",
                         "Period 5,wave 2",
                         "Period 5,wave 3",
                         "Passing Time",
                         "Period 6",
                         "Passing Time",
                         "Period 7",
                         "Prime Time"};
                         
int ad_times[] = {460, 505,                 //Per 1
                      510, 555,             //Per 2
                      560, 590,             //Advisory        
                      595, 640,             //Per 3
                      645, 690,             //Per 4
                      695, 720, 745, 770,   //Per 5
                      775, 820,             //Per 6
                      825, 870,             //Per 7
                      915};                 //Per 8
char *ad_names[] = {"Before School",
                         "Period 1",
                         "Passing Time",
                         "Period 2",
                         "Passing Time",
                         "Advisory",
                         "Passing Time",
                         "Period 3",
                         "Passing Time",
                         "Period 4",
                         "Passing Time",
                         "Period 5,wave 1",
                         "Period 5,wave 2",
                         "Period 5,wave 3",
                         "Passing Time",
                         "Period 6",
                         "Passing Time",
                         "Period 7",
                         "Teacher Time"};
                         
int pa_times[] = {460, 500,                 //Per 1
                      505, 545,             //Per 2
                      550, 590,             //Per 3
                      595, 635,             //Per 4
                      640, 680,             //Per 5
                      685, 710, 735, 760,   //Per 6
                      765, 805,             //Per 7
                      810, 870,             //PM Activity
                      915};                 //Per 8
char *pa_names[] = {"Before School",
                         "Period 1",
                         "Passing Time",
                         "Period 2",
                         "Passing Time",
                         "Period 3",
                         "Passing Time",
                         "Period 4",
                         "Passing Time",
                         "Period 5",
                         "Passing Time",
                         "Period 6,wave 1",
                         "Period 6,wave 2",
                         "Period 6,wave 3",
                         "Passing Time",
                         "Period 7",
                         "PM Activity",
                         "Teacher Time"};
                         
int do_times[] = {580, 610,                 //Per 1
                      615, 645,             //Per 2
                      650, 680,             //Per 3
                      685, 715,             //Per 4
                      720, 745, 770, 795,   //Per 5
                      800, 830,             //Per 6
                      835, 870,             //Per 7
                      915};                 //Per 8
char *do_names[] = {"Before School",
                         "Period 1",
                         "Passing Time",
                         "Period 2",
                         "Passing Time",
                         "Period 3",
                         "Passing Time",
                         "Period 4",
                         "Passing Time",
                         "Period 5,wave 1",
                         "Period 5,wave 2",
                         "Period 5,wave 3",
                         "Passing Time",
                         "Period 6",
                         "Passing Time",
                         "Period 7",
                         "Teacher Time"};
                         
int ne_times[] = {465, 565,                 //Per 1
                      570, 580,             //Per 2
                      585, 680,             //Per 3
                      685, 710, 735, 760,   //Per 5
                      765, 875,             //Per 6
                      915};                 //Per 8
char *ne_names[] = {"Before School",
                         "Period 1",
                         "Passing Time",
                         "Break",
                         "Passing Time",
                         "Period 3",
                         "Passing Time",
                         "Period 5,wave 1",
                         "Period 5,wave 2",
                         "Period 5,wave 3",
                         "Passing Time",
                         "Period 7",
                         "Teacher Time"};                
                        
int ex_times[] = {480, 570,                 //Per 1
                      600, 690,             //Per 2
                      695, 760,             //Per 3
                      765, 840,             //Per 6
                      915};                 //Per 8
char *ex_names[] = {"Before School",
                         "Exam 1",
                         "Passing Time",
                         "Exam 2",
                         "Passing Time",
                         "Lunch",
                         "Passing Time",
                         "Make Up Exam",
                         "Teacher Time"};                
                         
enum Settings { setting_type_of_day = 1, setting_offset};
static enum SettingTypeOfDay { type_of_day_regular = 1, 
                            type_of_day_prime_time,
                            type_of_day_advisory,
                            type_of_day_pm_activity,
                            type_of_day_delayed_opening,
                            type_of_day_necap,
                            type_of_day_exam,
                            type_of_day_count } 
                            type_of_day;
static enum SettingOffset { set_offset_delay = 0, set_offset_count} set_offset;

Window *window;
TextLayer *text_date_layer;
TextLayer *text_time_layer;
TextLayer *current_period_layer;
TextLayer *period_time_left_layer;
TextLayer *battery_layer;
TextLayer *connection_layer;
Layer *line_layer;
static AppSync app;
static uint8_t buffer[256];
int didVib = 0;
bool isConnected = true;
int chargePercent = 50;
bool nearEnd = false;
//int offset = -1;

void line_layer_update_callback(Layer *layer, GContext* ctx) {
  #ifdef PBL_COLOR
    graphics_context_set_fill_color(ctx, GColorVividCerulean);
  #else
    graphics_context_set_fill_color(ctx, GColorBlack);
  #endif
  graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
}

static void app_error_callback(DictionaryResult dict_error, AppMessageResult app_message_error, void* context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "app error %d", app_message_error);
}

static void handle_battery(BatteryChargeState charge_state) {
  static char battery_text[] = "100% charged";
  chargePercent = charge_state.charge_percent;
  if (charge_state.is_charging) {
    snprintf(battery_text, sizeof(battery_text), "charging");
  } else {
    snprintf(battery_text, sizeof(battery_text), "%d%% charged", chargePercent);
  }
  text_layer_set_text(battery_layer, battery_text);
  #ifdef PBL_COLOR
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "charged %d", chargePercent);
    if (chargePercent >= 70){
      text_layer_set_text_color(battery_layer, GColorGreen);
    } else if  (chargePercent >= 40){
      text_layer_set_text_color(battery_layer, GColorYellow);
    } else {
      text_layer_set_text_color(battery_layer, GColorDarkCandyAppleRed);
    }
  #else
    text_layer_set_text_color(battery_layer, GColorBlack);
  #endif
}

static void handle_bluetooth(bool connected) {
  isConnected = connected;
  if (connected){
    text_layer_set_text(connection_layer, "connected");
  } else {
    text_layer_set_text(connection_layer, "disconnected");
  }
  #ifdef PBL_COLOR
    if (isConnected){
      text_layer_set_text_color(connection_layer, GColorGreen);
    } else {
      text_layer_set_text_color(connection_layer, GColorDarkCandyAppleRed);
    }
  #else
    text_layer_set_text_color(connection_layer, GColorBlack);
  #endif
}

void handle_minute_tick(struct tm *tick_time, TimeUnits units_changed) {
  // Need to be static because they're used by the system later.
  static char time_text[] = "00:00";
  static char date_text[] = "Xxx, Xxx. 00";
  static char *period_text;
  static char period_time_left[] = "Remaing: xx minutes";
  
  int time_hour = 0;
  int time_min = 0;
  int min_time = 0;
  int minutes_left = 0;

  char *time_format;
  
  int found = 0;

  if (!tick_time) {
    time_t now = time(NULL);
    tick_time = localtime(&now);
  }
  
  time_min = tick_time->tm_min;
  time_hour = tick_time->tm_hour;
  
  min_time = time_hour * 60 + time_min + -1;
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Day Key is! %d", type_of_day);

  if (type_of_day == type_of_day_regular){
      for (int i = 0; (unsigned)i < sizeof(normal_times); i++){
          if (min_time < normal_times[i] && !found){
              period_text = normal_names[i];
              minutes_left = normal_times[i] - min_time;
              found = 1;
          }
      }
  } else if (type_of_day == type_of_day_prime_time){
      for (int i = 0; (unsigned)i < sizeof(pt_times); i++){
          if (min_time < pt_times[i] && !found){
              period_text = pt_names[i];
              minutes_left = pt_times[i] - min_time;
              found = 1;
          }
      } 
  } else if (type_of_day == type_of_day_advisory){
      for (int i = 0; (unsigned)i < sizeof(ad_times); i++){
          if (min_time < ad_times[i] && !found){
              period_text = ad_names[i];
              minutes_left = ad_times[i] - min_time;
              found = 1;
          }
      } 
  } else if (type_of_day == type_of_day_pm_activity){
      for (int i = 0; (unsigned)i < sizeof(pa_times); i++){
          if (min_time < pa_times[i] && !found){
              period_text = pa_names[i];
              minutes_left = pa_times[i] - min_time;
              found = 1;
          }
      } 
  } else if (type_of_day == type_of_day_delayed_opening){
      for (int i = 0; (unsigned)i < sizeof(do_times); i++){
          if (min_time < do_times[i] && !found){
              period_text = do_names[i];
              minutes_left = do_times[i] - min_time;
              found = 1;
          }
      } 
  } else if (type_of_day == type_of_day_necap){
      for (int i = 0; (unsigned)i < sizeof(ne_times); i++){
          if (min_time < ne_times[i] && !found){
              period_text = ne_names[i];
              minutes_left = ne_times[i] - min_time;
              found = 1;
          }
      } 
  }
  
  else if (type_of_day == type_of_day_exam){
      for (int i = 0; (unsigned)i < sizeof(ex_times); i++){
          if (min_time < ex_times[i] && !found){
              period_text = ex_names[i];
              minutes_left = ex_times[i] - min_time;
              found = 1;
          }
      } 
  }
  
  if (min_time >= 915 || min_time <= 360){
      found = 1;
      period_text = "";
      snprintf(period_time_left, sizeof(period_time_left), " ");
  } else {
    snprintf(period_time_left, sizeof(period_time_left), "Remaining: %d min", minutes_left);
  }

  if (minutes_left == 2 && !didVib){
      didVib = 1;
      vibes_short_pulse();
  } else if (minutes_left == 1 && didVib){
      didVib = 0; 
  }
  
  if (minutes_left <= 2){
    nearEnd = true;
  } else {
    nearEnd = false;
  }
  #ifdef PBL_COLOR
    if (nearEnd){
      text_layer_set_text_color(period_time_left_layer, GColorDarkCandyAppleRed);
    } else {
      text_layer_set_text_color(period_time_left_layer, GColorWhite);
    }
  #else
    text_layer_set_text_color(period_time_left_layer, GColorBlack);
  #endif
  
  text_layer_set_text(current_period_layer, period_text);
  text_layer_set_text(period_time_left_layer, period_time_left);
  
  // TODO: Only update the date when it's changed.
  strftime(date_text, sizeof(date_text), "%a, %b. %e", tick_time);
  text_layer_set_text(text_date_layer, date_text);
  

  if (clock_is_24h_style()) {
    time_format = "%R";
  } else {
    time_format = "%I:%M";
  }

  

  strftime(time_text, sizeof(time_text), time_format, tick_time);
  

  // Kludge to handle lack of non-padded hour format string
  // for twelve hour clock.
  if (!clock_is_24h_style() && (time_text[0] == '0')) {
    memmove(time_text, &time_text[1], sizeof(time_text) - 1);
  }

  text_layer_set_text(text_time_layer, time_text);
  handle_battery(battery_state_service_peek());

}

static void tuple_changed_callback(const uint32_t key, const Tuple* tuple_new, const Tuple* tuple_old, void* context) {
  //  we know these values are uint8 format
  int value = tuple_new->value->uint8;
  switch (key) {
    case setting_type_of_day:
      if ((value > 0) && (value < type_of_day_count) && (type_of_day != value)) {
        type_of_day = value+1;
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Day Key set to: %d", type_of_day);
        handle_minute_tick(NULL, MINUTE_UNIT);
    }
    case setting_offset:
      if ((value >= 0) && (value < set_offset_count) && (set_offset != value)) {
        set_offset = value;
        handle_minute_tick(NULL, MINUTE_UNIT);
    }
      break;
  }
}

void handle_deinit(void) {
  persist_write_int(DAY_KEY, type_of_day);
  tick_timer_service_unsubscribe();
  app_sync_deinit(&app);
}

void handle_init(void) {
  window = window_create();
  window_stack_push(window, true /* Animated */);
  #ifdef PBL_COLOR
    window_set_background_color(window, GColorBlack);
  #else
    window_set_background_color(window, GColorWhite);
  #endif

  Layer *window_layer = window_get_root_layer(window);
  
  connection_layer = text_layer_create(GRect(0, 75, 144-8, 34));
  #ifdef PBL_COLOR
    if (isConnected){
      text_layer_set_text_color(connection_layer, GColorGreen);
    } else {
      text_layer_set_text_color(connection_layer, GColorDarkCandyAppleRed);
    }
  #else
    text_layer_set_text_color(connection_layer, GColorBlack);
  #endif
  text_layer_set_background_color(connection_layer, GColorClear);
  text_layer_set_font(connection_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_text_alignment(connection_layer, GTextAlignmentCenter);
  handle_bluetooth(bluetooth_connection_service_peek());
  layer_add_child(window_layer, text_layer_get_layer(connection_layer));

  battery_layer = text_layer_create(GRect(0, 95,  144-8, 34));
  #ifdef PBL_COLOR
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "charged %d", chargePercent);
    if (chargePercent >= 70){
      text_layer_set_text_color(battery_layer, GColorGreen);
    } else if  (chargePercent >= 40){
      text_layer_set_text_color(battery_layer, GColorYellow);
    } else {
      text_layer_set_text_color(battery_layer, GColorDarkCandyAppleRed);
    }
  #else
    text_layer_set_text_color(battery_layer, GColorBlack);
  #endif
  text_layer_set_background_color(battery_layer, GColorClear);
  text_layer_set_font(battery_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_text_alignment(battery_layer, GTextAlignmentCenter);
  text_layer_set_text(battery_layer, "100% charged");
  layer_add_child(window_layer, text_layer_get_layer(battery_layer));

  text_date_layer = text_layer_create(GRect(8, 0, 144-8, 168-68));
  #ifdef PBL_COLOR
     text_layer_set_text_color(text_date_layer, GColorLightGray);
  #else
     text_layer_set_text_color(text_date_layer, GColorBlack);
  #endif
  text_layer_set_background_color(text_date_layer, GColorClear);
  text_layer_set_font(text_date_layer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));
  layer_add_child(window_layer, text_layer_get_layer(text_date_layer));

  GRect line_frame = GRect(8, 27, 144-16, 2);
  line_layer = layer_create(line_frame);
  layer_set_update_proc(line_layer, line_layer_update_callback);
  layer_add_child(window_layer, line_layer);

  text_time_layer = text_layer_create(GRect(7, 20, 144-7, 168-92));
  #ifdef PBL_COLOR
     text_layer_set_text_color(text_time_layer, GColorWhite);
  #else
     text_layer_set_text_color(text_time_layer, GColorBlack);
  #endif
  text_layer_set_background_color(text_time_layer, GColorClear);
  text_layer_set_font(text_time_layer, fonts_get_system_font(FONT_KEY_ROBOTO_BOLD_SUBSET_49));
  layer_add_child(window_layer, text_layer_get_layer(text_time_layer));

  current_period_layer = text_layer_create(GRect(8, 120, 144-8, 168-68));
  #ifdef PBL_COLOR
     text_layer_set_text_color(current_period_layer, GColorWhite);
  #else
     text_layer_set_text_color(current_period_layer, GColorBlack);
  #endif
  text_layer_set_background_color(current_period_layer, GColorClear);
  text_layer_set_font(current_period_layer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));
  layer_add_child(window_layer, text_layer_get_layer(current_period_layer));
  
  period_time_left_layer = text_layer_create(GRect(8, 140, 144-8, 168-68));
  #ifdef PBL_COLOR
    if (nearEnd){
      text_layer_set_text_color(period_time_left_layer, GColorDarkCandyAppleRed);
    } else {
      text_layer_set_text_color(period_time_left_layer, GColorWhite);
    }
  #else
    text_layer_set_text_color(period_time_left_layer, GColorBlack);
  #endif
  text_layer_set_background_color(period_time_left_layer, GColorClear);
  text_layer_set_font(period_time_left_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  layer_add_child(window_layer, text_layer_get_layer(period_time_left_layer));
    
  Tuplet tuples[] = {
    TupletInteger(setting_type_of_day, type_of_day) };
  
  app_message_open(160, 160);
  app_sync_init(&app, buffer, sizeof(buffer), tuples, ARRAY_LENGTH(tuples),
                tuple_changed_callback, app_error_callback, NULL);
  
  if (persist_exists(DAY_KEY)) {
    type_of_day = persist_read_int(DAY_KEY);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Day Key found! %d", type_of_day);
  } else {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "No Day Key found!");
  }

  tick_timer_service_subscribe(MINUTE_UNIT, handle_minute_tick);
  battery_state_service_subscribe(&handle_battery);
  bluetooth_connection_service_subscribe(&handle_bluetooth);
  handle_minute_tick(NULL, MINUTE_UNIT);
}

int main(void) {
  handle_init();

  app_event_loop();
  
  handle_deinit();
}
