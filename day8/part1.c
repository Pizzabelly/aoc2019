#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "../helper/loop.h"

int main(void) {

  input_t input = open_input("input.txt");

  char *string;
  loop_lines(input) {
    string = input.line;
  }

  int layers[125][25][6];

  int layer = 0;
  for (int i = 0; i < strlen(string) - 1; i++) {
    int lay = i - (layer * 25 * 6);
    int x = lay % 25;
    int y = lay / 25;
    int num = string[i] - '0';
    printf("layer: %i, x: %i y: %i\n", layer, x, y);
    layers[layer][x][y] = num;
    if (i == (25 * 6 * (layer + 1))) layer++;
  }
  
  printf("layer count: %i\n", layer);

  int least_zero = INT_MAX;
  int layer_zero = -1;

  for (int i = 0; i < layer + 1; i++) {
    int zeros = 0;
    for (int j = 0; j < (25 * 6) + 1; j++) {
      int x = j % 25;
      int y = j / 25;
      if (layers[i][x][y] == 0) {
        zeros++;
      }
    }

    if (zeros < least_zero) {
      least_zero = zeros;
      layer_zero = i;
    }
  }
  
  printf("zero: %i, layer: %i\n", least_zero, layer_zero);

  int ones = 0, twos = 0;
  for (int i = 0; i < (25 * 6) + 1; i++) {
    int x = i % 25;
    int y = i / 25;
    if (layers[layer_zero][x][y] == 1) ones++;
    if (layers[layer_zero][x][y] == 2) twos++;
  }

  printf("ans: %i\n", ones * twos);

  return 0;
}
