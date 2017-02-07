#include <cs50.h>
#include <string.h>
#include <stdio.h>

bool connections(int persons, int first, int second, int array[persons][persons], int* conn); //recursive function prototype

int main(void)
{
  int persons = GetInt();
  int array[persons][persons];
  char delim[2] = " ";

  for(int i = 0; i < persons; i++)
  {
    char* line = GetString();
    char* tok = strtok(line, delim);
    for(int j = 0; j < persons; j++)
    {
      array[i][j] = atoi(tok);
      tok = strtok(NULL, delim);
    }
  }

  int first = GetInt();
  int second = GetInt();

  int conn = 0;

  connections(persons, first, second, array, &conn);
  printf("%d", conn);
}

bool connections(int persons, int first, int second, int array[persons][persons], int* conn)
{
  if(array[first][second] != 1)
  {
      if(*conn > 100){
        *conn = -1;
        return false; }
        
    for(int i = 0; i < persons; i++)
    {
      if((array[first][i] == 1) && (array[i][second] == 1))
      {
        *conn += 2;
        return true;
      }
      
      else if(array[first][i] == 1)
      {
        *conn += 1;
        return connections(persons, i, second, array, conn);
      }
    }

    *conn = -1;
    return false;
  }

  *conn += 1;
  return true;
}