#include "../libs/bignumsub.h"
#include "../libs/exceptions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *bignumsub(char *ch_num1, char *ch_num2) {
  /*  substract 2 chars  */
  CheckExceededException(ch_num1, ch_num2);
  CheckNoValueException(ch_num1, ch_num2);

  LongNumber num1 = char2longnumber(ch_num1);
  LongNumber num2 = char2longnumber(ch_num2);
  LongNumber result = subtract(&num1, &num2);

  return longnumber2char(&result);
}

void minus_zero_exception(LongNumber *num) {
  /* replace -0 to 0 if occurred*/
  if (!strcmp(num->number, "0")) {
    num->mathsign = plus;
  }
}

void remove_first_nulls(LongNumber *num) {
  /*  remove left nulls in number (001 -> 1)  */
  char *temp;
  if (strlen(num->number) > 1) {

    while (num->number[0] == '0') {
      temp = num->number;
      temp = temp + 1;
      strcpy(num->number, temp);
    }
  }
}

char *subtraction_column_method(LongNumber *num1, LongNumber *num2) {
  /*  substract 2 numbers with column method (only positive numbers and
   * result)
   */
  int n_size = strlen(num1->number);
  char *result = malloc(sizeof(char) * n_size);

  for (int i = n_size - 1; i >= 0; i--) {
    result[i] = num1->number[i] - num2->number[i] + '0';

    if (result[i] < '0') {
      num1->number[i - 1] = num1->number[i - 1] - 1;
      num1->number[i] = num1->number[i] + 10;
    }

    result[i] = num1->number[i] - num2->number[i] + '0';
  }
  return result;
}

char *sum_column_method(LongNumber *num1, LongNumber *num2) {
  /*  sum 2 numbers with column method (only positive numbers and result)  */
  int n_size = strlen(num1->number);
  char *result = malloc(sizeof(char) * n_size);

  for (int i = n_size - 1; i >= 0; i--) {
    result[i] = num1->number[i] + num2->number[i] - '0';

    if (result[i] > '9') {
      num1->number[i] = num1->number[i] - 10;
      num1->number[i - 1] = num1->number[i - 1] + 1;
    }
    result[i] = num1->number[i] + num2->number[i] - '0';
  }
  return result;
}

LongNumber subtract(LongNumber *num1, LongNumber *num2) {
  /*  prepare numbers to "column method" notes sign of number and greater of
   * number */
  LongNumber result;

  add_nulls(num1, num2);
  if (num1->mathsign == plus && num2->mathsign == plus) {
    if (is_bigger(num1, num2)) {

      result.mathsign = minus;
      result.number = subtraction_column_method(num2, num1);
    } else {

      result.mathsign = plus;
      result.number = subtraction_column_method(num1, num2);
    }
  }

  if (num1->mathsign == plus && num2->mathsign == minus) {
    result.mathsign = plus;
    result.number = sum_column_method(num1, num2);
  }

  if (num1->mathsign == minus && num2->mathsign == plus) {
    result.mathsign = minus;
    result.number = sum_column_method(num1, num2);
  }

  if (num1->mathsign == minus && num2->mathsign == minus) {
    if (is_bigger(num1, num2)) {
      result.mathsign = plus;
      result.number = subtraction_column_method(num2, num1);
    } else {
      result.mathsign = minus;
      result.number = subtraction_column_method(num1, num2);
    }
  }

  minus_zero_exception(&result);
  return result;
}

void add_nulls(LongNumber *num1, LongNumber *num2) {
  /*  add nulls at begining of shorter number to equal its length  */
  char *temp;
  int num1_size = strlen(num1->number);
  int num2_size = strlen(num2->number);
  int j = 0;
  if (num1_size > num2_size) {

    temp = malloc(sizeof(char) * num1_size);

    for (int i = 0; i < num1_size; i++) {
      if (i < (num1_size - num2_size)) {
        temp[i] = '0';
      } else {
        temp[i] = num2->number[j++];
      }
    }

    num2->number = temp;
  }
  if (num1_size < num2_size) {
    add_nulls(num2, num1);
  }
}

LongNumber char2longnumber(char txt[]) {
  /* recalculate char value to struct LongNumber */
  LongNumber num;
  num.mathsign = plus;
  if (txt[0] == '-') {
    num.mathsign = minus;
    // shift minus sign
    txt = txt + 1;
  }
  num.number = txt;
  return num;
}

char *longnumber2char(LongNumber *num) {
  /* recalculate struct LongNumber to char   */
  remove_first_nulls(num);
  char *str;
  int i = 0;
  str = malloc(sizeof(char) * strlen(num->number));
  if (num->mathsign == minus) {
    str[i++] = '-';
  }
  strcpy(&(str[i]), num->number);
  return str;
}

char is_bigger(LongNumber *num1, LongNumber *num2) {
  /*  check if second arg (num2) is bigger than first arg (num1)  */

  for (int i = 0; i < strlen(num1->number); i++) {
    if (num1->number[i] > num2->number[i]) {
      return 0;
    }
    if (num1->number[i] < num2->number[i]) {
      return 1;
    }
  }
}