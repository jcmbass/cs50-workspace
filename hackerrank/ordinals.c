#include <cs50.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
    char *line = GetString();
    
    if(char* needle = strstr(line, "cat") == NULL)
    {
        printf("No cat yet\n");
    }
    
    for(int i = 0, n = strlen(line); i < n; i++)
}
