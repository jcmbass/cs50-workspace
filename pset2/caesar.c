#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//Caesar cypher, not a safe choice but it will do.
//The program will always need an argument and only one, otherwise it will Yell at you.
//Thes argument is going to be save as an integer and used as a Key for the Cypheredtext

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("YEll");
        return 1;
    }
    else
    {
        int k = atoi(argv[1]);
        string s = GetString();
        for (int i = 0, n = strlen(s); i < n; i++)
            {
                if (isalpha(s[i]) || isblank(s[i]) || isgraph(s[i]))
                {
                    if (isupper(s[i]))
                    {
                        int p = abs('A' - s[i]);
                        int c = ((p + k) % 26);
                        printf("%c", c + 'A');
                    }
                    else if (islower(s[i]))
                    {
                        int p = abs('a' - s[i]);
                        int c = ((p + k) % 26);
                        printf("%c", c + 'a');
                    }
                    else
                        printf("%c", s[i]);
                }
                else
                {
                    printf("\n");
                    return 1;
                }
            }
        printf("\n");
        return 0;
    }
}