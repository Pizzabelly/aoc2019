#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "../helper/loop.h"

int main(void) {

  input_t input = open_input("input.txt");

  loop_lines(input) {}

  int layers[125][25][6];

  int layer = 0;
  for (int i = 0; i < strlen(input.line); i++) {
    int lay = i - (layer * 25 * 6);
    int x = lay % 25;
    int y = lay / 25;
    int num = input.line[i] - '0';
    layers[layer][x][y] = num;
    if (i == (25 * 6 * (layer + 1))) layer++;
  }
  
  printf("layer count: %i\n", layer);

  int final_pic[25][6];
  for (int y = 0; y < 6; y++) {
    for (int x = 0; x < 25; x++) {
      for (int j = 0; j < layer + 1; j++) {
        if (layers[j][x][y] <= 1) {
          final_pic[x][y] = layers[j][x][y];
          break;
        }
      }
    }
  }

  for (int y = 0; y < 6; y++) {
    for (int x = 0; x < 25; x++) {
      if (final_pic[x][y] == 1) 
        printf("[]");
      else
        printf("  ");
        
    }
    printf("\n");
  }

  return 0;
}
