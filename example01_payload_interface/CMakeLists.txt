
cmake_minimum_required(VERSION 2.8.12)
# if(APPLE)
# set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum OS X deployment version")
# endif(APPLE)
project (example01_payload_interface LANGUAGES CXX)
# cmake -DCMAKE_BUILD_TYPE=Release ..
### Append project cmake script dir ###
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/Camera/Sony_Remote_SDK_Linux32ARMv7/cmake)

### Enumerate project files ###
include(enum_cli_hdr)
include(enum_cli_src)
include(enum_crsdk_hdr)

set(MAVLINK_PROTOCOL
    "${CMAKE_CURRENT_SOURCE_DIR}/Mavlink/src/src/v2.0"
)

# Find anothers libraries
find_package(PkgConfig REQUIRED)
find_package( Threads )
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

#Include header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR}/Common
                    ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy
                    ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/Camera
                    ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/Gimbal/gimbal_interface
                    ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/Gimbal/hal
                    ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/GUI
                    ${CMAKE_CURRENT_SOURCE_DIR}/Mavlink/platform/linux
                    ${MAVLINK_PROTOCOL}
                    ${CMAKE_CURRENT_SOURCE_DIR}/User
                    ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/Camera/Sony_Remote_SDK_Linux32ARMv7/app
                    ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/Camera/Sony_Remote_SDK_Linux32ARMv7/app/CRSDK
                    ${GST_INCLUDE_DIRS}
)

set(COMMON_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/Common/myMath.cpp
)

set(GREMSY_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/Camera/camera_interface.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/Gimbal/gimbal_interface/gimbal_control.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/Gimbal/gimbal_interface/gimbal_interface.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/Gimbal/gimbal_interface/gimbal_protocol.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/Gimbal/gimbal_interface/gimbal_protocol_v1.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/Gimbal/gimbal_interface/gimbal_protocol_v2.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/Gimbal/hal/gsdk_platform_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/Gimbal/hal/gsdk_serial_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/Gimbal/hal/gsdk_thread_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/GUI/gui_interface.cpp
)

set(MAVLINK_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/Mavlink/platform/linux/linux_serial_port.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Mavlink/platform/linux/posix_thread_manager.cpp
)

set(USER_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/User/main.cpp
)

set(SONY_APP_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/Camera/Sony_Remote_SDK_Linux32ARMv7/app/CameraDevice.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/Camera/Sony_Remote_SDK_Linux32ARMv7/app/ConnectionInfo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/Camera/Sony_Remote_SDK_Linux32ARMv7/app/LibManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/Camera/Sony_Remote_SDK_Linux32ARMv7/app/MessageDefine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/Camera/Sony_Remote_SDK_Linux32ARMv7/app/PropertyValueTable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/Camera/Sony_Remote_SDK_Linux32ARMv7/app/Text.cpp
)

set(cli_hdrs
    ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/Camera/Sony_Remote_SDK_Linux32ARMv7/app
)

set(cli_srcs
    ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/Camera/Sony_Remote_SDK_Linux32ARMv7/app
)

set(crsdk_hdrs
    ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/Camera/Sony_Remote_SDK_Linux32ARMv7/app/CRSDK
)

add_executable( ${PROJECT_NAME} 
                ${COMMON_SOURCE}
                ${GREMSY_SOURCE}
                ${MAVLINK_SOURCE}
                ${USER_SOURCE}
                ${SONY_APP_SOURCE}
                ${cli_hdrs}
                ${cli_srcs}
                ${crsdk_hdrs}
)

if(NOT APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        BUILD_RPATH "$ORIGIN"
        INSTALL_RPATH "$ORIGIN"
    )
endif(NOT APPLE)

## Specify char is signed-char to fix mismatch with Raspbian
target_compile_options(${PROJECT_NAME}
    PRIVATE
        -fsigned-char
    PUBLIC 
        ${GTK3_CFLAGS_OTHER}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${crsdk_hdr_dir} # defined in enum script
    PUBLIC 
        ${GTK3_INCLUDE_DIRS}
)

### Configure external library directories ###
set(ldir ${CMAKE_CURRENT_SOURCE_DIR}/Gremsy/Camera/Sony_Remote_SDK_Linux32ARMv7/external)
set(cr_ldir ${ldir}/crsdk)

### Link CRSDK library
find_library(camera_remote Cr_Core HINTS ${cr_ldir})
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_THREAD_LIBS_INIT}
    ${camera_remote}
    ${GTK3_LIBRARIES}
)

### Linux specific configuration ###
if(UNIX AND NOT APPLE)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8)
            # Must use std::experimental namespace if older than GCC8
            message("[${PROJECT_NAME}] GCC version less than 8. Using std::experimental namespace.")
            target_compile_definitions(${PROJECT_NAME} PRIVATE USE_EXPERIMENTAL_FS)
        endif()

        if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9)
            # Must explicitly link separate std::filesystem if older than GCC9
            message("[${PROJECT_NAME}] GCC version less than 9. Explicitly linking separate std::filesystem library.")
            target_link_libraries(${PROJECT_NAME} PRIVATE stdc++fs)
        endif()
    endif()
endif(UNIX AND NOT APPLE)

if(UNIX AND NOT APPLE)
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${cr_ldir} $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif(UNIX AND NOT APPLE)

## Install application
## '.' means, install to the root directory of CMAKE_INSTALL_PREFIX
install(TARGETS ${PROJECT_NAME} DESTINATION .)
install(DIRECTORY ${cr_ldir}/ DESTINATION .)