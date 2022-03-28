#ifndef Libs
#define Libs

enum sign { minus = 0, plus = 1 };

struct LongNumber {
  char number[33];
  enum sign mathsign;
};

typedef struct LongNumber LongNumber;

char *bignumsub(char *, char *);
int if_swap(LongNumber *, LongNumber *);
LongNumber char2longnumber(char[]);
void add_nulls(LongNumber *, LongNumber *);
LongNumber subtract(LongNumber *, LongNumber *);
char *subtraction_column_method(LongNumber *, LongNumber *);
char *longnumber2char(LongNumber *);
void remove_first_nulls(LongNumber *);
void minus_zero_exception(LongNumber *);

#endif