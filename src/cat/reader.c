#include <getopt.h>
#include <stdio.h>
#include <string.h>

#include "flag_struct.h"

int flag_v(int current_sym);

int reader(char *argv[], flg *flag) {
  int err = 0;
  FILE *file_name = fopen(argv[optind], "r");
  if (file_name != NULL) {
    int str_count = 1;
    int empty_str_count = 0;
    int previos_sym = '\n';
    while (1) {
      int current_sym = fgetc(file_name);
      if (current_sym == EOF) {
        break;
      }
      if (flag->s && current_sym == '\n' && previos_sym == '\n') {
        empty_str_count++;
        if (empty_str_count > 1) {
          continue;
        }
      } else {
        empty_str_count = 0;
      }
      if (previos_sym == '\n' &&
          ((flag->b && current_sym != '\n') || flag->n)) {
        printf("%6d\t", str_count++);
      }
      if (flag->e && current_sym == '\n' && flag->b && previos_sym == '\n')
        printf("        $");
      else if ((flag->e && current_sym == '\n'))
        printf("$");

      if (flag->t && current_sym == '\t') {
        printf("^");
        current_sym = 'I';
      }
      if (flag->v) {
        current_sym = flag_v(current_sym);
      }
      printf("%c", current_sym);
      previos_sym = current_sym;
    }
    fclose(file_name);
  } else
    err = -1;
  return err;
}

int flag_v(int c) {
  if (c > 127 && c < 160) printf("M-^");
  if ((c < 32 && c != '\n' && c != '\t') || c == 127) printf("^");
  if ((c < 32 || (c > 126 && c < 160)) && c != '\n' && c != '\t')
    c = c > 126 ? c - 128 + 64 : c + 64;
  return c;
}