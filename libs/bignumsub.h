#ifndef Bignumsub
#define Bignumsub

enum sign { minus = 0, plus = 1 };

struct LongNumber {
  char *number;
  enum sign mathsign;
};

typedef struct LongNumber LongNumber;

char *bignumsub(char *, char *);
char is_bigger(LongNumber *, LongNumber *);
LongNumber char2longnumber(char[]);
void add_nulls(LongNumber *, LongNumber *);
LongNumber subtract(LongNumber *, LongNumber *);
char *subtraction_column_method(LongNumber *, LongNumber *);
char *longnumber2char(LongNumber *);
void remove_first_nulls(LongNumber *);
void minus_zero_exception(LongNumber *);
void CheckExceededException(char *, char *);
void CheckNoValueException(char *, char *);

#endif