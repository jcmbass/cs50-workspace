 #include <stdio.h>
 #include <cs50.h>
 
 int main (void)
 {
  printf("minutes: ");
  int min = GetInt();
  int bottles = (min*12);
  printf("bottles: %d\n", bottles);
 }