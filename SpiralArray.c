#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int UINT4;

typedef struct {
  UINT4 x;
  UINT4 y;
} CELL; 

typedef struct {
  UINT4 width;
  UINT4 height;
  UINT4 cellCount;
  UINT4 leftFilled;
  UINT4 rightFilled;
  UINT4 topFilled;
  UINT4 bottomFilled;
} BOARD;

void moveRight(UINT4***, BOARD*, CELL, CELL, UINT4);

void printSpiral(UINT4 **spiral, const UINT4 width, const UINT4 height)
{
  UINT4 row;
  UINT4 column;
  for (row = 0; row < height; row++) {
    for (column = 0; column < width; column++) {
      printf("%3u ", spiral[row][column]);  
    }
    printf("\n");
  }
}

void moveUp(UINT4 ***spiral, BOARD *board, CELL start, CELL end, UINT4 value) {
  int index;
  for (index = start.y; index >= (int)end.y; index--) {
    (*spiral)[index][start.x] = value++;
  }
  board->leftFilled++;

  if (value != board->cellCount) {
    CELL s;
    CELL e;

    s.x = end.x + 1;
    s.y = end.y;
    e.x = (board->width - 1) - board->rightFilled;
    e.y = s.y;
    moveRight(spiral, board, s, e, value);
  }
}

void moveLeft(UINT4 ***spiral, BOARD *board, CELL start, CELL end, UINT4 value) { 
  int index;
  for (index = start.x; index >= (int)end.x; index--) {
    (*spiral)[start.y][index] = value++;
  }
  board->bottomFilled++;
  
  if (value != board->cellCount) {
    CELL s;
    CELL e;

    s.x = end.x;
    s.y = end.y - 1;
    e.x = s.x;
    e.y = board->topFilled;
    moveUp(spiral, board, s, e, value);
  }
}

void moveDown (UINT4 ***spiral, BOARD *board, CELL start, CELL end, UINT4 value) { 
  int index;
  for (index = start.y; index <= end.y; index++) {
    (*spiral)[index][start.x] = value++;
  }
  board->rightFilled++;
  
  if (value != board->cellCount) {
    CELL s;
    CELL e;

    s.x = end.x - 1;
    s.y = end.y;
    e.x = board->leftFilled; 
    e.y = s.y;
    moveLeft(spiral, board, s, e, value);
  }
}

void moveRight(UINT4 ***spiral, BOARD *board, CELL start, CELL end, UINT4 value) {
  int index;
  for (index = start.x; index <= end.x; index++) {
    (*spiral)[start.y][index] = value++;
  }
  board->topFilled++;
  
  if (value != board->cellCount) {
    CELL s;
    CELL e;
    
    s.x = end.x;
    s.y = end.y + 1;
    e.x = s.x;
    e.y = (board->height - 1) - board->bottomFilled;
    moveDown(spiral, board, s, e, value);
  }
}

void whirlAround(UINT4 ***spiral, const UINT4 width, const UINT4 height) {
  CELL start;
  CELL end;
  BOARD board;

  start.x = 0;
  start.y = 0;
  end.x = width - 1;
  end.y = 0;

  board.width = width;
  board.height = height;
  board.cellCount = width * height;
  board.leftFilled = 0;
  board.rightFilled = 0;
  board.topFilled = 0;
  board.bottomFilled = 0;

  moveRight(spiral, &board, start, end, 0);
}

void makeSpiral(const UINT4 width, const UINT4 height) {
  UINT4 **spiral;
  UINT4 index;

  spiral = malloc(sizeof(*spiral) * height);
  for (index = 0; index < height; index++) {
    spiral[index] = malloc(sizeof(UINT4) * width);
  }

  whirlAround(&spiral, width, height);
  printSpiral(spiral, width, height);

  for (index = 0; index < height; index++) {
    free(spiral[index]);
  }
  free(spiral);
}

int main(int argc, char** argv) {
  UINT4 width;
  UINT4 height;	

  printf("Spiral Array Width: ");
  scanf("%u", &width);
  printf("Spiral Array height: ");
  scanf("%u", &height);
  printf("%u x %u\n", width, height);

  makeSpiral(width, height);

  return 0;
}
