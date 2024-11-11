#ifndef FLAG_GREP_STRUCT
#define FLAG_GREP_STRUCT
#include <regex.h>
#include <stdio.h>

typedef struct Patterns {
  regex_t reg_sample[1024];
  char sample[1024][1024];
  size_t cur_size;
} Patterns;

typedef struct flag_grep {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  struct Patterns Patts;
  int file_count;
  int flag_count;
} flg_grep;

#endif