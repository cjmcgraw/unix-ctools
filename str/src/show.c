#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <string.h>

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
  if (argc <= 1) {
    show_help("no command provided!");
    exit(1);
  }

  char *cmd = argv[0];
  wchar_t *lookup;
  wchar_t *translation;

  if (strcasecmp(cmd, "whitespace") == 0) {
    lookup = ' \t\r\n';
    translation = '·￫§¶';
  } else {
    char *msg;
    snprintf(msg, 100, "unknown command given %s", cmd);
    show_help(msg);
    exit(1);
  }

  wchar_t c = getwchar();
  while (c != EOF) {
    wchar_t *idx = wcschr(lookup, c);
    if (idx != NULL) {
      wchar_t replacement = translation[*idx];
      putwchar(replacement);
    } else {
      putwchar(c);
    }
  }
}