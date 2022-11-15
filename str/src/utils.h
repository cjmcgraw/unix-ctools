#ifndef UTILS_H_
#define UTILS_H_

#include <string.h>
#include <regex.h>
#include <stdbool.h>

#define UTF(x)  L##x
#define str_equals(a, b) strcmp(a, b) == 0
#define str_startswith(a, b) strncmp(a, b, strlen(b)) == 0

/** Begin a switch for the string x */
#define switchs(x) \
    { char *ss__sw = (x); bool ss__done = false; bool ss__cont = false; \
        regex_t ss__regex; regcomp(&ss__regex, ".*", 0); do {

/** Check if the string matches the cases argument (case sensitive) */
#define cases(x)    } if ( ss__cont || !strcmp ( ss__sw, x ) ) \
                        { ss__done = true; ss__cont = true;

/** Check if the string matches the icases argument (case insensitive) */
#define icases(x)    } if ( ss__cont || !strcasecmp ( ss__sw, x ) ) { \
                        ss__done = true; ss__cont = true;

/** Check if the string matches the specified regular expression using regcomp(3) */
#define cases_re(x,flags) } regfree ( &ss__regex ); if ( ss__cont || ( \
                              0 == regcomp ( &ss__regex, x, flags ) && \
                              0 == regexec ( &ss__regex, ss__sw, 0, NULL, 0 ) ) ) { \
                                ss__done = true; ss__cont = true;

/** Default behaviour */
#define defaults    } if ( !ss__done || ss__cont ) {

/** Close the switchs */
#define switchs_end } while ( 0 ); regfree(&ss__regex); }

struct Buffer {
  char *buf;
  size_t len;
  FILE *stream;
};

void buffer_init(struct Buffer *buffer);
void buffer_add(struct Buffer *buffer, char data);
void buffer_write(struct Buffer *buffer);
void buffer_clear(struct Buffer *buffer);
void buffer_close(struct Buffer *buffer);

#endif
