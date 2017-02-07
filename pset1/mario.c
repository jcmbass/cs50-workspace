#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //ask for the Height of the piramid in the interval
    int Height;
    do
    {
        printf("Height: ");
        Height = GetInt();
    }
    while(Height < 0 || Height > 23);
    
    //Generate the piramid
    int n = Height;
    for(int i = 0; i < n; i++)
    {
        for(int spaces = (Height - 1); spaces > 0; spaces--)
        {
            printf(" ");
        }
        for(int hashes = (n + 2); hashes > Height; hashes--)
        {
            printf("#");
        }
        printf("\n");
        Height--;
    }
}