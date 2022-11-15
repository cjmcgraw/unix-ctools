#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

void split_help(char *msg) {
  fprintf(stderr, "usage: split {options} <delim>");
  fprintf(stderr, "\n");
  fprintf(stderr, "  ERROR: %s", msg);
  fprintf(stderr, "\n");
  fprintf(stderr, "requried parameters:\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "  <delim>            string to split on, can be one or many characters");
  fprintf(stderr, "\n");
  fprintf(stderr, "optional parameters:\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "  --include-delim <before|after>   if the delimiter should be included in the split, and which side\n");
  fprintf(stderr, "  --limit <n>                      limit the split to the first n occurrences on each line\n");
  fprintf(stderr, "  --max <n>                        maximum number of splits to perform total for all lines\n");
  fprintf(stderr, "\n");
}

void split_on_delims(int argc, char **argv) {
  char *delim;
  unsigned int delim_len = 0;
  short include_delim = 0;
  unsigned int limit_per_line = -1;
  unsigned int max = -1;
  unsigned int idx = 0;
  unsigned int line_hits = 0;
  unsigned int occurrences = 0;
  struct Buffer *buf;

  for (int i = 0; i < argc; i++) {
    char *arg = argv[i];
    if (str_startswith(arg, "--")) {
      char *value = argv[++i];
      if (str_equals(arg, "--limit")) {
        limit_per_line = atoi(value);
      } else if (str_equals(arg, "--max")) {
        max = atoi(value);
      } else if (str_equals(arg, "--include-delim")) {
        if (str_equals(value, "before")) {
          include_delim = -1;
        } else {
          include_delim = 1;
        }
      } else {
        split_help("unknown argument!");
        exit(1);
      }
    } else {
      // set the deliminator
      delim = arg;
      delim_len = strlen(arg);
    }
  }

  if (delim_len <= 0) {
    split_help("missing required delim");
    exit(1);
  }

  buffer_init(buf);

  unsigned short foundDelimChars = 0;
  char c = getchar();
  while (c != EOF) {
    if (foundDelimChars < delim_len && c == delim[foundDelimChars]) {
      foundDelimChars++;
      buffer_add(buf, c);
    }else if (delim_len == foundDelimChars) {
      if (include_delim < 0) {
        buffer_write(buf);
      }
      putchar('\n');

      if (include_delim > 0) {
        buffer_write(buf);
      }

      buffer_clear(buf);
      putchar(c);
      foundDelimChars = 0;
    } else {
      if (foundDelimChars > 0) {
        buffer_write(buf);
        buffer_clear(buf);
        foundDelimChars = 0;
      }
      putchar(c);
    }

    c = getchar();
  }

  buffer_close(buf);
}