#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../helper/loop.h"

typedef struct orbital {
  char *str;

  int count;
  struct orbital **next;
  struct orbital *back;
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

int transverse_orb(orbital_t *orb, char *target) {
  orbital_t *cur = orb;

  if (!strcmp(cur->str, target)) {
    return 1;
  }

  int found = 0;
  for (int i = 0; i < cur->count; i++) {
    found += transverse_orb(cur->next[i], target);
  }
  
  return found;
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
    orbital_t *next = find_orb(part);
    orb->next[orb->count++] = next;
    next->back = orb;
  }

  orbital_t *you = find_orb("YOU");
  int count = 0;
  while (1) {
    count++;
    if (transverse_orb(you->back, "SAN")) {
      char *target = you->str;
      orbital_t *san = find_orb("SAN");
      while (1) {
        count++;
        if (transverse_orb(san->back, target))
          break;
        
        san = san->back;
      }
      break;
    }
    you = you->back;
  }

  printf("ans: %i\n", count - 2);
  
  return 0;
}
