#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <locale.h>
#include "utils.h"


void show_help(char *msg) {
  fprintf(stderr, "\n");
  fprintf(stderr, "  ERROR: %s\n", msg);
  fprintf(stderr, "\n");
  fprintf(stderr, "commands:\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "  whitespace       translates whitespace characters to visible\n");
  fprintf(stderr, "\n");
}

void show(int argc, char **argv)
{    
  setlocale(LC_ALL, "");

  if (argc <= 0) {
    show_help("no command provided!");
    exit(1);
  }

  wchar_t *lookup;
  wchar_t *translation;

  switchs(argv[0]) {
    cases("whitespace")
      lookup = UTF(" \t\r\n");
      translation = UTF("·￫§¶");
      break;
    defaults
      show_help("unknown command!");
      exit(1);
  } switchs_end;

  wchar_t c = getwchar();
  while (c != EOF) {
    wchar_t *loc = wcschr(lookup, c);
    if (loc != NULL) {
      int idx = loc - lookup;
      wchar_t replacement = translation[idx];
      printf("%lc", replacement);
      if ('\n' == c) {
        printf("%lc", c);
      }
    } else {
      printf("%lc", c);
    }
    c = getwchar();
  }
}