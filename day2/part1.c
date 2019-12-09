#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../helper/loop.h"

int *state;

int main(void) {

  input_t input = open_input("input.txt");

  state = (int *)malloc(1024);
  memset(state, 0, 1024);

  int count = 0;
  loop_lines(input) {
    state[count++] = atoi(input.line);
  }

  for (int i = 0; i < count; i++) {
    printf("%i,", state[i]);
  }
  printf("\n");
  printf("\n");

  state[1] = 12;
  state[2] = 2;

  int cur = 0;
  while (state[cur] != 99) {
    switch (state[cur]) {
      case 1:
        state[state[cur + 3]] = state[state[cur + 1]] + state[state[cur + 2]];
        break;
      case 2:
        state[state[cur + 3]] = state[state[cur + 1]] * state[state[cur + 2]];
        break;
    }
    cur += 4;
  }

  for (int i = 0; i < count; i++) {
    printf("%i,", state[i]);
  }
  printf("\n");

  printf("answer: %i\n", state[0]);

  return 0;
}

