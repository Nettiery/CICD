#include <getopt.h>
#include <stdio.h>
#include <string.h>

#include "flag_struct.h"
#include "parser.h"
#include "reader.h"

int main(int argc, char **argv) {
  int err = 0, err_flag = 0;
  flg flag = {0};
  err_flag = parser(argc, argv, &flag);
  if (err_flag == -1) printf("invalid option\n");
  if (flag.b == 1) {
    flag.n = 0;
  }
  while (optind < argc) {
    err = reader(argv, &flag);
    optind++;
  }
  if (err == -1) printf("No such file or directory");
  return err;
}
