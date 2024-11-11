#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "flag_grep_struct.h"
#include "parser_grep.h"

void compilation(flg_grep *flag_grep);
void flag_l(FILE *file_name, char *name, flg_grep *flag_grep);
void flag_c(FILE *file_name, char *name, flg_grep *flag_grep);
void flag_e(FILE *file_name, char *name, flg_grep *flag_grep);
void flag_v(FILE *file_name, char *name, flg_grep *flag_grep);
void flag_o(FILE *file_name, char *name, flg_grep *flag_grep);

int grep(flg_grep *flag_grep, char *argv[]) {
  FILE *file_name = fopen(argv[optind], "r");
  int err = 0;
  if (file_name != 0) {
    if (flag_grep->l) {
      flag_l(file_name, argv[optind], flag_grep);
    } else if (flag_grep->c) {
      flag_c(file_name, argv[optind], flag_grep);
    } else if (flag_grep->o && !flag_grep->v) {
      flag_o(file_name, argv[optind], flag_grep);
    } else if (flag_grep->v) {
      flag_v(file_name, argv[optind], flag_grep);
    } else if (flag_grep->e || flag_grep->f || flag_grep->flag_count == 0 ||
               (flag_grep->i && !flag_grep->v) || flag_grep->h ||
               ((flag_grep->n) && flag_grep->flag_count == 1)) {
      flag_e(file_name, argv[optind], flag_grep);
    }
    fclose(file_name);
  } else if (!flag_grep->s)
    printf("%s: No such file or directory\n", argv[optind]);
  return err;
}

void flag_e(FILE *file_name, char *name, flg_grep *flag_grep) {
  char curr_str[1024] = {'\0'};
  size_t line_count = 0;
  while (fgets(curr_str, sizeof(curr_str), file_name) != NULL) {
    line_count++;
    for (size_t i = 0; i < flag_grep->Patts.cur_size; i++)
      if (!regexec(&flag_grep->Patts.reg_sample[i], curr_str, 0, NULL, 0)) {
        if (flag_grep->file_count > 1 && !flag_grep->h) {
          fprintf(stdout, "%s:", name);
        }
        if (flag_grep->n) printf("%zu:", line_count);
        fprintf(stdout, "%s", curr_str);
      }
  }
}

void flag_l(FILE *file_name, char *name, flg_grep *flag_grep) {
  char curr_str[1024] = {'\0'};
  int count_match = 0, count_unmatch = 0;
  while (fgets(curr_str, sizeof(curr_str), file_name) != NULL) {
    for (size_t i = 0; i < flag_grep->Patts.cur_size; i++) {
      if (!flag_grep->v) {
        if (!regexec(&flag_grep->Patts.reg_sample[i], curr_str, 0, NULL, 0) &&
            count_match == 0) {
          fprintf(stdout, "%s\n", name);
          count_match++;
        }
      } else {
        if (regexec(&flag_grep->Patts.reg_sample[i], curr_str, 0, NULL, 0) !=
                0 &&
            count_unmatch == 0) {
          fprintf(stdout, "%s", name);
          count_unmatch++;
        }
      }
    }
  }
}

void flag_c(FILE *file_name, char *name, flg_grep *flag_grep) {
  char curr_str[1024] = {'\0'};
  int count_match = 0, count_unmatch = 0;
  while (fgets(curr_str, sizeof(curr_str), file_name) != NULL) {
    for (size_t i = 0; i < flag_grep->Patts.cur_size; i++) {
      if (!regexec(&flag_grep->Patts.reg_sample[i], curr_str, 0, NULL, 0)) {
        count_match++;
      } else {
        count_unmatch++;
      }
    }
  }
  if (flag_grep->file_count > 1 && !flag_grep->h) {
    fprintf(stdout, "%s:", name);
  }
  if (flag_grep->v)
    fprintf(stdout, "%d\n", count_unmatch);
  else {
    fprintf(stdout, "%d\n", count_match);
  }
}
void flag_v(FILE *file_name, char *name, flg_grep *flag_grep) {
  char curr_str[1024] = {'\0'};
  size_t line_count = 0;
  while (fgets(curr_str, sizeof(curr_str), file_name) != NULL) {
    line_count++;
    for (size_t i = 0; i < flag_grep->Patts.cur_size; i++)
      if (regexec(&flag_grep->Patts.reg_sample[i], curr_str, 0, NULL, 0) != 0) {
        {
          if (flag_grep->file_count > 1 && !flag_grep->h) {
            fprintf(stdout, "%s:", name);
          }
          if (flag_grep->n) printf("%zu:", line_count);
          fprintf(stdout, "%s\n", curr_str);
        }
      }
  }
}

void flag_o(FILE *file_name, char *name, flg_grep *flag_grep) {
  char curr_str[1024] = {'\0'};
  regmatch_t match = {0};
  size_t line_count = 0;
  while (fgets(curr_str, sizeof(curr_str), file_name) != NULL) {
    char *temp_str = curr_str;
    line_count++;
    for (size_t i = 0; i < flag_grep->Patts.cur_size; i++) {
      size_t nmatch = 1;
      while (!regexec(&flag_grep->Patts.reg_sample[i], temp_str, nmatch, &match,
                      0)) {
        if (flag_grep->file_count > 1 && !flag_grep->h) {
          fprintf(stdout, "%s:", name);
        }
        if (flag_grep->n) printf("%zu:", line_count);
        printf("%.*s\n", (int)(match.rm_eo - match.rm_so),
               temp_str + match.rm_so);
        temp_str += match.rm_eo;
      }
    }
  }
}

void compilation(flg_grep *flag_grep) {
  for (size_t i = 0; i < flag_grep->Patts.cur_size; i++) {
    if (flag_grep->i) {
      regcomp(&flag_grep->Patts.reg_sample[i], flag_grep->Patts.sample[i],
              REG_ICASE);
    } else
      regcomp(&flag_grep->Patts.reg_sample[i], flag_grep->Patts.sample[i], 0);
  }
}
