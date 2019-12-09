#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "../helper/loop.h"

int* state;

int set_val(int num, int idx) {
  state[idx] = num;
}

int get_val(int mode, int num) {
  switch (mode) {
    case 0:
      return state[num];
    case 1:
      return num;
  }
}

int *get_modes(int num) {
  int *modes = malloc(3);
  modes[0] = (num % 1000) / 100;
  modes[1] = num / 1000;
  modes[2] = 0;
  return modes;
}

int main(void) {

  input_t input = open_input("input.txt");

  state = (int *)malloc(1024);
  memset(state, 0, 1024);

  int count = 0;
  loop_lines(input) {
    state[count++] = atoi(input.line);
  }

  char in[12];
  int cur = 0;
  while (state[cur] != 99) {
    int op = state[cur] % 100;
    int *modes = get_modes(state[cur] - op);
    switch (op) {
      case 1:
        set_val(get_val(modes[0], state[cur + 1]) + get_val(modes[1], state[cur + 2]), state[cur + 3]);
        cur += 4;
        break;
      case 2:
        set_val(get_val(modes[0], state[cur + 1]) * get_val(modes[1], state[cur + 2]), state[cur + 3]);
        cur += 4;
        break;
      case 3:
        fgets(in, 12, stdin);
        set_val(atoi(in), state[cur + 1]);
        cur += 2;
        break;
      case 4:
        printf("%i\n", get_val(modes[0], state[cur + 1]));
        cur += 2;
        break;
    }
    free(modes);
  }

  return 0;
}
