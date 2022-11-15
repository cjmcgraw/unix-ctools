#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void buffer_init(struct Buffer *buf) {
  buf->stream = open_memstream(&buf->buf, &buf->len);
}

void buffer_add(struct Buffer *buffer, char data) {
  fputc(data, buffer->stream);
}

void buffer_write(struct Buffer *buffer) {
  int i;
  fflush(buffer->stream);
  if (buffer->len > 0) {
    for (i = 0; i<buffer->len; i++) {
      putchar(buffer->buf[i]);
    }
  }
}

void buffer_clear(struct Buffer *buffer) {
  rewind(buffer->stream);
  buffer->len = 0;
}

void buffer_close(struct Buffer *buffer) {
  fclose(buffer->stream);
  free(buffer->buf);
}

