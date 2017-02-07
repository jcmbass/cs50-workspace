#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main (void)
{
    //asking how much change is owed
    float owed;
    do
    {
        printf("O hai! How much change is owed?");
        owed = GetFloat();
    }
    while (owed < 0.0);
    
    int quarter = 25;
    int dime = 10;
    int nickles = 5;
    int pennies = 1;
    int counter = 0;
    
    //rounding change to get a int
    owed = owed * 100.0;
    int change = round(owed);
    
    //counting the minimun amount of coins
    while (change >= 25)
    {
        change = change - quarter;
        counter++;
    }
    while (change >= 10)
    {
        change = change - dime;
        counter++;
    }
    while (change >= 5)
    {
        change = change - nickles;
        counter++;
    }
    while (change >= 1)
    {
        change = change - pennies;
        counter++;
    }
    
    //spit out the minimun number of coins
    printf("%d\n", counter);
}
