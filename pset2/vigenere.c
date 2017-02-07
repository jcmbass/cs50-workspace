#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*Vigenere Cypher, a safest choice than Caesar Cypher.
The program will always need an argument compose of a string of characters and only one, otherwise it will Yell at you.
These argument is going to be save as integers and used as Keys for the Cyphered text*/

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("YEll\n");
        return 1;
    }
    else
    {
        //Acepting a keyword and assining a shift value to each character. 
        //if the keyword is not a single alphabetic world you recive a YELL!

        string s = argv[1];
        int n = strlen(s), k[n];
        for (int i = 0; i < n; i++)
        {
            if (isalpha(s[i]))
            {    if (isupper(s[i]))
                {
                    int a = abs('A' - s[i]);
                    k[i] = a;
                }
                else
                {
                    int a = abs('a' - s[i]);
                    k[i] = a;
                }
            }
            else
            {
                printf("YELL\n");
                return 1;
            }
        }
        
        //Getting a plaintex and shifting each character acordin to the keyword
        
        string p = GetString();
        int m = strlen(p), count = 0;
        for (int j = 0; j < m; j++)
        {
            if (isalpha(p[j]))
                {
                    int key = ((count) % n);
                    if (isupper(p[j]))
                    {
                        int a = abs('A' - p[j]);
                        int c = ((a + k[key]) % 26);
                        printf("%c", c + 'A');
                    }
                    else
                    {
                        int a = abs('a' - p[j]);
                        int c = ((a + k[key]) % 26);
                        printf("%c", c + 'a');
                    }
                    count++;
                }
            else if (isblank(p[j]) || isgraph(p[j]))
                printf("%c", p[j]);
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