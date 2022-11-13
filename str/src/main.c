#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trim.h"

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
  fprintf(stderr, "  trim         allows triming/stripping of leading/trailing whitespace");
  fprintf(stderr, "\n");
}

int main(int argc, char **argv)
{
  if (argc <= 1) {
    help("no command given!");
    exit(1);
  }
  char *cmd = argv[1];
  if (strcasecmp(cmd, "trim") != -1) {
      trim_stdin_lines(argc - 1, &argv[2]);
  } else {
      char *msg;
      sprintf(msg, "unknown command: %s", argv[1]);
      help(msg);
      exit(1);
  }
  exit(0);
}
