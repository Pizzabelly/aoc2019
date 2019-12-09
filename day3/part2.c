#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#include "../helper/loop.h"

typedef struct {
  vec2 pos;
  int steps;
} entry_t;

typedef struct {
  int count;
  int steps;
  entry_t *entries;
  vec2 pos;
} line_t;

void get_offset(char d, vec2 *offset) {
  switch (d) {
    case 'R':
      *offset = (vec2){1, 0};
      break;
    case 'L':
      *offset = (vec2){-1, 0};
      break;
    case 'U':
      *offset = (vec2){0, -1};
      break;
    case 'D':
      *offset = (vec2){0, 1};
      break;
  }
}

int main(void) {

  input_t input = open_input("input.txt");

  line_t line1 = (line_t){
    .count = 0,
    .steps = 0,
    .entries = (entry_t *)malloc(sizeof(entry_t) * 1000000),
    .pos = (vec2){ 0, 0 }
  };

  line_t line2 = (line_t){
    .count = 0,
    .steps = 0,
    .entries = (entry_t *)malloc(sizeof(entry_t) * 1000000),
    .pos = (vec2){ 0, 0 }
  };

  line_t *cur_line = &line1;

  vec2 offset;
  loop_lines(input) {

    if (*input.line == 'n') {
      cur_line = &line2;
      continue;
    }

    get_offset(*input.line, &offset);

    int count = atoi(++input.line);
    for (int i = 0; i < count; i++) {
      cur_line->steps++;
      cur_line->pos.x += offset.x;
      cur_line->pos.y += offset.y;

      int repeat = 0;
      for (int j = 0; j < cur_line->count; j++) {
        if (cur_line->entries[j].pos.x == cur_line->pos.x &&
            cur_line->entries[j].pos.y == cur_line->pos.y)
          repeat = 1;
      }

      if (repeat) continue;

      cur_line->entries[cur_line->count++] = (entry_t) {
        .pos = cur_line->pos,
        .steps = cur_line->steps
      };
    }
  }

  int min_steps = INT_MAX;
  for (int i = 0; i < line1.count; i++) {
    for (int j = 0; j < line2.count; j++) {
      if (line1.entries[i].pos.x == line2.entries[j].pos.x && 
          line1.entries[i].pos.y == line2.entries[j].pos.y) {
        int steps = line1.entries[i].steps + line2.entries[j].steps;
        if (steps < min_steps && steps != 0) 
          min_steps = steps;
      }
    }
  }

  printf("answer: %i\n", min_steps);

  return 0;
}
