/** 
  ******************************************************************************
  * @file    myMath.h
  * @author  Gremsy Team
  * @version V2.0.0
  * @date    ${date}
  * @brief   This file contains all the functions prototypes for the myMath.c
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

#ifndef __MY_MATH_H_
#define __MY_MATH_H_

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported class ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
int runExternalCommand(char *cmd, char lines[][255]);
int num_digits(int n);
void reverse(char s[]);
void itoa(int n, char s[]);
void float2string(char str[], float n);
int random(int minN, int maxN);
#endif /* __MY_MATH_H_ */

/************************ (C) COPYRIGHT GREMSY *****END OF FILE****************/