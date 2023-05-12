

/** 
  ******************************************************************************
  * @file    main.cpp
  * @author  Gremsy Team
  * @version V1.0.0
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


#include "Common.h"
#include <signal.h>
#include "gui_interface.h"
#include "camera_interface.h"
#include "gimbal_interface.h"
#include "linux_serial_port.h"
#include "posix_thread_manager.h"

#define CAMERA_ENABLE 1


using namespace GSDK;
using namespace Linux;

static pthread_t sdk_threadId;
#if (CAMERA_ENABLE == 1)
Camera_Interface    camera;
#endif

gui_interface       gui;


char *uart_name = (char *)"/dev/ttyUSB0";
int baudrate = 115200;

Linux_Serial_Port serial_port(uart_name, baudrate);
Gimbal_Interface gimbal_interface(&serial_port, true, 1, MAV_COMP_ID_ONBOARD_COMPUTER, MAVLINK_GIMBAL_V1);

// ------------------------------------------------------------------------------
//   Quit Signal Handler
// ------------------------------------------------------------------------------
// this function is called when you press Ctrl-C
void quit_handler(int sig);

static void camera_capture_button_handler(void)
{
    if(gui.get_capture_button_press())
    {
        #if (CAMERA_ENABLE == 1)
        camera.take_photo(Camera_Interface::Camera_shooting_type_t::CAMERA_SHOTTING_TYPE_SINGLE);
        #endif

        LOG_INFO << "camera capture" << END_LINE;
    }
}

static void camera_record_button_handler(void)
{
    static bool record_state = true;

    if(gui.get_record_button_press())
    {
        #if (CAMERA_ENABLE == 1)
        camera.set_record(record_state);
        #endif

        LOG_INFO << "camera record [" << record_state << "]" << END_LINE;

        record_state = !record_state;   
    }
}


static void gimbal_setting_default_param_handler(void)
{
    while(!gimbal_interface.get_connection())
    {
        usleep(500000);
    }

    // Setting axis for control. see the struct gimbal_config_axis_t
    gimbal_config_axis_t config = { 0 };
    config = { DIR_CW, 180, 20, 180, 20};   // Tilt
    gimbal_interface.set_gimbal_config_tilt_axis(config);
    config = { DIR_CW, 180, 20, 0, 0};    // Roll
    gimbal_interface.set_gimbal_config_roll_axis(config);
    config = { DIR_CW, 180, 20, 180, 20};  // Yaw
    gimbal_interface.set_gimbal_config_pan_axis(config);

    // Motor control likes: Stiffness, holdstrength, gyro filter, output filter and gain
    // Uncomment block below to configure gimbal motor
    // gimbal_motor_control_t tilt = { 20, 30 };
    // gimbal_motor_control_t roll = { 30, 30 };
    // gimbal_motor_control_t pan = { 50, 30 };
    // gimbal_interface.set_gimbal_motor_control( tilt, roll, pan, 5, 1, 120 ); 

    uint8_t enc_value_rate = 10;
    uint8_t orien_rate = 10;
    uint8_t imu_rate = 10;
    printf("Set encoder messages rate: %dHz\n", enc_value_rate);
    gimbal_interface.set_msg_encoder_rate(enc_value_rate);
    printf("Set mount orientation messages rate: %dHz\n", orien_rate);
    gimbal_interface.set_msg_mnt_orient_rate(orien_rate);
    printf("Set gimbal device attitude status messages rate: %dHz\n", orien_rate);
    gimbal_interface.set_msg_attitude_status_rate(orien_rate);
    printf("Set raw imu messgaes rate: %dHz\n", imu_rate);
    gimbal_interface.set_msg_raw_imu_rate(imu_rate);
    printf("Set gimbal send raw encoder value.\n");
    gimbal_interface.set_gimbal_encoder_type_send(true);
    printf("Request gimbal device information.\n");
    gimbal_interface.request_gimbal_device_info();

}

static void gimbal_control_pitch_yaw_rate_handler(void)
{
    int pitch_value = gui.get_pitch_scale_value();
    int yaw_value = gui.get_yaw_scale_value();

    result_t result = UNKNOWN;

    if(gui.get_return_home_button_press())
    {
        do {           
            result = gimbal_interface.set_gimbal_reset_mode(GIMBAL_RESET_MODE_PITCH_AND_YAW);

            if(result == SUCCESS)
            {
                LOG_INFO << "Setting gimbal RESET mode SUCCESS !!!" << END_LINE;
            }
            else if(result == ERROR || result == DENIED || result == TIMEOUT)
            {
                LOG_ERROR << "Setting gimbal RESET mode FAILED !!!" << result << END_LINE;
            }
        } while (result != SUCCESS);
    }
    else
    {
        while(!gimbal_interface.get_connection())
        {
            usleep(500000);
        }
        
        gimbal_interface.set_gimbal_rotation_rate_sync(pitch_value, 0, yaw_value);
    }
    
}

static void gimbal_mode_control_handler(void)
{
    result_t result = UNKNOWN;

    gui_interface::e_mode_button mode = gui.get_mode_button_press();

    if(mode == gui_interface::e_mode_button::MODE_BUTTON_MAPPING)
    {
        do {           
            result = gimbal_interface.set_gimbal_mapping_mode_sync();

            if(result == SUCCESS)
            {
                LOG_INFO << "Setting gimbal MAPPING mode SUCCESS !!!" << END_LINE;
            }
            else if(result == ERROR || result == DENIED || result == TIMEOUT)
            {
                LOG_ERROR << "Setting gimbal MAPPING mode FAILED !!!" << result << END_LINE;
            }
        } while (result != SUCCESS);
    }
    else if(mode == gui_interface::e_mode_button::MODE_BUTTON_LOCK)
    {
        do {           
            result = gimbal_interface.set_gimbal_lock_mode_sync();

            if(result == SUCCESS)
            {
                LOG_INFO << "Setting gimbal LOCK mode SUCCESS !!!" << END_LINE;
            }
            else if(result == ERROR || result == DENIED || result == TIMEOUT)
            {
                LOG_ERROR << "Setting gimbal LOCK mode FAILED !!!" << result << END_LINE;
            }
        } while (result != SUCCESS);
    }
    else if(mode == gui_interface::e_mode_button::MODE_BUTTON_FOLLOW)
    {
        do {           
            result = gimbal_interface.set_gimbal_follow_mode_sync();

            if(result == SUCCESS)
            {
                LOG_INFO << "Setting gimbal FOLLOW mode SUCCESS !!!" << END_LINE;
            }
            else if(result == ERROR || result == DENIED || result == TIMEOUT)
            {
                LOG_ERROR << "Setting gimbal FOLLOW mode FAILED !!!" << result << END_LINE;
            }
        } while (result != SUCCESS);
    }
}

/** @brief      This function handle gui_interface write thread
*/
void *sdk_process_thread(void *args)
{
    #if (GIMBAL_ENABLE == 1)
    gimbal_setting_default_param_handler();
    #endif

    for(;;)
    {
        camera_capture_button_handler();
        camera_record_button_handler();

        gimbal_control_pitch_yaw_rate_handler();
        gimbal_mode_control_handler();

        usleep(100);
    }
}

static void SDK_init(void)
{
    int result = 0;

    LOG_INFO << "---------------------------------------" << END_LINE;

    #if (CAMERA_ENABLE == 1)
    camera.start();
    #endif

    serial_port.start();
    gimbal_interface.start();

    result = pthread_create(&sdk_threadId, NULL, &sdk_process_thread, 0);

    gui.start(); 
}

int main(int argc, char *argv[])
{
    int result = 0;

    signal(SIGINT, quit_handler);

    SDK_init();

    while(1)
    {

    }
    
    LOG_ERROR << "EXIT !!!" << END_LINE;

    return 0;
}

// ------------------------------------------------------------------------------
//   Quit Signal Handler
// ------------------------------------------------------------------------------
// this function is called when you press Ctrl-C
void quit_handler(int sig)
{
    LOG_WARN << "TERMINATING AT USER REQUEST\n\r";

    #if (CAMERA_ENABLE == 1)
    try {
    camera.handle_quit(sig);

    } catch (int error) {}
    #endif

    try {
        gui.handle_quit(sig);

    } catch (int error) {}

    // autopilot interface
    try {
        gimbal_interface.handle_quit();

    } catch (int error) {}

    // serial port
    try {
        serial_port.stop();

    } catch (int error) {}

    usleep(100000); // 10Hz

    // end program here
    exit(0);
}