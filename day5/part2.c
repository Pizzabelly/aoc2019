#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "../helper/loop.h"

int *state;
int mem_count = 171323954;

void set_val(int num, int idx) {
  if (idx > mem_count) {
    printf("realloc: %i\n", idx);
    state = realloc(state, idx + 1);
    mem_count = idx;
  }
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

  state = (int *)malloc(mem_count);
  memset(state, 0, mem_count);

  int count = 0;
  loop_lines(input) {
    set_val(atoi(input.line), count++);
  }

  char in[12];
  int cur = 0;
  while (get_val(0, cur) != 99) {
    int op = get_val(0, cur) % 100;
    int *modes = get_modes(get_val(0, cur) - op);
    switch (op) {
      case 1:
        set_val(get_val(modes[0], get_val(0, cur + 1)) + get_val(modes[1], get_val(0, cur + 2)), get_val(0, cur + 3));
        cur += 4;
        break;
      case 2:
        set_val(get_val(modes[0], get_val(0, cur + 1)) * get_val(modes[1], get_val(0, cur + 2)), get_val(0, cur + 3));
        cur += 4;
        break;
      case 3:
        fgets(in, 12, stdin);
        set_val(atoi(in), get_val(0, cur + 1));
        cur += 2;
        break;
      case 4:
        printf("%i\n", get_val(modes[0], get_val(0, cur + 1)));
        cur += 2;
        break;
      case 5:
        if (get_val(modes[0], get_val(0, cur + 1))) {
          cur = get_val(modes[1], get_val(0, cur + 2));
        } else cur += 3;
        break;
      case 6:
        if (!get_val(modes[0], get_val(0, cur + 1))) {
          cur = get_val(modes[1], get_val(0, cur + 2));
        } else cur += 3;
        break;
      case 7:
        if (get_val(modes[0], get_val(0, cur + 1)) < get_val(modes[1], get_val(0, cur + 2))) {
          set_val(1, get_val(0, cur + 3));
        } else {
          set_val(0, get_val(0, cur + 3));
        }
        cur += 4;
        break;
      case 8:
        if (get_val(modes[0], get_val(0, cur + 1)) == get_val(modes[1], get_val(0, cur + 2))) {
          set_val(1, get_val(0, cur + 3));
        } else {
          set_val(0, get_val(0, cur + 3));
        }
        cur += 4;
        break;
    }
  }

  return 0;
}

