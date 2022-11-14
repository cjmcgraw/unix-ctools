#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Buffer {
  char *buf;
  size_t len;
  FILE *stream;
} buffer;

void buffer_init(struct buffer *buf) {
  buffer->stream = open_memstream(&buf->buf, &buffer->len);
}

void buffer_add(struct Buffer *buffer, char data) {
  fputc(data, buffer->stream);
}

void buffer_write(struct Buffer *buffer) {
  int i;
  fflush(buffer->stream);
  for (i = 0; i<buffer->len; i++) {
    putchar(buffer->buf[i]);
  }
  buffer->len = i;
}

void buffer_clear(struct Buffer *buffer) {
  rewind(buffer->stream);
  buffer->len = 0;
}

void buffer_close(struct Buffer *buffer) {
  fclose(buffer->stream);
}

