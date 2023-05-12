/** 
  ******************************************************************************
  * @file    gui_interface.cpp
  * @author  Gremsy Team
  * @version V2.0.0
  * @date    ${date}
  * @brief   
  *
  ******************************************************************************
  * @Copyright
  * COPYRIGHT NOTICE: (c) ${year} Gremsy.  
  * All rights reserved.
  *
  * The information contained herein is confidential
  * property of Company. The use, copying, transfer or 
  * disclosure of such information is prohibited except
  * by express written agreement with Company.
  *
  ******************************************************************************
*/ 

/* Includes ------------------------------------------------------------------*/

#include "Common.h"
#include "gui_interface.h"
#include <gtk/gtk.h>

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static GtkWidget *window;

static GtkWidget *halign;
static GtkWidget *valign;

static GtkWidget *hbox;
// static GtkWidget *vbox;

static GtkWidget *pitch_scale;
static GtkWidget *pitch_label;

static GtkWidget *yaw_scale;
static GtkWidget *yaw_label;
static GtkWidget *gb_mapping_button;
static GtkWidget *gb_lock_button;
static GtkWidget *gb_follow_button;
static GtkWidget *gb_return_home_button;

static GtkWidget *capture_button;
static GtkWidget *record_button;
static GtkWidget *camera_fixed;
static GtkWidget *gimbal_fixed;
static GtkWidget *table;

static GtkWidget *frame1;
static GtkWidget *frame2;

static bool s_capture_button = false;
static bool s_record_button = false;
static int s_pitch_value = 0;
static int s_yaw_value = 0;
static bool s_gb_mapping_button = false;
static bool s_gb_lock_button = false;
static bool s_gb_follow_button = false;
static bool s_gb_return_home_button = false;
/* Private function prototypes -----------------------------------------------*/

static void scale_pitch_value_changed_cb(GtkRange *range, gpointer win) ;
static void scale_yaw_value_changed_cb(GtkRange *range, gpointer win) ;
static void on_capture_button_clicked_callback(GtkWidget *button, gpointer user_data) ;
static void on_record_button_clicked_callback(GtkWidget *button, gpointer user_data) ;
static void on_gimbal_mapping_button_clicked_callback(GtkWidget *button, gpointer user_data) ;
static void on_gimbal_lock_button_clicked_callback(GtkWidget *button, gpointer user_data) ;
static void on_gimbal_follow_button_clicked_callback(GtkWidget *button, gpointer user_data) ;
static void on_gimbal_return_home_button_clicked_callback(GtkWidget *button, gpointer user_data) ;
static void gui_window_create(void);

/** @brief      This function handle gui_interface write thread
*/
void *start_gui_interface_process_write_thread(void *args);

/** @brief      This function handle gui_interface read thread
*/
void *start_gui_interface_process_read_thread(void *args);

/* Private functions ---------------------------------------------------------*/
/** @brief      This function use inititalize gui_interface library
*/
gui_interface::gui_interface(/* args */)
{

}

/** @brief      This function use de-inititalize gui_interface library
*/
gui_interface::~gui_interface(/* args */)
{

}

/** @brief      This function use start gui_interface library
*/
void gui_interface::start(void)
{
    // int result = 0;

    // /// reset flag exit all thread
    // is_gui_interface_all_thread_exit = false;

    // /// create library write thread
    // result = pthread_create(&gui_interface_write_threadId, NULL, &start_gui_interface_process_write_thread, this);

    // /// check result
    // if(result) throw result;

    // result = pthread_create(&gui_interface_read_threadId, NULL, &start_gui_interface_process_read_thread, this);

    // /// check result
    // if(result) throw result;

    /// extension library functions is here
    
    gui_window_create();

    usleep(10000);
}

/** @brief      This function use stop gui_interface library
*/
void gui_interface::stop(void)
{
      LOG_WARN << "CLOSE ALL THREAD !!!" << END_LINE;

      is_gui_interface_all_thread_exit = true;

      pthread_join(gui_interface_write_threadId, NULL);
      pthread_join(gui_interface_read_threadId, NULL);
}

/** @brief      This function use quit gui_interface library
*/
void gui_interface::handle_quit(int sig)
{
    try {
        stop();

    } catch (int error) {
        LOG_WARN << "could not stop gui_interface !!!" << END_LINE;
    }
}

/** @brief
 *  @param[in]
	@return
*/

static void gui_table_create(void)
{
  table = gtk_table_new(1, 2, TRUE);
  gtk_table_set_row_spacings(GTK_TABLE(table), 10);
  gtk_table_set_col_spacings(GTK_TABLE(table), 10);
  gtk_container_add(GTK_CONTAINER(window), table);

  frame1 = gtk_frame_new("Camera");
  gtk_frame_set_shadow_type(GTK_FRAME(frame1), GTK_SHADOW_IN);
  frame2 = gtk_frame_new("Gimbal");
  gtk_frame_set_shadow_type(GTK_FRAME(frame2), GTK_SHADOW_OUT);

  gtk_table_attach_defaults(GTK_TABLE(table), frame1, 0, 1, 0, 1);
  gtk_table_attach_defaults(GTK_TABLE(table), frame2, 1, 2, 0, 1);

  gtk_widget_set_size_request(frame1, 5, 5);
  gtk_widget_set_size_request(frame2, 1, 1);

}

static void gui_scale_pitch_create(void)
{

  pitch_scale = gtk_scale_new_with_range(GTK_ORIENTATION_VERTICAL, -100, 100, 1);
  gtk_scale_set_draw_value(GTK_SCALE(pitch_scale), TRUE);
  gtk_range_set_value(GTK_RANGE(pitch_scale), 0);

  gtk_fixed_put(GTK_FIXED(gimbal_fixed), pitch_scale, 50, 55);
  gtk_widget_set_size_request(pitch_scale, 320, 200);

  pitch_label = gtk_label_new("pitch");
  gtk_misc_set_alignment(GTK_MISC(pitch_label), 0.0, 0);
  gtk_box_pack_start(GTK_BOX(hbox), pitch_label, FALSE, FALSE, 0);

    g_signal_connect(pitch_scale, "value-changed",
        G_CALLBACK(scale_pitch_value_changed_cb), pitch_label);
}

static void gui_scale_yaw_create(void)
{

  yaw_scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -100, 100, 1);
  gtk_scale_set_draw_value(GTK_SCALE(yaw_scale), TRUE);
  gtk_range_set_value(GTK_RANGE(yaw_scale), 0);

  gtk_fixed_put(GTK_FIXED(gimbal_fixed), yaw_scale, 270, 80);
  gtk_widget_set_size_request(yaw_scale, 200, 150);

  yaw_label = gtk_label_new("yaw");
  gtk_misc_set_alignment(GTK_MISC(yaw_label), 0.0, 0);
  gtk_box_pack_start(GTK_BOX(hbox), yaw_label, FALSE, FALSE, 0);

    g_signal_connect(yaw_scale, "value-changed",
        G_CALLBACK(scale_yaw_value_changed_cb), yaw_label);     
}

static void gui_button_gb_return_home_create(void)
{
  gb_return_home_button = gtk_button_new_with_label("HOME");
  gtk_fixed_put(GTK_FIXED(gimbal_fixed), gb_return_home_button, 10, 250);
  gtk_widget_set_size_request(gb_return_home_button, 100, 50);
  g_signal_connect(gb_return_home_button, "clicked", G_CALLBACK(on_gimbal_return_home_button_clicked_callback), NULL);    
}

static void gui_button_gb_mapping_create(void)
{
  gb_mapping_button = gtk_button_new_with_label("MAPPING");
  gtk_fixed_put(GTK_FIXED(gimbal_fixed), gb_mapping_button, 10, 95);
  gtk_widget_set_size_request(gb_mapping_button, 80, 30);
  g_signal_connect(gb_mapping_button, "clicked", G_CALLBACK(on_gimbal_mapping_button_clicked_callback), NULL);    
}

static void gui_button_gb_lock_create(void)
{
  gb_lock_button = gtk_button_new_with_label("LOCK");
  gtk_fixed_put(GTK_FIXED(gimbal_fixed), gb_lock_button, 10, 5);
  gtk_widget_set_size_request(gb_lock_button, 80, 30);
  g_signal_connect(gb_lock_button, "clicked", G_CALLBACK(on_gimbal_lock_button_clicked_callback), NULL);    
}

static void gui_button_gb_follow_create(void)
{
  gb_follow_button = gtk_button_new_with_label("FOLLOW");
  gtk_fixed_put(GTK_FIXED(gimbal_fixed), gb_follow_button, 10, 45);
  gtk_widget_set_size_request(gb_follow_button, 80, 30);
  g_signal_connect(gb_follow_button, "clicked", G_CALLBACK(on_gimbal_follow_button_clicked_callback), NULL);    
}

static void gui_button_camera_capture_create(void)
{
  capture_button = gtk_button_new_with_label("Capture");
  gtk_fixed_put(GTK_FIXED(camera_fixed), capture_button, 15, 20);
  gtk_widget_set_size_request(capture_button, 100, 80);
  g_signal_connect(capture_button, "clicked", G_CALLBACK(on_capture_button_clicked_callback), NULL);

}

static void gui_button_camera_record_create(void)
{
  record_button = gtk_button_new_with_label("Record");
  gtk_fixed_put(GTK_FIXED(camera_fixed), record_button, 15, 150);
  gtk_widget_set_size_request(record_button, 100, 80);
  g_signal_connect(record_button, "clicked", G_CALLBACK(on_record_button_clicked_callback), NULL);

}

static void gui_window_create(void)
{
    gtk_init(NULL, NULL);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 1024, 360);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_title(GTK_WINDOW(window), "PixyS-Example01");

    gui_table_create();
    
    camera_fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(frame1), camera_fixed);

    gimbal_fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(frame2), gimbal_fixed);

    gui_button_camera_capture_create();
    gui_button_camera_record_create();

    hbox = gtk_hbox_new(FALSE, 20);

    gui_scale_pitch_create();
    gui_scale_yaw_create();

    
    gui_button_gb_lock_create();
    gui_button_gb_follow_create();
    gui_button_gb_mapping_create();
    gui_button_gb_return_home_create();

    g_signal_connect(window, "destroy",
        G_CALLBACK(gtk_main_quit), NULL); 

    gtk_widget_show_all(window);

    gtk_main();
}


static void scale_pitch_value_changed_cb(GtkRange *range, gpointer win) 
{
    
   gdouble val = gtk_range_get_value(range);
   gchar *str = g_strdup_printf("%.f", val);    
   gtk_label_set_text(GTK_LABEL(win), str);

   s_pitch_value = (int)val;

   printf("pitch hscalse [%.f]\n\r", val);
   
   g_free(str);
}

static void scale_yaw_value_changed_cb(GtkRange *range, gpointer win) 
{
    
   gdouble val = gtk_range_get_value(range);
   gchar *str = g_strdup_printf("%.f", val);    
   gtk_label_set_text(GTK_LABEL(win), str);

   s_yaw_value = (int)val;

   printf("yaw hscalse [%.f]\n\r", val);
   
   g_free(str);
}

static void on_capture_button_clicked_callback(GtkWidget *button, gpointer user_data) 
{
  g_print("Button capture clicked\n");

  s_capture_button = true;
}

static void on_record_button_clicked_callback(GtkWidget *button, gpointer user_data) 
{
  g_print("Button record clicked\n");

  s_record_button = true;
}

static void on_gimbal_mapping_button_clicked_callback(GtkWidget *button, gpointer user_data) 
{
  g_print("Button gimbal mapping mode clicked\n");

  s_gb_mapping_button = true;
}

static void on_gimbal_lock_button_clicked_callback(GtkWidget *button, gpointer user_data) 
{
  g_print("Button gimbal lock mode clicked\n");

  s_gb_lock_button = true;
}

static void on_gimbal_follow_button_clicked_callback(GtkWidget *button, gpointer user_data) 
{
  g_print("Button button gimbal follow mode clicked\n");

  s_gb_follow_button = true;
}

static void on_gimbal_return_home_button_clicked_callback(GtkWidget *button, gpointer user_data) 
{
  g_print("Button button gimbal return home clicked\n");

  s_gb_return_home_button = true;
}

bool gui_interface::get_capture_button_press(void)
{
    if(s_capture_button == true)
    {
        s_capture_button = false;

        return true;
    }

    return false;
}

bool gui_interface::get_record_button_press(void)
{
    if(s_record_button == true)
    {
        s_record_button = false;

        return true;
    }

    return false;
}

int gui_interface::get_pitch_scale_value(void)
{
    return -s_pitch_value;
}

int gui_interface::get_yaw_scale_value(void)
{
    return -s_yaw_value;
}

bool gui_interface::get_return_home_button_press(void)
{
    if(s_gb_return_home_button == true)
    {
        s_gb_return_home_button = false;

        return true;
    }

    return false;
}

gui_interface::e_mode_button gui_interface::get_mode_button_press(void)
{
    if(s_gb_mapping_button == true)
    {
        s_gb_mapping_button = false;

        return gui_interface::e_mode_button::MODE_BUTTON_MAPPING;
    }

    if(s_gb_lock_button == true)
    {
        s_gb_lock_button = false;

        return gui_interface::e_mode_button::MODE_BUTTON_LOCK;
    }

    if(s_gb_follow_button == true)
    {
        s_gb_follow_button = false;

        return gui_interface::e_mode_button::MODE_BUTTON_FOLLOW;
    }

    return gui_interface::e_mode_button::MODE_BUTTON_NONE;
}

/** @brief      This function handle write gui_interface library
*/
void gui_interface::gui_interface_write_thread(void)
{
    LOG_INFO << "START THREAD !!!" << END_LINE; 

    while(is_gui_interface_all_thread_exit == false)
    {


        usleep(1000);
    }

    LOG_ERROR << "CLOSE THREAD !!!" << END_LINE;
}

void gui_interface::start_gui_interface_write_thread(void)
{
    gui_interface_write_thread();
}

/** @brief      This function handle read gui_interface library
*/
void gui_interface::gui_interface_read_thread(void)
{
    LOG_INFO << "START THREAD !!!" << END_LINE; 

    while(is_gui_interface_all_thread_exit == false)
    {


        usleep(1000);
    }

    LOG_ERROR << "CLOSE THREAD !!!" << END_LINE;
}

void gui_interface::start_gui_interface_read_thread(void)
{
    gui_interface_read_thread();
}

/** @brief      This function handle gui_interface write thread
*/
void *start_gui_interface_process_write_thread(void *args)
{
    /// handle write function here
    gui_interface *pgui_interface = (gui_interface *)args;

    pgui_interface->start_gui_interface_write_thread();

    return NULL;
}

/** @brief      This function handle gui_interface read thread
*/
void *start_gui_interface_process_read_thread(void *args)
{
    /// handle read function here
    gui_interface *pgui_interface = (gui_interface *)args;

    pgui_interface->start_gui_interface_read_thread();
    
    return NULL;
}
/************************ (C) COPYRIGHT GREMSY *****END OF FILE****************/