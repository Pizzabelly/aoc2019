#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define LINE_SIZE 12

#include "../helper/loop.h"

static long *state;
static long offset = 0;
static long pc = 0;
static int mem_count = 17154;

static long getv(int mode, long pc) {
  switch (mode) {
    case 0:
      return state[state[pc]];
    case 1:
      return state[pc];
    case 2:
      return state[state[pc] + offset];
  }
}

static void setv(long num, int mode, int idx) {
  switch (mode) {
    case 0:
      state[state[idx]] = num;
      break;
    case 2:
      state[state[idx] + offset] = num;
      break;
  }
}

static inline int *get_modes(long num) {
  char str[5];
  sprintf(str, "%li", num / 100);
  
  int chars = strlen(str);
  int *modes = (int *)malloc(3);

  for (int i = 0; i < 3; i++) {
    if (i + 1 > chars) modes[i] = 0;
    else modes[i] = str[chars - (1 + i)] - '0';
  }

  return modes;
}

int main(void) {
  input_t input = open_input("input.txt");

  state = (long *)malloc(sizeof(long) * mem_count);
  memset(state, 0, sizeof(long) * mem_count);

  int count = 0;
  loop_lines(input) {
    state[count++] = atol(input.line);
  }

  char in[12];
  while (state[pc] != 99) {
    int op = state[pc] % 100;
    int *m = get_modes(state[pc] - op);
    switch (op) {
      case 1:
        setv(getv(m[0], pc + 1) + getv(m[1], pc + 2), m[2], pc + 3);
        pc += 4;
        break;
      case 2:
        setv(getv(m[0], pc + 1) * getv(m[1], pc + 2), m[2], pc + 3);
        pc += 4;
        break;
      case 3:
        //fgets(in, 12, stdin);
        //setv(atol(in), m[0], pc + 1);
        setv(2, m[0], pc + 1);
        pc += 2;
        break;
      case 4:
        printf("%li\n", getv(m[0], pc + 1));
        pc += 2;
        break;
      case 5:
        if (getv(m[0], pc + 1) != 0) {
          pc = getv(m[1], pc + 2);
        } else pc += 3;
        break;
      case 6:
        if (getv(m[0], pc + 1) == 0) {
          pc = getv(m[1], pc + 2);
        } else pc += 3;
        break;
      case 7:
        if (getv(m[0], pc + 1) < getv(m[1], pc + 2)) {
          setv(1, m[2], pc + 3);
        } else {
          setv(0, m[2], pc + 3);
        }
        pc += 4;
        break;
      case 8:
        if (getv(m[0], pc + 1) == getv(m[1], pc + 2)) {
          setv(1, m[2], pc + 3);
        } else {
          setv(0, m[2], pc + 3);
        }
        pc += 4;
        break;
      case 9:
        offset += getv(m[0], pc + 1);
        pc += 2;
        break;
    }
    
    free(m);
  }

  return 0;
}
