#include <getopt.h>
#include <stdio.h>
#include <string.h>

#include "flag_struct.h"

static struct option options[] = {
    {"number-nonblank", 0, 0, 'b'},
    {"number", 0, 0, 'n'},
    {"squeeze-blank", 0, 0, 's'},
    {0, 0, 0, 0},
};

int parser(int argc, char **argv, flg *flag) {
  int f;
  int err = 0;
  int index = 0;
  while ((f = getopt_long(argc, argv, "benstvTE", options, &index)) != -1) {
    switch (f) {
      case 'b':
        flag->b = 1;
        break;
      case 'E':
        flag->e = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 'T': {
        flag->t = 1;
      } break;
      case 'v':
        flag->v = 1;
        break;
      case 'e':
        flag->e = 1;
        flag->v = 1;
        break;
      case 't':
        flag->t = 1;
        flag->v = 1;
        break;
      case '?':
        err = -1;
        break;
    }
  }
  return err;
}