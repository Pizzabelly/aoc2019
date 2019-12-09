#include <stdio.h>

#define START 156218
#define END 652527

enum {
  ADJ = 1,
  INC = 1 << 1
};

int main(void) {

  int total = 0;

  int num[6];
  int flags = 0;
  for (int i = START; i < END + 1; i++) {
    num[0] = i / 100000;
    num[1] = (i % 100000) / 10000;
    num[2] = (i % 10000) / 1000;
    num[3] = (i % 1000) / 100;
    num[4] = (i % 100) / 10;
    num[5] = (i % 10);

    flags |= INC;
    for (int j = 0; j < 5; j++) {
      if (num[j] == num[j + 1])
        flags |= ADJ;
      if (num[j] > num[j + 1])
        flags &= ~INC;
    }

    if (flags == 3)
      total++;

    flags = 0;
  }

  printf("answer: %i\n", total);

  return 0;
}
