#include <stdio.h>
#include <cs50.h>

int main (void)
{
    long long credit;
    
    //asking the user for a valid credit card number
    do
    {
        printf("number: ");                                 
        credit = GetLongLong();                              
    }
    while (credit < 0);
    
    //count lenght of the credit card
    int count = 0;                                              
    long long lenght = credit;
    while(lenght != 0)                          
    {
        lenght /= 10;
        ++count;
    }
    
    //isolating first digits of credit card and asigning it value "number"
    int cardnumber[count];
    for (int i = 0; i < count; i++)
    {
        cardnumber[i] = credit % 10;
        credit = credit / 10;
    }
    if ((count == 13 || count == 15) || count == 16)
    {
        int digit[count], sumnon = 0, sumpar = 0, total = 0;
        if (count == 13)
        {
            if (cardnumber[12] == 4)
            {
                for(int i = 0; i < count; i += 2)
                {
                    digit[i] = cardnumber[i];
                    sumnon = sumnon + digit[i];
                }
                for(int i = 1; i < count; i += 2)
                {
                    digit[i] = cardnumber[i] * 2;
                    if (digit[i] > 9)
                    {
                        for(int j = 0; j < 2; j++)
                        {
                            int ddigit[j];
                            ddigit[j] = digit[i] % 10;
                            sumpar = sumpar + ddigit[j];
                            digit[i] /= 10;
                        }
                    }
                    else
                    {
                        sumpar = sumpar + digit[i];
                    }
                }
                total = sumpar + sumnon;
                if (total % 10 == 0)
                {
                    printf("VISA\n");
                    return(0);
                }
                else
                {
                    printf("INVALID\n");
                    return(0);
                }
            }
            else
            {
                printf("INVALID\n");
                return(0);
            }
        }
       else if (count == 15)
        {
            if ((cardnumber[14] == 3 && cardnumber[13] == 4) || (cardnumber[14] == 3 && cardnumber[13] == 7))
            {
                for(int i = 0; i < count; i += 2)
                {
                    digit[i] = cardnumber[i];
                    sumnon = sumnon + digit[i];
                }
                for(int i = 1; i < count; i += 2)
                {
                    digit[i] = cardnumber[i] * 2;
                    if (digit[i] > 9)
                    {
                        for(int j = 0; j < 2; j++)
                        {
                            int ddigit[j];
                            ddigit[j] = digit[i] % 10;
                            sumpar = sumpar + ddigit[j];
                            digit[i] /= 10;
                        }
                    }
                    else
                    {
                        sumpar = sumpar + digit[i];
                    }
                }
                total = sumpar + sumnon;
                if (total % 10 == 0)
                {
                    printf("AMEX\n");
                    return(0);
                }
                else
                {
                    printf("INVALID\n");
                    return(0);
                }
            }
            else
            {
                printf("INVALID\n");
                return(0);
            }
        }
        else
        {
            if (cardnumber[15] == 4 || (cardnumber[15] == 5 && (cardnumber[14] > 0 && cardnumber[14] < 6)))
            {
                for(int i = 1; i < count; i += 2)
                {
                    digit[i] = cardnumber[i];
                    sumnon = sumnon + digit[i];
                }
                for(int i = 0; i < count; i += 2)
                {
                    digit[i] = cardnumber[i] * 2;
                    if (digit[i] > 9)
                    {
                        for(int j = 0; j < 2; j++)
                        {
                            int ddigit[j];
                            ddigit[j] = digit[i] % 10;
                            sumpar = sumpar + ddigit[j];
                            digit[i] /= 10;
                        }
                    }
                    else
                    {
                        sumpar = sumpar + digit[i];
                    }
                }
                total = sumpar + sumnon;
                if (total % 10 == 0)
                {
                    printf("MASTER CARD\n");
                    return(0);
                }
                else
                {
                    printf("INVALID\n");
                    return(0);
                }
            }
            else
            {
                printf("INVALID\n");
                return(0);
            }
        }
    }
}