#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define buff_size 999999
#include "flag_grep_struct.h"
static struct option long_flags[] = {
    {"regexp", required_argument, NULL, 'e'},
    {"file", required_argument, NULL, 'f'},
    {"ignore-case", no_argument, NULL, 'i'},
    {"no-message", no_argument, NULL, 's'},
    {"invert-match", no_argument, NULL, 'v'},
    {"line-number", no_argument, NULL, 'n'},
    {"invert-match", no_argument, NULL, 'v'},
    {"no-filename", no_argument, NULL, 'h'},
    {"only-matching", no_argument, NULL, 'o'},
    {"files-with-matches", no_argument, NULL, 'l'},
    {"count", no_argument, NULL, 'c'},
    {"help", no_argument, NULL, 0},
    {NULL, 0, NULL, 0}

};

int add_pattern(flg_grep *flag_grep, char *load_str);
void add_pattern_from_file(flg_grep *flag_grep, char *load_str);

int parser_grep(int argc, char *argv[], flg_grep *flag_grep) {
  int f = 0, result = 0, index = 0;
  while ((f = getopt_long(argc, argv, "ivclnhsoe:f:", long_flags, &index)) !=
         -1) {
    switch (f) {
      case 'e': {
        flag_grep->e = 1;
        add_pattern(flag_grep, optarg);
        flag_grep->flag_count++;
      } break;
      case 'f': {
        flag_grep->f = 1;
        add_pattern_from_file(flag_grep, optarg);
        flag_grep->flag_count++;
      } break;
      case 'i':
        flag_grep->i = 1;
        flag_grep->flag_count++;
        break;
      case 'v':
        flag_grep->v = 1;
        flag_grep->flag_count++;
        break;
      case 'c':
        flag_grep->c = 1;
        flag_grep->flag_count++;
        break;
      case 'h':
        flag_grep->h = 1;
        flag_grep->flag_count++;
        break;
      case 'l':
        flag_grep->l = 1;
        flag_grep->flag_count++;
        break;
      case 'n':
        flag_grep->n = 1;
        flag_grep->flag_count++;
        break;
      case 's':
        flag_grep->s = 1;
        flag_grep->flag_count++;
        break;
      case 'o':
        flag_grep->o = 1;
        flag_grep->flag_count++;
        break;
      case '?':
        result = 1;
        flag_grep->flag_count++;
        break;
    }
  }

  return result;
}

int add_pattern(flg_grep *flag_grep, char *orig_str) {
  strcpy(flag_grep->Patts.sample[flag_grep->Patts.cur_size], orig_str);
  flag_grep->Patts.cur_size++;
  return 0;
}

void add_pattern_from_file(flg_grep *flag_grep, char *filename) {
  FILE *file = fopen(filename, "r");
  if (file != 0) {
    char buffer_str[buff_size];
    int count = 0;
    char c = fgetc(file);
    while (c != '\0') {
      buffer_str[count] = c;
      count++;
      c = fgetc(file);
    }
    buffer_str[count] = '\0';
    strcpy(flag_grep->Patts.sample[flag_grep->Patts.cur_size], buffer_str);
    flag_grep->Patts.cur_size++;
    fclose(file);
  } else
    fprintf(stdout, "%s: No such file or directory\n", filename);
}