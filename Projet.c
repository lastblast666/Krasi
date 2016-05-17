//#include <utility.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct T_domino T_domino;
struct T_domino
{
  int val1, val2;
  int dispo;
};

//May be useful
typedef int bool;
#define true 1
#define false 0

/* Defining type for game board/player */
typedef struct T_jeu T_jeu;
struct T_jeu
{
  int nbTilesLeft;
  T_domino *allTiles;
};

/*Type for tiles */
T_domino newT_domino(int _val1, int _val2)
{
  T_domino tile;
  tile.val1 = _val1;
  tile.val2 = _val2;
  tile.dispo = 1;

  return tile;
}

/* Siple function generating tiles */
T_domino* generateDominos(const int nbTiles)
{
  T_domino *tiles = malloc(nbTiles * sizeof(T_domino));
  int cpt = 0;

  for (int i = 0; i <= 6; i++)
  {
    for (int j = i; j <= 6; j++)
    {
      tiles[cpt++] = newT_domino(i, j);
    }
  }

  return tiles;
}

/* Printing function */
void printDomino(T_domino tile)
{
  printf(" _\n|\033[4m%d\033[24m|\n|\033[4m%d\033[24m|\n", tile.val1, tile.val2);
}

/* Simple function to copy a tiles array */
T_domino* arrayCopy(T_domino* baseArray, int len, int newDispo)
{
  T_domino *copy = malloc(len * sizeof(T_domino));
  for (int i = 0; i < len; i++)
  {
    copy[i] = baseArray[i];
    copy[i].dispo = newDispo;
  }

  return copy;
}

/* Function that print available tiles for player or board */
void printAvailableTiles(T_domino* tiles, int len)
{
  for (int i = 0; i < len; i++)
  {
    if(tiles[i].dispo == 1)
    printDomino(tiles[i]);
  }
}

/* Function to check if the tile is available */
bool arrayContains(int* array, int value, int len)
{
  int i = 0;
  bool contains = false;

  while(i < len && contains == false)
  {
    if(array[i] == value)
    contains = true;

    i++;
  }

  return contains;
}

/* Creating a random array of size arg(size) and within range arg(range) */
int* randomNbArray(int size, int maxRange)
{
  int *elements = malloc(sizeof(int)*size);

  for(int i = 0; i < size; i++)
  {
    elements[i] = -1;
  }

  int i = 0;
  while(i < size)
  {
    int newNb = rand() % maxRange;
    if(arrayContains(elements, newNb, size) == 0)
    {
      elements[i] = newNb;
      i++;
    }
    else
    {
      elements[i] = -1;
    }
  }
  return elements;
}

/* Main menu for player p */
void PrintMenu() //TODO : add args for current player
{
  printf("Hello player !\n"
          "What do you want to do?\n\n"
          "\t1.Place tile"
          "\t2.Exit\n\n > ");

  getchar();
}

int main(int argc , char * argv[])
{
  /* Game variables */
  const int NB_DOM = 28;
  const int NB_INITIAL_DOM = 6;
  const int NB_JOUEURS = 1;
  T_domino *tilesList = generateDominos(NB_DOM);
  /* Creating game board */
  T_jeu board;
  board.nbTilesLeft = NB_DOM;
  board.allTiles = tilesList;

  T_jeu* players = malloc((NB_JOUEURS + 1) * sizeof(T_jeu));

  /* Initializing rand function */
  srand((int)time(NULL));

  for (int i = 0; i <= NB_JOUEURS; i++)
  {
    players[i].nbTilesLeft = NB_INITIAL_DOM;
    players[i].allTiles = arrayCopy(tilesList, NB_DOM, 0);
    int *randomNumbers = randomNbArray(NB_INITIAL_DOM, NB_DOM);

    for (int j = 0; j < NB_INITIAL_DOM; j++)
    {
      players[i].allTiles[randomNumbers[j]].dispo = 1;
    }
  }

  /* Printing player available tiles */
  for (int i = 0; i <= NB_JOUEURS; i++)
  {
    printf("Player %d :\n", i+1);
    printAvailableTiles(players[i].allTiles, NB_DOM);
  }

  /* Printing menu */
  PrintMenu();

  /* REGION : Freeing memory */
  free(players[0].allTiles); //TODO : Un-hardcode this shit
  free(players[1].allTiles); //TODO : Un-hardcode this shit
  free(tilesList);
  free(players);
  /* ENDREGION */

  return 0;
}
