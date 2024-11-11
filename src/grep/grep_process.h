#ifndef GREP_PROCESS
#define GREP_PROCESS
#include "flag_grep_struct.h"
#include "parser_grep.h"

int grep(flg_grep *flag_grep, char *argv[]);
void flag_l(FILE *file_name, char *serach_name, flg_grep *flag_grep);
void flag_c(FILE *file_name, char *name, flg_grep *flag_grep);
void flag_e(FILE *file_name, char *name, flg_grep *flag_grep);
void flag_v(FILE *file_name, char *name, flg_grep *flag_grep);
void compilation(flg_grep *flag_grep);

#endif