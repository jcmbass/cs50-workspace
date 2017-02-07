#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main(void)
{
    string s = GetString();
    if (isalpha(s[0]))
        printf("%c", toupper(s[0]));
    for (int i = 1, n = strlen(s); i < n; i++)
        {
        if (isalpha(s[i]) && isblank(s[i-1]))
            printf("%c", toupper(s[i]));
        }
    printf("\n");
}