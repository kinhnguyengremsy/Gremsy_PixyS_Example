/** 
  ******************************************************************************
  * @file    gui_interface.h
  * @author  Gremsy Team
  * @version V2.0.0
  * @date    ${date}
  * @brief   This file contains all the functions prototypes for the gui_interface.c
  *          firmware library
  *
  ******************************************************************************
  * @Copyright
  * COPYRIGHT NOTICE: (c) 2018 Gremsy. All rights reserved.
  *
  * The information contained herein is confidential
  * property of Company. The use, copying, transfer or 
  * disclosure of such information is prohibited except
  * by express written agreement with Company.
  *
  ******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __GUI_INTERFACE_
#define __GUI_INTERFACE_

/* Includes ------------------------------------------------------------------*/
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string> 
#include <stdint.h>
#include <stdbool.h>
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported class ------------------------------------------------------------*/
class gui_interface
{
    public:

        enum e_mode_button
        {
          MODE_BUTTON_NONE = 0x00,
          MODE_BUTTON_MAPPING,
          MODE_BUTTON_LOCK,
          MODE_BUTTON_FOLLOW,
          MODE_BUTTON_COUNT

        };

        gui_interface(/* args */);
        ~gui_interface();

        /// global variables here

        void start(void);
        void stop(void);

        void start_gui_interface_write_thread(void);
        void start_gui_interface_read_thread(void);

        void handle_quit(int sig);

        /// global library function here
        bool get_capture_button_press(void);
        bool get_record_button_press(void);
        int get_pitch_scale_value(void);
        int get_yaw_scale_value(void);
        bool get_return_home_button_press(void);
        e_mode_button get_mode_button_press(void);

    private:

        /// private variables here
        bool is_gui_interface_all_thread_exit = false;

        pthread_t gui_interface_write_threadId;
        pthread_t gui_interface_read_threadId;

        /// private thread function here
        void gui_interface_write_thread(void);
        void gui_interface_read_thread(void);

        /// private library function here
};
/* Exported functions --------------------------------------------------------*/

#endif /* __GUI_INTERFACE_ */

/************************ (C) COPYRIGHT GREMSY *****END OF FILE****************/