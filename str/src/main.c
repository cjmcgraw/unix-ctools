#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trim.h"
#include "show.h"
#include "split.h"
#include "utils.h"

void help(char *msg) {
  fprintf(stderr, "\n");
  fprintf(stderr, "usage: str <cmd>\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "  executes common string operations line by line\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "  ERROR: %s\n", msg);
  fprintf(stderr, "\n");
  fprintf(stderr, "commands:\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "  split    splits into multiple lines based on some delimiter\n");
  fprintf(stderr, "  trim     allows triming/stripping of leading/trailing whitespace\n");
  fprintf(stderr, "  show     translate non-visible characters into visible characters\n");
  fprintf(stderr, "\n");
}

int main(int argc, char **argv)
{
  if (argc <= 1) {
    help("no command given!");
    exit(1);
  }

  switchs(argv[1]) {
    cases("trim")
      trim_stdin_lines(argc - 2, &argv[2]);
      break;

    cases("show")
      show(argc - 2, &argv[2]);
      break;

    cases("split")
      split_on_delims(argc - 2, &argv[2]);
      break;

    defaults
      char *msg;
      sprintf(msg, "unknown command: %s", argv[1]);
      help(msg);
      exit(1);
      break;
  } switchs_end;
  exit(0);
}
