#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../helper/loop.h"

typedef struct orbital {
  char *str;
  int count;
  struct orbital **next;
} orbital_t;

int orb_count;
orbital_t *orbs;

orbital_t *find_orb(char* name) {
  for (int i = 0; i < orb_count; i++) {
    if (!strcmp(name, orbs[i].str)) {
      return &orbs[i];
    }
  }

  orbs[orb_count] = (orbital_t) {
    .str = name,
    .count = 0,
    .next = malloc(sizeof(orbital_t) * 10)
  };

  return &orbs[orb_count++];
}

int transverse_orb(orbital_t *orb) {
  orbital_t *cur = orb;
  int count = 1;
  for (int i = 0; i < cur->count; i++)
    count += transverse_orb(cur->next[i]);
  
  return count;
}

int main(void) {
  
  input_t input = open_input("input.txt");

  orbs = (orbital_t *)malloc(sizeof(orbital_t) * 10000);
  orb_count = 0;

  loop_lines(input) {
    char* line = malloc(24);
    memcpy(line, input.line, 24);

    char *part = strtok(line, ")");
    orbital_t *orb = find_orb(part);
    part = strtok(NULL, "\n");
    orb->next[orb->count++] = find_orb(part);
  }

  int total = 0;
  for (int i = 0; i < orb_count; i++) {
    total += transverse_orb(&orbs[i]) - 1;
  }

  printf("ans: %i\n", total);
  
  return 0;
}
