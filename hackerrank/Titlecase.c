#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int main(void)
{
    char* string = GetString();      //Function implemented in cs50.h
    char* needle = &string[0];
    const char* annd = " and";
    const char* but = " but";
    const char* of = " of";
    const char* the = " the";
    
    string[0] = toupper(string[0]);         //capitalize first word
    
    while((needle = strchr(needle + 1, ' ')) != NULL)
    {
        if((strncmp(needle, annd, 4) != 0) && (strncmp(needle, but, 4) != 0) && (strncmp(needle, of, 3) != 0) && (strncmp(needle, the, 4) != 0))
            needle[1] = toupper(needle[1]);
    }
    
    char* last = strrchr(string, ' ');
    if(last != NULL)
        last[1] = toupper(last[1]);     //Capitalize the last word
    
    printf("%s\n", string);
}