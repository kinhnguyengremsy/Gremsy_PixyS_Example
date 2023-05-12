/*******************************************************************************
 * @file    gsdk_serial_manager.cpp
 * @author  The GremsyCo
 * @version V1.0.0
 * @date    May-25-2022
 * @brief   This file contains API for gimbal interface.
 *
 *  @Copyright (c) 2018 Gremsy
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include "gsdk_serial_manager.h"

using namespace GSDK::HAL;

gSDK_Serial_Manager::gSDK_Serial_Manager()
{

}

gSDK_Serial_Manager::~gSDK_Serial_Manager()
{

}

bool gSDK_Serial_Manager::write_message(const mavlink_message_t &message)
{
    if (!get_device_status()) {
        fprintf(stderr, "Serial device has not been initialized\n");
        return false;
    }

    uint8_t buff[MAVLINK_MAX_PACKET_LEN] = { 0 };
    uint16_t len = mavlink_msg_to_send_buffer(buff, &message);
    return serial_write(buff, len) == len;
}
