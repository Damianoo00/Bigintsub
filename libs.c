#include "libs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *bignumsub(char *ch_num1, char *ch_num2) {
  LongNumber num1 = char2longnumber(ch_num1);
  LongNumber num2 = char2longnumber(ch_num2);
  LongNumber result = subtract(&num1, &num2);
  return longnumber2char(&result);
}

void minus_zero_exception(LongNumber *num) {
  if (!strcmp(num->number, "0")) {
    num->mathsign = plus;
  }
}

void remove_first_nulls(LongNumber *num) {
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
  int n_size = strlen(num1->number);

  char *wynik = malloc(sizeof(char) * 32);

  for (int i = n_size - 1; i >= 0; i--) {
    wynik[i] = num1->number[i] - num2->number[i] + '0';

    if (wynik[i] < '0') {
      num1->number[i - 1] = num1->number[i - 1] - 1;
      num1->number[i] = num1->number[i] + 10;
    }

    wynik[i] = num1->number[i] - num2->number[i] + '0';
  }
  return wynik;
}

char *sum_column_method(LongNumber *num1, LongNumber *num2) {
  int n_size = strlen(num1->number);
  char *wynik = malloc(sizeof(char) * 32);

  for (int i = n_size - 1; i >= 0; i--) {
    wynik[i] = num1->number[i] + num2->number[i] - '0';

    if (wynik[i] > '9') {
      num1->number[i] = num1->number[i] - 10;
      num1->number[i - 1] = num1->number[i - 1] + 1;
    }
    wynik[i] = num1->number[i] + num2->number[i] - '0';
  }
  return wynik;
}

LongNumber subtract(LongNumber *num1, LongNumber *num2) {
  LongNumber wynik;

  add_nulls(num1, num2);
  if (num1->mathsign == plus && num2->mathsign == plus) {
    if (if_swap(num1, num2)) {

      wynik.mathsign = minus;
      strcpy(wynik.number, subtraction_column_method(num2, num1));
    } else {

      wynik.mathsign = plus;
      strcpy(wynik.number, subtraction_column_method(num1, num2));
    }
  }

  if (num1->mathsign == plus && num2->mathsign == minus) {
    wynik.mathsign = minus;
    strcpy(wynik.number, sum_column_method(num1, num2));
  }

  if (num1->mathsign == minus && num2->mathsign == plus) {
    wynik.mathsign = minus;
    strcpy(wynik.number, sum_column_method(num1, num2));
  }

  if (num1->mathsign == minus && num2->mathsign == minus) {
    wynik.mathsign = plus;
    strcpy(wynik.number, subtraction_column_method(num2, num1));
  }

  minus_zero_exception(&wynik);
  return wynik;
}

void add_nulls(LongNumber *num1, LongNumber *num2) {

  char temp[32];
  int j = 0;
  if (strlen(num1->number) > strlen(num2->number)) {
    for (int i = 0; i < strlen(num1->number); i++) {
      if (i < (strlen(num1->number) - strlen(num2->number))) {
        temp[i] = '0';
      } else {
        temp[i] = num2->number[j++];
      }
    }

    strcpy(num2->number, temp);
  }
  if (strlen(num1->number) < strlen(num2->number)) {
    for (int i = 0; i < strlen(num2->number); i++) {
      if (i < (strlen(num2->number) - strlen(num1->number))) {
        temp[i] = '0';
      } else {
        temp[i] = num1->number[j++];
      }
    }
    strcpy(num1->number, temp);
  }
}

LongNumber char2longnumber(char txt[]) {

  LongNumber num;
  num.mathsign = plus;
  if (txt[0] == '-') {
    num.mathsign = minus;
    // shift minus sign
    txt = txt + 1;
  }
  strcpy(num.number, txt);
  return num;
}

char *longnumber2char(LongNumber *num) {
  remove_first_nulls(num);
  char *str = malloc(sizeof(char) * 32);
  int i = 0;
  if (num->mathsign == minus)
    str[i++] = '-';
  strcpy(&(str[i]), num->number);
  return str;
}

int if_swap(LongNumber *num1, LongNumber *num2) {

  for (int i = 0; i < strlen(num1->number); i++) {
    if (num1->number[i] > num2->number[i]) {
      return 0;
    }
    if (num1->number[i] < num2->number[i]) {
      return 1;
    }
  }
}