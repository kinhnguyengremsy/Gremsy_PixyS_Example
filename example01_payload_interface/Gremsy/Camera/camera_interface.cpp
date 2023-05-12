/** 
  ******************************************************************************
  * @file    camera_interface.cpp
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
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "Common.h"
#include "camera_interface.h"
#include "Text.h"
#include <sys/stat.h>
#include <vector>
#include <dirent.h>
#include <cmath>
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define LIVEVIEW_ENB
// #define MSEARCH_ENB
#define HAS_CAMERA
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

SDK::ICrEnumCameraObjectInfo* camera_list = nullptr;

bool bQuit = false;
auto enum_status = 0;
auto ncams = 0;
auto a = 0;
/* Private function prototypes -----------------------------------------------*/
void *start_camera_interface_read_thread(void *args);
void *start_camera_interface_write_thread(void *args);
void *start_camera_monitor_thread(void *args);
/* Private functions ---------------------------------------------------------*/

/** @brief
 *  @param[in]
	@return
*/
Camera_Interface::Camera_Interface(/* args */)
{
    // Change global locale to native locale
    std::locale::global(std::locale(""));

    // Make the stream's locale the same as the current global locale
    cli::tin.imbue(std::locale());
    cli::tout.imbue(std::locale());

    cli::tout << "RemoteSampleApp v1.07.00 running...\n\n";

    CrInt32u version = SDK::GetSDKVersion();
    int major = (version & 0xFF000000) >> 24;
    int minor = (version & 0x00FF0000) >> 16;
    int patch = (version & 0x0000FF00) >> 8;
    // int reserved = (version & 0x000000FF);

    cli::tout << "Remote SDK version: ";
    cli::tout << major << "." << minor << "." << std::setfill(TEXT('0')) << std::setw(2) << patch << "\n";

    // Load the library dynamically
    // cr_lib = cli::load_cr_lib();

    cli::tout << "Initialize Remote SDK...\n";

    #if defined(__APPLE__)
            char path[MAC_MAX_PATH]; /*MAX_PATH*/
            memset(path, 0, sizeof(path));
            if(NULL == getcwd(path, sizeof(path) - 1)){
                cli::tout << "Folder path is too long.\n";
                std::exit(EXIT_FAILURE);
                return;
            }
            getcwd(path, sizeof(path) -1);
            cli::tout << "Working directory: " << path << '\n';
    #else
        // fs::current_path("/home/gremsy/memory/Image");
        cli::tout << "Working directory: " << fs::current_path() << '\n';
    #endif
    // auto init_success = cr_lib->Init(0);
    auto init_success = SDK::Init();
    if (!init_success) {
        cli::tout << "Failed to initialize Remote SDK. Terminating.\n";
        // cr_lib->Release();
        SDK::Release();
        std::exit(EXIT_FAILURE);
    }
    cli::tout << "Remote SDK successfully initialized.\n\n";

    #ifdef MSEARCH_ENB

        cli::tout << "Enumerate connected camera devices...\n";
        // SDK::ICrEnumCameraObjectInfo* camera_list = nullptr;
        // auto enum_status = cr_lib->EnumCameraObjects(&camera_list, 3);
        // auto enum_status = SDK::EnumCameraObjects(&camera_list);
        enum_status = SDK::EnumCameraObjects(&camera_list);
        if (CR_FAILED(enum_status) || camera_list == nullptr) {
            cli::tout << "No cameras detected. Connect a camera and retry.\n";
            // cr_lib->Release();
            SDK::Release();
            std::exit(EXIT_FAILURE);
        }
        // auto ncams = camera_list->GetCount();
        ncams = camera_list->GetCount();
        cli::tout << "Camera enumeration successful. " << ncams << " detected.\n\n";

        for (CrInt32u i = 0; i < ncams; ++i) {
            auto camera_info = camera_list->GetCameraObjectInfo(i);
            // camera_info = camera_list->GetCameraObjectInfo(i);
            cli::text conn_type(camera_info->GetConnectionTypeName());
            cli::text model(camera_info->GetModel());
            cli::text id = TEXT("");
            if (TEXT("IP") == conn_type) {
                cli::NetworkInfo ni = cli::parse_ip_info(camera_info->GetId(), camera_info->GetIdSize());
                id = ni.mac_address;
            }
            else id = ((TCHAR*)camera_info->GetId());
            cli::tout << '[' << i + 1 << "] " << model.data() << " (" << id.data() << ")\n";
        }

        cli::tout << std::endl << "Connect to camera with input number...\n";
        cli::tout << "input> ";
        cli::text connectNo;
        std::getline(cli::tin, connectNo);
        cli::tout << '\n';

        cli::tsmatch smatch;
        CrInt32u no = 0;
        while (true) {
            no = 0;
            if (std::regex_search(connectNo, smatch, cli::tregex(TEXT("[0-9]")))) {
                no = stoi(connectNo);
                if (no == 0)
                    break; // finish

                if (camera_list->GetCount() < no) {
                    cli::tout << "input value over \n";
                    cli::tout << "input> "; // Redo
                    std::getline(cli::tin, connectNo);
                    continue;
                }
                else
                    break; // ok
            }
            else
                break; // not number
        }

        if (no == 0) {
            cli::tout << "Invalid Number. Finish App.\n";
            SDK::Release();
            std::exit(EXIT_FAILURE);
        }

        // typedef std::shared_ptr<cli::CameraDevice> CameraDevicePtr;
        // typedef std::vector<CameraDevicePtr> CameraDeviceList;
        // CameraDeviceList cameraList; // all
        // std::int32_t cameraNumUniq = 1;
        // std::int32_t selectCamera = 1;

        cli::tout << "Connect to selected camera...\n";
        auto* camera_info = camera_list->GetCameraObjectInfo(no - 1);
        // camera_info = camera_list->GetCameraObjectInfo(no - 1);

        cli::tout << "Create camera SDK camera callback object.\n";
        // CameraDevicePtr camera = CameraDevicePtr(new cli::CameraDevice(cameraNumUniq, nullptr, camera_info));
        camera = CameraDevicePtr(new cli::CameraDevice(cameraNumUniq, nullptr, camera_info));
        cameraList.push_back(camera); // add 1st

        cli::tout << "Release enumerated camera list.\n";
        camera_list->Release();

        // loop-B : TOP-MENU ____ Switching between 'Remote Control Mode' connection and 'Contents Transfer Mode (MTP)' connection.
        while (true)
        {
            cli::tout << "<< TOP-MENU >>\nWhat would you like to do? Enter the corresponding number.\n";
            cli::tout
                << "(1) Connect (Remote Control Mode)\n"
                << "(2) Connect (Contents Transfer Mode)\n"
                // << "(f) Release Device \n"
                << "(x) Exit\n";

            cli::tout << "input> ";
            cli::text action;
            std::getline(cli::tin, action);
            cli::tout << '\n';

            if (action == TEXT("x")) { /* Exit app */
                bQuit = true;
                CameraDeviceList::const_iterator it = cameraList.begin();
                for (std::int32_t j = 0; it != cameraList.end(); ++j, ++it) {
                    if ((*it)->is_connected()) {
                        cli::tout << "Initiate disconnect sequence.\n";
                        auto disconnect_status = (*it)->disconnect();
                        if (!disconnect_status) {
                            // try again
                            disconnect_status = (*it)->disconnect();
                        }
                        if (!disconnect_status)
                            cli::tout << "Disconnect failed to initiate.\n";
                        else
                            cli::tout << "Disconnect successfully initiated!\n\n";
                    }
                    (*it)->release();
                }
                break; // exit loop-B
            }
            else if (action == TEXT("1")) { /* connect Remote */
                if (camera->is_connected()) {
                    cli::tout << "Please disconnect\n";
                }
                else {
                        camera->connect(SDK::CrSdkControlMode_Remote, SDK::CrReconnecting_ON);
                }
                break; // exit loop-B
            }
            else if (action == TEXT("2")) { /* connect MTP */
                if (camera->is_connected()) {
                    cli::tout << "Please disconnect\n";
                }
                else {
                    camera->connect(SDK::CrSdkControlMode_ContentsTransfer, SDK::CrReconnecting_ON);
                }
                break; // exit loop-B
            }
            cli::tout << std::endl;

        } // end of loop-B

    #else

        #ifdef HAS_CAMERA
            cli::tout << "Enumerate connected camera devices...\n";
            enum_status = SDK::EnumCameraObjects(&camera_list);
            if (CR_FAILED(enum_status) || camera_list == nullptr) {
                cli::tout << "No cameras detected. Connect a camera and retry.\n";
                SDK::Release();
                std::exit(EXIT_FAILURE);
            }

            ncams = camera_list->GetCount();
            cli::tout << "Camera enumeration successful. " << ncams << " detected.\n\n";

            for (CrInt32u i = 0; i < ncams; ++i) {
                auto camera_info = camera_list->GetCameraObjectInfo(i);
                cli::text conn_type(camera_info->GetConnectionTypeName());
                cli::text model(camera_info->GetModel());
                cli::text id = TEXT("");
                if (TEXT("IP") == conn_type) {
                    cli::NetworkInfo ni = cli::parse_ip_info(camera_info->GetId(), camera_info->GetIdSize());
                    id = ni.mac_address;
                }
                else id = ((TCHAR*)camera_info->GetId());
                cli::tout << '[' << i + 1 << "] " << model.data() << " (" << id.data() << ")\n";
            }

            CrInt32u no = 0;

            cli::tout << "Number of camera count = " << ncams <<'\n';
            no = ncams;

            cli::tout << "Connect to selected camera...\n";
            auto* camera_info = camera_list->GetCameraObjectInfo(no - 1);

            cli::tout << "Create camera SDK camera callback object.\n";
            camera = CameraDevicePtr(new cli::CameraDevice(cameraNumUniq, nullptr, camera_info));
            cameraList.push_back(camera); // add 1st

            cli::tout << "Release enumerated camera list.\n";
            camera_list->Release();

            if (camera->is_connected()) {
                cli::tout << "Please disconnect\n";
            }
            else {
                camera->connect(SDK::CrSdkControlMode_Remote, SDK::CrReconnecting_ON);
            }
        #endif
    #endif

    is_camera_connection = true;
}

Camera_Interface::~Camera_Interface()
{
}

/** @brief      start library camera interface
 *  @param[in]
	@return
*/
void Camera_Interface::start()
{
    int result = 0;

    is_read_write_threadExit = false;

    // --------------------------------------------------------------------------
    //   WRITE THREAD
    // --------------------------------------------------------------------------
    result = pthread_create(&write_tid, NULL, &start_camera_interface_write_thread, this);

    if (result) throw result;

    usleep(100000); // 10Hz

    // --------------------------------------------------------------------------
    //   READ THREAD
    // --------------------------------------------------------------------------
    result = pthread_create(&read_tid, NULL, &start_camera_interface_read_thread, this);

    if (result) throw result;

    usleep(100000); // 10Hz

    result = pthread_create(&monitor_tid, NULL, &start_camera_monitor_thread, this);

    if (result) throw result;

    usleep(100000); // 10Hz

    // pthread_join(read_tid, NULL);
    // pthread_join(write_tid, NULL);
    // pthread_join(mavlinkMonitor_tid, NULL);

    // --------------------------------------------------------------------------
    //   CHECK FOR MESSAGES
    // --------------------------------------------------------------------------
    do {
        if (is_read_write_threadExit) {
            LOG_INFO << "Waitting for camera connections !!! \n\r";
            return;
        }

        usleep(500000); // Check at 2Hz
    } while (!get_connection());

    LOG_INFO << "Camera Connected !!!\n\r";

    #ifdef HAS_CAMERA
        if(set_image_store_locations())
        {
            LOG_INFO << "success !!!" << END_LINE ;
        }
        else
        {
            LOG_ERROR << "failed !!!" << END_LINE ;
        }
    #endif
}

/** @brief      stop library camera interface
 *  @param[in]
	@return
*/
void Camera_Interface::stop()
{
    // --------------------------------------------------------------------------
    //   CLOSE THREADS
    // --------------------------------------------------------------------------
    LOG_INFO << "CLOSE_ALL_THREAD !!! \n\r";
    // signal exit
    is_read_write_threadExit = true;

    sleep(1);

    cli::tout << "Release SDK resources.\n";
    // cr_lib->Release();
    SDK::Release();

    // cli::free_cr_lib(&cr_lib);

    cli::tout << "Exiting application.\n";
    std::exit(EXIT_SUCCESS);    

    pthread_join(read_tid, NULL);
    pthread_join(write_tid, NULL);
    pthread_join(monitor_tid, NULL);
    // now the read and write threads are closed
}


void Camera_Interface::runSample(void)
{
    // Overview
    //   loop-A : main loop
    //   loop-C : REMOTE-MENU
    //   loop-D : MTP-MENU

    // loop-A
    for (;;) {

        // 1,2   = break of TOP-MENU, continue to REMOTE-MENU or MTP-MENU
        // x     = quit the app
        // other = ignore

        // check quit
        if (bQuit) break; // exit loop-A

        // ------------------------
        // Remote
        // ------------------------
        if (SDK::CrSdkControlMode_Remote == camera->get_sdkmode())
        {
            // loop-C
            while (true)
            {
                if ((SDK::CrSSHsupportValue::CrSSHsupport_ON == camera->get_sshsupport()) && (false == camera->is_getfingerprint()))
                {
                    // Fingerprint is incorrect
                    break;
                }
                cli::tout << "<< REMOTE-MENU 1 >>\nWhat would you like to do? Enter the corresponding number.\n";
                cli::tout
                    << "(s) Status display and camera switching \n"
                    << "(0) Disconnect and return to the top menu\n"
                    << "(1) Shutter Release \n"
                    << "(2) Shutter Half Release in AF mode \n"
                    << "(3) Shutter Half and Full Release in AF mode \n"
                    << "(4) Continuous Shooting \n"
                    << "(5) Aperture \n"
                    << "(6) ISO \n"
                    << "(7) Shutter Speed \n"
                    << "(8) Live View \n"
                    << "(9) Live View Image Quality \n"
                    << "(a) Position Key Setting \n"
                    << "(b) Exposure Program Mode \n"
                    << "(c) Still Capture Mode(Drive mode) \n"
                    << "(d) Focus Mode \n"
                    << "(e) Focus Area \n"
    #if defined(LIVEVIEW_ENB)
                    << "(lv) LiveView Enable \n"
    #endif
                    << "(11) FELock \n"
                    << "(12) AWBLock \n"
                    << "(13) AF Area Position(x,y) \n"
                    << "(14) Selected MediaFormat \n"
                    << "(15) Movie Rec Button \n"
                    << "(16) White Balance \n"
                    << "(17) Custom WB \n"
                    << "(18) Zoom Operation \n"
                    << "(19) Zoom Speed Type \n"
                    << "(20) Preset Focus \n"
                    << "(21) REMOTE-MENU 2 \n"
                    ;

                cli::tout << "input> ";
                cli::text action;
                std::getline(cli::tin, action);
                cli::tout << '\n';

                if (action == TEXT("s")) { /* status display and device selection */
                    cli::tout << "Status display and camera switching.\n";
    #if defined(LIVEVIEW_ENB)
                    cli::tout << "number - connected - lvEnb - model - id\n";
    #else
                    cli::tout << "number - connected - model - id\n";
    #endif
                    CameraDeviceList::const_iterator it = cameraList.begin();
                    for (std::int32_t i = 0; it != cameraList.end(); ++i, ++it)
                    {
                        cli::text model = (*it)->get_model();
                        if (model.size() < 10) {
                            int32_t apendCnt = 10 - model.size();
                            model.append(apendCnt, TEXT(' '));
                        }
                        cli::text id = (*it)->get_id();
                        std::uint32_t num = (*it)->get_number();
                        if (selectCamera == num) { cli::tout << "* "; }
                        else { cli::tout << "  "; }
                        cli::tout << std::setfill(TEXT(' ')) << std::setw(4) << std::left << num
                            << " - " << ((*it)->is_connected() ? "true " : "false")
    #if defined(LIVEVIEW_ENB)
                            << " - " << ((*it)->is_live_view_enable() ? "true " : "false")
    #endif
                            << " - " << model.data()
                            << " - " << id.data() << std::endl;
                    }

                    cli::tout << std::endl << "Selected camera number = [" << selectCamera << "]" << std::endl << std::endl;

                    cli::tout << "Choose a number :\n";
                    cli::tout << "[-1] Cancel input\n";
    #ifdef MSEARCH_ENB
                    cli::tout << "[0]  Create new CameraDevice\n";
    #endif
                    cli::tout << "[1]  Switch cameras for controls\n";
                    cli::tout << std::endl << "input> ";

                    cli::text input;
                    std::getline(cli::tin, input);
                    cli::text_stringstream ss(input);
                    int selected_index = 0;
                    ss >> selected_index;

    #ifdef MSEARCH_ENB
                    if (selected_index < 0 || 1 < selected_index) {
                        cli::tout << "Input cancelled.\n";
                    }
    #else
                    if (selected_index < 1 || 1 < selected_index) {
                        cli::tout << "Input cancelled.\n";
                    }
    #endif
    #ifdef MSEARCH_ENB
                    // new camera connect
                    if (0 == selected_index) 
                    {
                        enum_status = SDK::EnumCameraObjects(&camera_list);
                        if (CR_FAILED(enum_status) || camera_list == nullptr) {
                            cli::tout << "No cameras detected. Connect a camera and retry.\n";
                        }
                        else
                        {
                            cli::tout << "[-1] Cancel input\n";
                            ncams = camera_list->GetCount();
                            for (CrInt32u i = 0; i < ncams; ++i) {
                                auto camera_info = camera_list->GetCameraObjectInfo(i);
                                cli::text conn_type(camera_info->GetConnectionTypeName());
                                cli::text model(camera_info->GetModel());
                                cli::text id = TEXT("");
                                if (TEXT("IP") == conn_type) {
                                    cli::NetworkInfo ni = cli::parse_ip_info(camera_info->GetId(), camera_info->GetIdSize());
                                    id = ni.mac_address;
                                }
                                else id = ((TCHAR*)camera_info->GetId());
                                cli::tout << '[' << i + 1 << "] " << model.data() << " (" << id.data() << ") ";
                                CameraDeviceList::const_iterator it = cameraList.begin();
                                for (std::int32_t j = 0; it != cameraList.end(); ++j, ++it){
                                    cli::text alreadyId = (*it)->get_id();
                                    if (0 == id.compare(alreadyId)) {
                                        cli::tout << "*";
                                        break;
                                    }
                                }
                                cli::tout << std::endl;
                            }

                            cli::tout << std::endl << "idx input> ";
                            std::getline(cli::tin, input);
                            cli::text_stringstream ss2(input);
                            int selected_no = 0;
                            ss2 >> selected_no;

                            if (selected_no < 1 || (std::int32_t)ncams < selected_no) {
                                cli::tout << "Input cancelled.\n";
                            }
                            else {
                                auto camera_info = camera_list->GetCameraObjectInfo(selected_no - 1);
                                cli::text conn_type(camera_info->GetConnectionTypeName());
                                cli::text model_select(camera_info->GetModel());
                                cli::text id_select = TEXT("");
                                if (TEXT("IP") == conn_type) {
                                    cli::NetworkInfo ni = cli::parse_ip_info(camera_info->GetId(), camera_info->GetIdSize());
                                    id_select = ni.mac_address;
                                }
                                else id_select = ((TCHAR*)camera_info->GetId());
                                bool findAlready = false;
                                CameraDeviceList::const_iterator it = cameraList.begin();
                                for (std::int32_t j = 0; it != cameraList.end(); ++j, ++it) {
                                    if ((0 == (*it)->get_model().compare(model_select)) &&
                                        (0 == (*it)->get_id().compare(id_select))) {
                                        findAlready = true;
                                        cli::tout << "Already connected!\n";
                                        break;
                                    }
                                }
                                if (false == findAlready) {
                                    std::int32_t newNum = cameraNumUniq + 1;
                                    CameraDevicePtr newCam = CameraDevicePtr(new cli::CameraDevice(newNum, nullptr, camera_info));
                                    cameraNumUniq = newNum;
                                    cameraList.push_back(newCam); // add
                                    camera = newCam; // switch target
                                    selectCamera = cameraNumUniq; // latest
                                    break; // exit loop-C
                                }
                            }
                            camera_list->Release();
                        }
                    }
    #endif
                    // switch device
                    else if (1 == selected_index) {
                        cli::tout << std::endl << "number input> ";
                        std::getline(cli::tin, input);
                        cli::text_stringstream ss3(input);
                        int input_no = 0;
                        ss3 >> input_no;

                        if (input_no < 1) {
                            cli::tout << "Input cancelled.\n";
                        }
                        else {
                            bool findTarget = false;
                            CameraDeviceList::const_iterator it = cameraList.begin();
                            for (; it != cameraList.end(); ++it) {
                                if ((*it)->get_number() == input_no) {
                                    findTarget = true;
                                    camera = (*it);
                                    selectCamera = input_no;
                                    break;
                                }
                            }
                            if (!findTarget) {
                                cli::tout << "The specified camera cannot be found!\n";
                            }
                        }
                    }
                } // end menu-s

                else if (action == TEXT("0")) { /* Return top menu */
                    if (camera->is_connected()) {
                        camera->disconnect();
                    }
                    break; // exit loop-B
                }
                else if (action == TEXT("1")) { /* Take photo */
                    camera->capture_image();
                }
                else if (action == TEXT("2")) { /* S1 Shooting */
                    camera->s1_shooting();
                }
                else if (action == TEXT("3")) { /* AF Shutter */
                    camera->af_shutter();
                }
                else if (action == TEXT("4")) { /* Continuous Shooting */
                    camera->continuous_shooting();
                }
                else if (action == TEXT("5")) { /* Aperture. */
                    camera->get_aperture();
                    camera->set_aperture();
                }
                else if (action == TEXT("6")) { /* ISO */
                    camera->get_iso();
                    camera->set_iso();
                }
                else if (action == TEXT("7")) { /* Shutter Speed */
                    camera->get_shutter_speed();
                    camera->set_shutter_speed();
                }
                else if (action == TEXT("8")) { /* Live View */
                    camera->get_live_view();
                }
                else if (action == TEXT("9")) { /* Live View Image Quality */
                    camera->get_live_view_image_quality();
                    camera->set_live_view_image_quality();
                }
                else if (action == TEXT("a")) { /* Position Key Setting */
                    camera->get_position_key_setting();
                    camera->set_position_key_setting();
                }
                else if (action == TEXT("b")) { /* Exposure Program Mode */
                    camera->get_exposure_program_mode();
                    camera->set_exposure_program_mode();
                }
                else if (action == TEXT("c")) { /* Still Capture Mode(Drive mode) */
                    camera->get_still_capture_mode();
                    camera->set_still_capture_mode();
                }
                else if (action == TEXT("d")) { /* Focus Mode */
                    camera->get_focus_mode();
                    camera->set_focus_mode();
                }
                else if (action == TEXT("e")) { /* Focus Area */
                    camera->get_focus_area();
                    camera->set_focus_area();
                }
                else if (action == TEXT("11")) { /* FELock */
                    cli::tout << "Flash device required.";
                    camera->execute_lock_property((CrInt16u)SDK::CrDevicePropertyCode::CrDeviceProperty_FEL);
                }
                else if (action == TEXT("12")) { /* AWBLock */
                    camera->execute_lock_property((CrInt16u)SDK::CrDevicePropertyCode::CrDeviceProperty_AWBL);
                }
                else if (action == TEXT("13")) { /* AF Area Position(x,y) */
                    camera->set_af_area_position();
                }
                else if (action == TEXT("14")) { /* Selected MediaFormat */
                    camera->get_select_media_format();
                    camera->set_select_media_format();
                }
                else if (action == TEXT("15")) { /* Movie Rec Button */
                    camera->execute_movie_rec();
                }
                else if (action == TEXT("16")) { /* White Balance */
                    camera->get_white_balance();
                    camera->set_white_balance();
                }
                else if (action == TEXT("17")) { /* Custom WB */
                    camera->get_custom_wb();
                    camera->set_custom_wb();
                }
                else if (action == TEXT("18")) { /* Zoom Operation */
                    camera->get_zoom_operation();
                    camera->set_zoom_operation();
                }
                else if (action == TEXT("19")) { /* Remocon Zoom Speed Type */
                    camera->get_remocon_zoom_speed_type();
                    camera->set_remocon_zoom_speed_type();
                }
                else if (action == TEXT("20")) { /* Preset Focus */
                    camera->execute_preset_focus();
                }
                else if (action == TEXT("21")) { /*Remote menu 2*/
                    camera->remote_menu_2();
                }
    #if defined(LIVEVIEW_ENB)
                else if (action == TEXT("lv")) { /* LiveView Enable */
                    camera->change_live_view_enable();
                }
    #endif
                cli::tout << std::endl;
            } // end of loop-C
            cli::tout << std::endl;
        }
        // ------------------------
        // Contents Transfer
        // ------------------------
        else
        {
            // loop-D
            while (true)
            {
                cli::tout << "<< MTP-MENU >>\nWhat would you like to do? Enter the corresponding number.\n";
                cli::tout
                    << "(0) Disconnect and return to the top menu\n"
                    << "(1) Get contents list \n";
                cli::tout << "input> ";
                cli::text action;
                std::getline(cli::tin, action);
                cli::tout << '\n';

                if (action == TEXT("0")) { /* Return top menu */
                    if (camera->is_connected()) {
                        camera->disconnect();
                    }
                    break; // exit loop-D
                }
                else if (action == TEXT("1")) { /* GetContentsList() */
                    if (camera->is_connected()) {
                        camera->getContentsList();
                    }
                    else
                    {
                        cli::tout << "Disconnected\n";
                        break;
                    }
                }
                if (!camera->is_connected()) {
                    break;
                }
                cli::tout << std::endl;
            } // end of loop-D
            cli::tout << std::endl;
        }

    }// end of loop-A

    cli::tout << "Release SDK resources.\n";
    // cr_lib->Release();
    SDK::Release();

    // cli::free_cr_lib(&cr_lib);

    cli::tout << "Exiting application.\n";
    std::exit(EXIT_SUCCESS);    
}

/** @brief
 *  @param[in]
	@return
*/
bool Camera_Interface::take_photo(Camera_shooting_type_t type)
{
    /// check camera connection mode
    if (SDK::CrSdkControlMode_Remote == camera->get_sdkmode())
    {
        if(type == CAMERA_SHOTTING_TYPE_SINGLE)
        {
            camera->capture_image();
        }
        else if(type == CAMERA_SHOTTING_TYPE_CONTINUOUS)
        {
            camera->continuous_shooting();
        }
        else
        {
            LOG_ERROR << "shotting type is not support !!! \n\r";

            return false;
        }
    }
    else
    {
        LOG_ERROR << "Camera not in remote control mode !!!\n\r";

        return false;
    }

    return true;
}

/** @brief
 *  @param[in]
	@return
*/
void Camera_Interface::set_record(bool state)
{
    if(state == true)
    {
        if(isRecording(true) != CAMERA_RECORD_STATE_START)
        {
            LOG_ERROR << "set camera start record FAILED !!!" << END_LINE;
        }

        usleep(500000);

        if(set_connection(true) != true)
        {
            LOG_ERROR << "set camera disconnections FAILED !!!" << END_LINE;
        }
    }
    else
    {
        if(set_connection(false) != true)
        {
            LOG_ERROR << "set camera connections FAILED !!!" << END_LINE;
        }

        usleep(500000);

        if(isRecording(false) != CAMERA_RECORD_STATE_STOP)
        {
            LOG_ERROR << "set camera stop record FAILED !!!" << END_LINE;
        }
    }

    // camera->recording(state);
}

/** @brief
 *  @param[in]
	@return
*/
bool Camera_Interface::set_connection(bool state)
{
    if(state == true)
    {
        return camera->disconnect();
    }
    else
    {
        return camera->connect(SCRSDK::CrSdkControlMode_Remote, SCRSDK::CrReconnecting_ON);
    }

    return false;
}

/** @brief
 *  @param[in]
	@return
*/
Camera_Interface::e_camera_record_state Camera_Interface::isRecording(bool state)
{
    std::int64_t device_handle = camera->get_device_handle();

    if(device_handle == 0)
    {
        LOG_ERROR << "not found camera device handle " << END_LINE;
        LOG_WARN << "Please read README.md to add user functions to CameraDeivce.cpp" << END_LINE;
        return CAMERA_RECORD_STATE_ERROR;
    }

    LOG_INFO << "Recording..." << END_LINE;

    if(state == true)
    {
        LOG_INFO << "Start " << END_LINE;

        SDK::SendCommand(device_handle, SDK::CrCommandId::CrCommandId_MovieRecord, SDK::CrCommandParam_Down);
        // Wait, then send shutter up
        usleep(35000);

        return CAMERA_RECORD_STATE_START;
    }
    else
    {
        LOG_INFO << "Stop " << END_LINE;

        SDK::SendCommand(device_handle, SDK::CrCommandId::CrCommandId_MovieRecord, SDK::CrCommandParam_Up);
       
        // Wait, then send shutter up
        usleep(35000);

        return CAMERA_RECORD_STATE_STOP;
    }

    return CAMERA_RECORD_STATE_IDLE;
}

/** @brief
 *  @param[in]
	@return
*/
uint16_t Camera_Interface::get_still_image_store_destination()
{

}

/** @brief
 *  @param[in]
	@return
*/
bool Camera_Interface::set_image_store_locations(void)
{
    SCRSDK::CrDeviceProperty prop;
    uint16_t storeTytpe = 0;//camera->get_still_image_store_destination();

    LOG_WARN << "current : " << storeTytpe << END_LINE;

    if(storeTytpe != (uint16_t)SCRSDK::CrStillImageStoreDestination::CrStillImageStoreDestination_MemoryCard)
    {
        prop.SetCode(SCRSDK::CrDevicePropertyCode::CrDeviceProperty_StillImageStoreDestination);
        prop.SetCurrentValue((CrInt16u)SCRSDK::CrStillImageStoreDestination::CrStillImageStoreDestination_MemoryCard);
        prop.SetValueType(SCRSDK::CrDataType::CrDataType_UInt16Array);

        // camera->set_property(prop);

        return true;
    }

    return false;
}

// ------------------------------------------------------------------------------
//   Read Thread
// ------------------------------------------------------------------------------
void Camera_Interface::read_thread(void)
{
    LOG_INFO << "START CAMERA INTERFACE READ THREAD !!! \n\r";

    // while (!is_read_write_threadExit) {
    while (is_read_write_threadExit == false) {

        // runSample();

        usleep(100);   // sleep 1000us
    } // end: while not received all

    LOG_ERROR << "CLOSE THREAD !!!\n\r" ;
}

// ------------------------------------------------------------------------------
//   Write Thread
// ------------------------------------------------------------------------------
void Camera_Interface::write_thread(void)
{
    LOG_INFO << "START CAMERA INTERFACE WRITE THREAD !!! \n\r";

    // Blocking wait for new data
    while (is_read_write_threadExit == false) {

        // if(get_connection())
        // liveViewBuffer();

        usleep(300000);   // sleep 1000us
    }

    LOG_ERROR << "CLOSE THREAD !!! \n\r";
}

void Camera_Interface::monitor_thread(void)
{
    static int timeCheckDeviceConnection = 0;

    LOG_INFO << "START CAMERA MONITOR THREAD !!! \n\r";

    // Blocking wait for new data
    while (is_read_write_threadExit == false) {
        

        

        usleep(1000000);
    }

    LOG_ERROR << "CLOSE THREAD !!! \n\r";
}

// ------------------------------------------------------------------------------
//   Read Thread
// ------------------------------------------------------------------------------
void Camera_Interface::start_read_thread(void)
{
  read_thread();
}

// ------------------------------------------------------------------------------
//   Write Thread
// ------------------------------------------------------------------------------
void Camera_Interface::start_write_thread(void)
{
  write_thread(); 
}

void Camera_Interface::start_monitor_thread(void)
{
  monitor_thread(); 
}

void Camera_Interface::handle_quit( int sig )
{
    // Send command disable
    // disable_offboard_control();
    try {
        stop();

    } catch (int error) {
        LOG_WARN << "could not stop camera interface\n\r";
    }
}

bool Camera_Interface::get_connection(void)
{
    return is_camera_connection;
}

void *start_camera_interface_read_thread(void *args)
{
    Camera_Interface *interface = (Camera_Interface *)args;

    interface->start_read_thread();

  return NULL;
}

void *start_camera_interface_write_thread(void *args)
{
    Camera_Interface *interface = (Camera_Interface *)args;

    interface->start_write_thread();

  return NULL;
}

void *start_camera_monitor_thread(void *args)
{
    Camera_Interface *interface = (Camera_Interface *)args;

    interface->start_monitor_thread();

  return NULL;
}
/************************ (C) COPYRIGHT GREMSY *****END OF FILE****************/