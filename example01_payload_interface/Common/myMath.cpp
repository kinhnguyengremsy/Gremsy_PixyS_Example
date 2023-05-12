/** 
  ******************************************************************************
  * @file    myMath.cpp
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
#include "myMath.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/** @brief
 *  @param[in]
	@return
*/
int runExternalCommand(char *cmd, char lines[][255]) {
  FILE *fp;
  char path[255];
 
  /* Open the command for reading. */
  fp = popen(cmd, "r");
  if (fp == NULL) {
    return -1;
  }
 
  int cnt = 0;
  while (fgets(path, sizeof(path), fp) != NULL) {
    strcpy(lines[cnt++], path);
  }
  pclose(fp);
  return cnt;  
}

int num_digits(int n) {
    if (n == 0) return 1;
    if (n < 0) n = -n;
    int count = 0;
    while (n > 0) {
        count++;
        n /= 10;
    }
    return count;
}

void reverse(char s[])
{
    int i, j;
    char c;
    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[])
{
    int i, sign;
    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void float2string(char str[], float n)
{
  sprintf(str, "%.7f", n);
}

int random(int minN, int maxN)
{
 return minN + rand() % (maxN + 1 - minN);
}
/************************ (C) COPYRIGHT GREMSY *****END OF FILE****************/