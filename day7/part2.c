#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "../helper/loop.h"

enum {
  OUTPUT_CHANGED = 1,
};

typedef struct {
  int *state;
  int pc;
  int mem_count;
  int output;

  int input;
  int phase;

  int flags;
} instance_t;

instance_t amps[5];

void init_inst(int *init, instance_t *i) {
  i->mem_count = 2048;
  i->state = malloc(sizeof(int) * i->mem_count); 
  memset(i->state, 0, sizeof(int) * i->mem_count);
  memcpy(i->state, init, sizeof(int) * 1024);
  i->pc = 0;
  i->output = 0;
  i->flags = 0;
  i->input = 0;
  i->phase = 0;
}

void set_val(instance_t *i, int num, int idx) {
  if (idx > i->mem_count) {
    printf("realloc: %i\n", idx);
    i->state = realloc(i->state, idx + 1);
    i->mem_count = idx;
  }
  i->state[idx] = num;
}

int get_val(instance_t *i, int mode, int num) {
  switch (mode) {
    case 0:
      return i->state[num];
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

int *get_inputs(int num) {
  int *inputs = malloc(5);
  inputs[0] = num / 10000;
  inputs[1] = (num % 10000) / 1000;
  inputs[2] = (num % 1000) / 100;
  inputs[3] = (num % 100) / 10;
  inputs[4] = (num % 10);

  for (int i = 0; i < 5; i++) {
    if (inputs[i] < 5) return NULL;
    for (int j = 0; j < 5; j++) {
      if (inputs[i] == inputs[j] && i != j)
        return NULL;
    }
  }

  return inputs;
}

void op_code(instance_t *inst) {
  int op = get_val(inst, 0, inst->pc) % 100;
  int *modes = get_modes(get_val(inst, 0, inst->pc) - op);
  switch (op) {
    case 1:
      set_val(inst, get_val(inst, modes[0], get_val(inst, 0, inst->pc + 1)) + get_val(inst, modes[1], get_val(inst, 0, inst->pc + 2)), get_val(inst, 0, inst->pc + 3));
      inst->pc += 4;
      break;
    case 2:
      set_val(inst, get_val(inst, modes[0], get_val(inst, 0, inst->pc + 1)) * get_val(inst, modes[1], get_val(inst, 0, inst->pc + 2)), get_val(inst, 0, inst->pc + 3));
      inst->pc += 4;
      break;
    case 3:
      //fgets(in, 12, stdin);
      //set_val(inst, atoi(inst->input), get_val(inst, 0, inst->pc + 1));
      set_val(inst, inst->phase >= 0 ? inst->phase : inst->input, get_val(inst, 0, inst->pc + 1));
      inst->phase = -1;
      inst->pc += 2;
      break;
    case 4:
      inst->output = get_val(inst, modes[0], get_val(inst, 0, inst->pc + 1));
      inst->flags |= OUTPUT_CHANGED;
      inst->pc += 2;
      break;
    case 5:
      if (get_val(inst, modes[0], get_val(inst, 0, inst->pc + 1))) {
        inst->pc = get_val(inst, modes[1], get_val(inst, 0, inst->pc + 2));
      } else inst->pc += 3;
      break;
    case 6:
      if (!get_val(inst, modes[0], get_val(inst, 0, inst->pc + 1))) {
        inst->pc = get_val(inst, modes[1], get_val(inst, 0, inst->pc + 2));
      } else inst->pc += 3;
      break;
    case 7:
      if (get_val(inst, modes[0], get_val(inst, 0, inst->pc + 1)) < get_val(inst, modes[1], get_val(inst, 0, inst->pc + 2))) {
        set_val(inst, 1, get_val(inst, 0, inst->pc + 3));
      } else {
        set_val(inst, 0, get_val(inst, 0, inst->pc + 3));
      }
      inst->pc += 4;
      break;
    case 8:
      if (get_val(inst, modes[0], get_val(inst, 0, inst->pc + 1)) == get_val(inst, modes[1], get_val(inst, 0, inst->pc + 2))) {
        set_val(inst, 1, get_val(inst, 0, inst->pc + 3));
      } else {
        set_val(inst, 0, get_val(inst, 0, inst->pc + 3));
      }
      inst->pc += 4;
      break;
  }
}

int main(void) {

  input_t input = open_input("input.txt");

  int count = 0;

  int *init = malloc(sizeof(int) * 1024);
  memset(init, 0, sizeof(int) * 1024);
  loop_lines(input) {
    init[count++] = atoi(input.line);
  }

  int max = 0;
  for (int j = 55555; j < 100000; j++) {
    int *inputs = get_inputs(j);
    if (inputs == NULL) continue;

    for (int i = 0; i < 5; i++) {
      init_inst(init, &amps[i]);
      amps[i].phase = inputs[i];
    }

    int i = 0;
    int out = 0;

    while (get_val(&amps[i], 0, amps[i].pc) != 99) {
      op_code(&amps[i]);
      
      if (amps[i].flags & OUTPUT_CHANGED) {
        out = amps[i].output;
        amps[i].flags = 0;
        i++; i %= 5; 
        amps[i].input = out;
      }
    }

    if (amps[4].output > max) {
      max = amps[4].output;
    }
  }

  printf("ans: %i\n", max);

  return 0;
}
