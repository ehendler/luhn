#include<string.h>
#include<stdio.h>
#include<stdlib.h>
/* Store credit card information */
typedef struct {
  int cclen;
  const char * ccnum;
  int * wildcards;
  int * ccint;
  int * last_six;
  int wildcard_count;
} environment;
/* Perform luhn checksum on c string*/
int luhn_char_pointer(const char *);
/* Perform luhn checksum on array of ints*/
int luhn_int_pointer(environment *);
/* Format Luhn checksum to return all valid card numbers 5th and 6th digits*/
void last_six(environment *);
/* Format Luhn checksum to return all valid card numbers full number*/
void full(environment *);
/* Format Luhn checksum to return all valid card numbers
 * Arg1: Any digit card number, using '*' as wildcard (eg. 444444**44444*444
 * Arg2: Format function pointer
 * */
int print_all_valid_numbers(const char *,void(*)());
