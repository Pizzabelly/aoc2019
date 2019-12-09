#include <stdlib.h>
#include <stdio.h>

#include "../helper/loop.h"

int main(void) {

  input_t input = open_input("input.txt");
  
  int sum = 0;
  loop_lines(input) {
    sum += (int)(atoi(input.line)/3.0) - 2;
  }

  printf("answer: %i\n", sum);

  return 0;
}
