#include <stdlib.h>
#include <stdio.h>

#include "../helper/loop.h"

int recurse_mass(int mass) {
  int calc = (int)(mass/3.0) - 2;
  if (calc <= 0)
    return 0;
  return calc + recurse_mass(calc);
}

int main(void) {

  input_t input = open_input("input.txt");
  
  int sum = 0;
  loop_lines(input) {
    sum += recurse_mass(atoi(input.line));
  }

  printf("answer: %i\n", sum);

  return 0;
}
