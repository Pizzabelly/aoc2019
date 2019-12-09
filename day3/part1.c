#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#include "../helper/loop.h"

typedef struct {
  int count;
  vec2 *entries;
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
    .entries = (vec2 *)malloc(sizeof(vec2) * 1000000),
    .pos = (vec2){ 0, 0 }
  };

  line_t line2 = (line_t){
    .count = 0,
    .entries = (vec2 *)malloc(sizeof(vec2) * 1000000),
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
      cur_line->pos.x += offset.x;
      cur_line->pos.y += offset.y;
      cur_line->entries[cur_line->count++] = cur_line->pos;
    }
  }

  int min_dist = INT_MAX;
  for (int i = 0; i < line1.count; i++) {
    for (int j = 0; j < line2.count; j++) {
      if (line1.entries[i].x == line2.entries[j].x && 
          line1.entries[i].y == line2.entries[j].y) {
        int dist = abs(0 - line2.entries[j].x) + abs(0 - line2.entries[j].y);
        if (dist < min_dist && dist != 0) 
          min_dist = dist;
      }
    }
  }

  printf("answer: %i\n", min_dist);

  return 0;
}
