#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * We are going to use some variables in the external state
 * because we don't expect to be needing them independently,
 * its also helpful to not have to malloc data to the heap
 */
char *buf;
size_t len;
FILE *stream;

void buffer_init() {
  stream = open_memstream(&buf, &len);
}

void buffer_add(char data) {
  fputc(data, stream);
}

void buffer_write() {
  fflush(stream);
  for (int i = 0; i<len; i++) {
    putchar(buf[i]);
  }
  len = 0;
}

void buffer_clear() {
  rewind(stream);
}

void buffer_close() {
  fclose(stream);
}


/**
 * @brief program derived from K&R getchar/putchar example
 */
void trim_stdin_lines(int argc, char **argv)
{
  buffer_init();
  short lineHasStarted = 0;
  int c = getchar();
  while (c != EOF) {
    if ('\n' == c) {
      /*
       * We found a newline character. We should refresh
       * the buffer and
       * need to buffer them. We can just skip and
       * continue about our marry way
       */
      putchar(c);
      buffer_clear();
      lineHasStarted = 0;
    } else if (isspace(c) && lineHasStarted != 0) {
      /*
       * We found a whitespace character
       * and we know that the line has previous
       * characters so we are going to start
       * adding the buffer incase we need to flush
       */
      buffer_add(c);
    } else if (!isspace(c)) {
      /*
       * We have encountered a valid printable character
       * so we need to flush the buffer and continue
       */
      lineHasStarted = 1;
      buffer_write();
      buffer_clear();
      putchar(c);
    }
    c = getchar();
  }
  buffer_close();
}
