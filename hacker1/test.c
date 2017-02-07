#include <cs50.h>
#include <stdio.h>

int main (void)
    {
    
    int count = 2, sumpar = 0;
    int cardnumber[count], digit[count];
    cardnumber[count] = 5;
    for(int i = 0; i < count; i += 2)
        {
            digit[i] = cardnumber[i] * 2;
            printf("%d %d\n",cardnumber[i], digit[i]);
            if (digit[i] > 9)
            {
                int ddigit[count];
                ddigit[count] = digit[i];
                for(int j = 0; j < 2; j++)
                {
                    sumpar = sumpar + ddigit[j];
                    printf("%d\n", ddigit[j]);
                }
            }
        }
    }