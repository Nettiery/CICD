#ifndef PARSER_GREP
#define PARSER_GREP
#include "flag_grep_struct.h"

int parser_grep(int argc, char *argv[], flg_grep *flag_grep);
int add_pattern(flg_grep *flag_grep, char *load_str);
void add_pattern_from_file(flg_grep *flag_grep, char *load_str);

#endif