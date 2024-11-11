#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "flag_grep_struct.h"
#include "grep_process.h"
#include "parser_grep.h"

int main(int argc, char *argv[]) {
  int result = 0;
  flg_grep flag_grep = {0};
  if (argc > 2) {
    result = parser_grep(argc, argv, &flag_grep);

    if (!flag_grep.f && !flag_grep.e) {
      add_pattern(&flag_grep, argv[optind]);
      optind++;
    }

    flag_grep.file_count = argc - optind;
    compilation(&flag_grep);
    while (optind < argc) {
      result = grep(&flag_grep, argv);
      optind++;
      if (flag_grep.v && flag_grep.file_count > 1) printf("\n");
    }
    for (size_t i = 0; i < flag_grep.Patts.cur_size; i++) {
      regfree(&flag_grep.Patts.reg_sample[i]);
    }
  } else
    result = 1;
  return result;
}
