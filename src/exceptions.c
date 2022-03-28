#include "../libs/flags.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBER_SIZE 32

void CheckExceededException(char *str1, char *str2) {
  if (strlen(str1) > MAX_NUMBER_SIZE || strlen(str2) > MAX_NUMBER_SIZE) {
    printf("[Error: %d] The allowed length of the number has been exceeded\n",
           ERANGE);
    exit(ERANGE);
  }
}

void CheckNoValueException(char *str1, char *str2) {
  if (strlen(str1) == 0 || strlen(str2) == 0) {
    printf("[Error: %d] One of argument is empty \n", VEMPTY);
    exit(VEMPTY);
  }
}