#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

/**
 * @brief program derived from K&R getchar/putchar example
 */
void trim_stdin_lines(int argc, char **argv)
{
  struct Buffer *buf;

  buffer_init(buf);
  short lineHasStarted = 0;
  int c = getchar();
  while (c != EOF) {
    if ('\n' == c) {
      /*
       * We found a newline character. We should refresh
       * the buffer and need to buffer them. We can just 
       * skip and continue about our marry way
       */
      putchar(c);
      buffer_clear(buf);
      lineHasStarted = 0;
    } else if (isspace(c) && lineHasStarted != 0) {
      /*
       * We found a whitespace character
       * and we know that the line has previous
       * characters so we are going to start
       * adding the buffer incase we need to flush
       */
      buffer_add(buf, c);
    } else if (!isspace(c)) {
      /*
       * We have encountered a valid printable character
       * so we need to flush the buffer and continue
       */
      lineHasStarted = 1;
      buffer_write(buf);
      buffer_clear(buf);
      putchar(c);
    }
    c = getchar();
  }
  buffer_close(buf);
}
