#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#include "../helper/c_hashmap/hashmap.h"
#include "../helper/loop.h"

typedef struct {
  int x;
  int y;
  int steps;
} entry_t;

typedef struct {
  int count;
  int steps;
  map_t entries;
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
} int main(void) {

  input_t input = open_input("input.txt");

  line_t line = (line_t){
    .count = 0,
    .steps = 0,
    .entries = hashmap_new(),
    .pos = (vec2){ 0, 0 }
  };

  int second_line = 0;

  vec2 offset;
  int min_steps = INT_MAX;
  loop_lines(input) {

    if (*input.line == 'n') {
      line.pos = (vec2){0, 0};
      line.steps = 0;
      second_line = 1;
      continue;
    }

    get_offset(*input.line, &offset);

    int count = atoi(++input.line);
    for (int i = 0; i < count; i++) {
      line.steps++;
      line.pos.x += offset.x;
      line.pos.y += offset.y;

      char *idx = malloc(64);
      sprintf(idx, "%i,%i", line.pos.x, line.pos.y);

      entry_t *val;
      int res = hashmap_get(line.entries, idx, (void**)(&val));
      if (res == MAP_MISSING && !second_line) {
        entry_t *new = (entry_t *)malloc(sizeof(entry_t));
        memset(new, 0, sizeof(entry_t));
        new->steps = line.steps;
        new->x = line.pos.x;
        new->y = line.pos.y;
        hashmap_put(line.entries, idx, new);
      } else if (res != MAP_MISSING) {
        if (second_line) {
          val->steps += line.steps;
          if (val->steps < min_steps) {
            min_steps = val->steps;
          }
        }
      }
    }
  }

  printf("answer: %i\n", min_steps);

  return 0;
}
