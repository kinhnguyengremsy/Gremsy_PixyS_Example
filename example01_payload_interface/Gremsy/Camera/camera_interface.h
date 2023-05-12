/** 
  ******************************************************************************
  * @file    camera_interface.h
  * @author  Gremsy Team
  * @version V2.0.0
  * @date    ${date}
  * @brief   This file contains all the functions prototypes for the camera_interface.c
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

#ifndef __CAMERA_INTERFACE_H_
#define __CAMERA_INTERFACE_H_

/* Includes ------------------------------------------------------------------*/
#include <cstdlib>
#include <iostream>
#if defined(USE_EXPERIMENTAL_FS)
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#include <filesystem>
namespace fs = std::filesystem;
#if defined(__APPLE__)
#include <unistd.h>
#endif
#endif

#include <cstdint>
#include <iomanip>
#include "CRSDK/CameraRemote_SDK.h"
#include "CameraDevice.h"
#include "Text.h"

// #include <exiv2/exiv2.hpp>
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
namespace SDK = SCRSDK;
/* Exported class ------------------------------------------------------------*/
class Camera_Interface
{

public:

typedef enum _Camera_shooting_type_t
{
  CAMERA_SHOTTING_TYPE_SINGLE = 0x00,
  CAMERA_SHOTTING_TYPE_CONTINUOUS,

}Camera_shooting_type_t;

typedef enum _e_camera_record_state
{
  CAMERA_RECORD_STATE_IDLE = 0x00,
  CAMERA_RECORD_STATE_START,
  CAMERA_RECORD_STATE_STOP,
  CAMERA_RECORD_STATE_ERROR,
  CAMERA_RECORD_TOTAL_STATE

}e_camera_record_state;

    Camera_Interface(/* args */);
    ~Camera_Interface();

    void start();
    void stop();

    void start_read_thread(void);
    void start_write_thread(void);

    void start_monitor_thread(void);

    void handle_quit(int sig);

    bool set_connection(bool state);
    bool get_connection(void);

    void runSample(void);

    bool take_photo(Camera_shooting_type_t type);
    void set_record(bool state);

private:
    /* data */

    typedef std::shared_ptr<cli::CameraDevice> CameraDevicePtr;
    typedef std::vector<CameraDevicePtr> CameraDeviceList;
    CameraDeviceList cameraList; // all
    std::int32_t cameraNumUniq = 1;
    std::int32_t selectCamera = 1;

    CameraDevicePtr camera ;

    bool is_read_write_threadExit = false;
    bool is_camera_connection = false;

    pthread_t read_tid  = 0;
    pthread_t write_tid = 0;
    pthread_t monitor_tid = 0;

    void read_thread(void);
    void write_thread(void);
    void monitor_thread(void);

    uint16_t get_still_image_store_destination();
    bool set_image_store_locations(void);

    e_camera_record_state isRecording(bool state);
};

/* Exported functions --------------------------------------------------------*/

#endif /* __CAMERA_INTERFACE_H_ */

/************************ (C) COPYRIGHT GREMSY *****END OF FILE****************/