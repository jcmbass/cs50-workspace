#include <cs50.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
    char* hotel = GetString();
    int floors = hotel[0] - '0'; //number of floor in the hotel
    int rooms = hotel[2] - '0'; //number of rooms per floor
    
    char* map = malloc(floors * rooms);
    char* occupied = malloc(rooms);
    
    for(int i = 0; i < floors; i++)
    {
        occupied = GetString();
        strcat(map, occupied);
        free(occupied);
    }
    
    int check = GetInt(); //how many guest wants to check-in
    
    char* guest = malloc(check);
    for(int j = 0; j < check; j++)
    {
        guest[j] = '0';
    }
    
    char* found = strstr(map, guest);
    
    free(map);
    
    if(found != NULL)
        {    
            printf("1\n");
            return 0;
        }
        
    printf("0\n");
}