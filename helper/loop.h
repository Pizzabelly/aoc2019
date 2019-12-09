#include <stdio.h>

#ifndef LINE_SIZE
  #define LINE_SIZE 128
#endif

typedef struct {
  int x;
  int y;
} vec2;

typedef struct {
  FILE *fp;
  char *line;
  size_t count;
} input_t;

input_t open_input(char* file_name) {
  input_t input;
  input.fp = fopen(file_name, "r");
  input.line = (char *)malloc(LINE_SIZE);
  return input;
}

#define loop_lines(input) while(getline(&input.line, &input.count, input.fp) != -1)
