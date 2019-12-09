#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../helper/loop.h"

int main(void) {

  input_t input = open_input("input.txt");

  int *state = (int *)malloc(1024);
  int *init_state = (int *)malloc(1024);
  memset(state, 0, 1024);

  int count = 0;
  loop_lines(input) {
    state[count++] = atoi(input.line);
  }

  memcpy(init_state, state, 1024);

  for (int noun = 0; noun < 100; noun++) {
    for (int verb = 0; verb < 100; verb++) {
      state[1] = noun;
      state[2] = verb;

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

      if (state[0] == 19690720) {
        printf("noun: %i, verb: %i, answer: %i\n", noun, verb, 100 * noun + verb);
        return 0;
      } else {
        memcpy(state, init_state, 1024);
      }
    }
  }

  return 0;
}

