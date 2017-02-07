#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void)
{
  int total = 0;
  int digit = 0;
  int place = 1;
  int sign = 1;

  char *line = GetString(); //a function implemented in cs50.h 

  for (int i = strlen(line); i >= 0; i--) {
    if (isdigit(line[i])) {
      digit += (line[i] - '0') * place;
      place *= 10;
    }
    else if (line[i] != ' ') {
      if (line[i] == '+')
        sign = 1;
      else if (line[i] == '-')
        sign = -1;

      total += sign * digit;
      digit = 0;
      place = 1;
    }
  }
  
  total += digit; // add the last digit to the total
  printf("%d", total);
  free(line);
}